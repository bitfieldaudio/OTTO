#include "tapebuffer.h"

#include <cmath>
#include <algorithm>
#include <sndfile.hh>
#include "../globals.h"

//typedef SF_CUES_VAR (2048) SF_CUES ;
typedef struct
{	int cue_count ;

  struct SF_CUE_POINT
  {	int32_t   indx ;
    uint32_t  position ;
    int32_t   fcc_chunk ;
    int32_t   chunk_start ;
    int32_t   block_start ;
    uint32_t  sample_offset ;
    char name [256] ;
  } cue_points [2048] ;
} SF_CUES ;

/*******************************************/
/*  TapeBuffer Implementation              */
/*******************************************/

TapeBuffer::TapeBuffer() : playPoint (0), newCuts (false) {
  // Lambda magic to run member in new thread
  diskThread = std::thread([this]{threadRoutine();});
}

// Disk handling:

void TapeBuffer::threadRoutine() {
  std::unique_lock<std::mutex> lock (threadLock);

  movePlaypointAbs(0);

  int samplerate = GLOB.samplerate;
  int format = SF_FORMAT_WAV | SF_FORMAT_PCM_32;

  SndfileHandle snd (GLOB.project->path, SFM_RDWR, format, nTracks, samplerate);
  float *framebuf = (float *) malloc(sizeof(float) * nTracks * buffer.SIZE / 2);

  if (snd.error()) {
    LOGE << "Cannot open sndfile '" <<
      GLOB.project->path.c_str() << "' for output:";
    LOGE << snd.strError();

    GLOB.running = false;
  }

  while(GLOB.running) {

    // Keep some space in the middle to avoid overlap fights
    int desLength = buffer.SIZE / 2 - sizeof(AudioFrame);

    if (buffer.notWritten) {
      // TODO: theres gonna be a pesky data race!
      int startIdx = buffer.notWritten.in;
      int startTime = buffer.posAt0 + buffer.notWritten.in;
      if (startTime < 0) {
        startIdx = buffer.notWritten.in -= startTime;
        startTime = buffer.posAt0 + buffer.notWritten.in;
      }
      snd.seek(startTime, SEEK_SET);
      // TODO: This really should be done more than a sample at a time
      for (int i = 0; i < buffer.notWritten.size(); i++) {
        snd.writef(
          (float *) (buffer.data.data() + buffer.wrapIdx(startIdx + i)), 1);
      }
      buffer.notWritten.in = buffer.notWritten.out = buffer.playIdx;
    }

    if (buffer.lengthFW < desLength - MIN_READ_SIZE) {
      uint startIdx = buffer.playIdx + buffer.lengthFW; 
      snd.seek(buffer.posAt0 + startIdx, SEEK_SET);
      uint nframes = desLength - buffer.lengthFW;
      memset(framebuf, 0, nframes * nTracks * sizeof(float));
      uint read = snd.readf(framebuf, nframes);
      for (uint i = 0; i < nframes; i++) {
        // TODO: Read directly into buffer
        buffer[startIdx + i] = AudioFrame{{
          framebuf[nTracks * i],
          framebuf[nTracks * i + 1],
          framebuf[nTracks * i + 2],
          framebuf[nTracks * i + 3],
        }};
      }
      buffer.lengthFW += nframes;
      int overflow = buffer.lengthFW + buffer.lengthBW - buffer.SIZE;
      if (overflow > 0) {
        buffer.lengthBW -= overflow;
      }
    }

    if (buffer.lengthBW < desLength - MIN_READ_SIZE) {
      uint nframes = desLength - buffer.lengthBW;
      int startIdx = buffer.playIdx - buffer.lengthBW - nframes; 
      snd.seek(buffer.posAt0 + startIdx, SEEK_SET);
      memset(framebuf, 0, nframes * nTracks * sizeof(float));
      uint read = snd.readf(framebuf, nframes);
      for (uint i = 0; i < nframes; i++) {
        buffer[startIdx + i] = AudioFrame{{
            framebuf[nTracks * i],
            framebuf[nTracks * i + 1],
            framebuf[nTracks * i + 2],
            framebuf[nTracks * i + 3],
          }};
      }
      buffer.lengthBW += nframes;
      int overflow = buffer.lengthFW + buffer.lengthBW - buffer.SIZE;
      if (overflow > 0) {
        buffer.lengthFW -= overflow;
      }
    }

    if (newCuts) {
      SF_CUES cues {0};
      for (int track = 0;track < 4; track++) {
        auto tc = cuts[track];
        for (auto cut : tc) {
          char c1 = std::to_string(track).at(0);
          char c2 = (cut.second == CUT_IN) ? 'I'
            : (cut.second == CUT_OUT) ? 'O'
            : 'S';
          auto cp = SF_CUES::SF_CUE_POINT {
            cues.cue_count - 1,
            (uint32_t) cut.first,
            0, 0, 0, 0,
            {c1, c2},
          };
          cues.cue_points[cues.cue_count] = cp;
          cues.cue_count++;
        }
      }
      snd.command(0x10CF, &cues, sizeof(cues));
      newCuts = false;
    }

    readData.wait(lock);
  }
}

void TapeBuffer::movePlaypointRel(int time) {
  movePlaypointAbs(playPoint + time);
}

void TapeBuffer::movePlaypointAbs(int newPos) {
  if (newPos < 0) {
    newPos = 0;
  }
  uint oldPos = playPoint;
  int diff = newPos - oldPos;
  if (diff <= buffer.lengthFW && diff >= -buffer.lengthBW) {
    // The new position is within the loaded section, so keep that data
    // TOD: This should probably also happen if the new position is just
    //   slightly outside the but idk what to tell ya, section.
    //   That could be fixed with setting negative lenghts
    buffer.playIdx = buffer.wrapIdx(newPos - buffer.posAt0);
    buffer.lengthBW += diff;
    buffer.lengthFW -= diff;
  } else {
    // just discard the data
    buffer.lengthBW = 0;
    buffer.lengthFW = 0;
  }
  uint newTime = newPos - buffer.playIdx;
  if (newTime != buffer.posAt0) {
    buffer.notWritten.in += buffer.posAt0 - newTime;
    buffer.notWritten.out += buffer.posAt0 - newTime;
    buffer.posAt0 = newTime;
  }
  playPoint = newPos;
  readData.notify_all();
}

// Fancy wrapper methods!

std::vector<float> TapeBuffer::readFW(uint nframes, uint track) {
  uint n = std::min<int>(buffer.lengthFW, nframes);

  std::vector<float> ret;

  for (uint i = 0; i < n; i++) {
   ret.push_back(buffer[buffer.playIdx + i][track - 1]);
  }

  movePlaypointRel(n);

  return ret;
}

std::vector<AudioFrame> TapeBuffer::readAllFW(uint nframes) {
  uint n = std::min<int>(nframes, buffer.lengthFW);

  std::vector<AudioFrame> ret;

  for (uint i = 0; i < n; i++) {
    ret.push_back(buffer[buffer.playIdx + i]);
  }

  movePlaypointRel(n);

  return ret;
}

std::vector<float> TapeBuffer::readBW(uint nframes, uint track) {
  uint n = std::min<int>(nframes, buffer.lengthBW);

  std::vector<float> ret;

  for (uint i = 0; i < n; i++) {
    ret.push_back(buffer[buffer.playIdx - i][track - 1]);
  }

  movePlaypointRel(-n);

  return ret;
}

std::vector<AudioFrame> TapeBuffer::readAllBW(uint nframes) {
  uint n = std::min<int>(nframes, buffer.lengthBW);

  std::vector<AudioFrame> ret;

  for (uint i = 0; i < n; i++) {
    ret.push_back(buffer[buffer.playIdx - i]);
  }

  movePlaypointRel(-n);

  return ret;
}

uint TapeBuffer::writeFW(std::vector<float> data, uint track) {
  uint n = std::min<int>(data.size(), buffer.SIZE - buffer.lengthFW);

  int beginPos = buffer.playIdx - n;

  for (uint i = 0; i < n; i++) {
    buffer[beginPos + i][track - 1] = data[i];
  }

  if (buffer.notWritten) {
    buffer.notWritten.in =
      std::min<int>(buffer.notWritten.in, beginPos);
    buffer.notWritten.out =
      std::max<int>(buffer.notWritten.out, buffer.playIdx);
  } else {
    buffer.notWritten.in = beginPos;
    buffer.notWritten.out = buffer.playIdx;
  }

  auto tc = cuts[track-1];
  auto first = tc.lower_bound(position());
  auto last = tc.upper_bound(position() + n);

  tc.erase(first, last);
  ++last;
  auto type = last->second != CUT_IN ? CUT_SPLIT : CUT_OUT;
  tc[position() + n] = type;
  newCuts = true;

  buffer.lengthBW =
    std::max<int>(data.size(), buffer.lengthBW);
  buffer.lengthFW =
    std::min<int>(buffer.lengthFW, buffer.SIZE - buffer.lengthBW);

  return data.size() - n;
}

uint TapeBuffer::writeBW(std::vector<float> data, uint track) {
  uint n = std::min<int>(data.size(), buffer.SIZE - buffer.lengthBW);

  int endPos = buffer.playIdx + n;

  for (uint i = 0; i < n; i++) {
    buffer[endPos - i][track - 1] = data[i];
  }

  if (buffer.notWritten) {
    buffer.notWritten.in =
      std::min<int>(buffer.notWritten.in, buffer.playIdx);
    buffer.notWritten.out =
      std::max<int>(buffer.notWritten.out, endPos);
  } else {
    buffer.notWritten.in = buffer.playIdx;
    buffer.notWritten.out = endPos;
  }

  buffer.lengthFW =
    std::max<int>(data.size(), buffer.lengthFW);
  buffer.lengthBW =
    std::min<int>(buffer.lengthBW, buffer.SIZE - buffer.lengthFW);

  return data.size() - n;
}

void TapeBuffer::goTo(TapeTime pos) {
  movePlaypointAbs(pos);
}

// Cuts & Slices

TapeBuffer::TapeCutSet::iterator findClosest(
  TapeBuffer::TapeCutSet &data, TapeTime pos) {
  auto upper = data.lower_bound(pos);
  if (upper == data.begin() || upper->first == pos)
    return upper;
  auto lower = upper;
  --lower;
  if (upper == data.end() || (pos - lower->first) < (upper->first - pos))
    return lower;
  return upper;
}

void TapeBuffer::cutTape(int track) {
  TapeCutType type = inSlice(track) ? CUT_SPLIT : CUT_IN;
  cuts[track-1][position()] = type;
}

TapeBuffer::TapeCutSet TapeBuffer::cutsIn(Section<TapeTime> area, int track) {
  TapeCutSet xs;
  TapeCutSet tc = cuts[track-1];
  for (auto it = tc.lower_bound(area.in);
       it->first < tc.upper_bound(area.out)->first; ++it) {
    xs[it->first] = it->second;
  }
  return xs;
}

bool TapeBuffer::inSlice(int track) {
  auto closest = *findClosest(cuts[track-1], position());
  return ((closest.first >= position() && closest.second != CUT_IN)
       || (closest.first <= position() && closest.second != CUT_OUT));
}

TapeBuffer::TapeSlice TapeBuffer::currentSlice(int track) {
  if (!inSlice(track)) return {0, 0, 0};
  TapeCutSet tc = cuts[track - 1];
  TapeTime pos = position();
  return {tc.upper_bound(pos)->first, tc.lower_bound(pos)->first, track};
}

std::vector<TapeBuffer::TapeSlice> TapeBuffer::slicesIn(Section<TapeTime> area, int track) {
  std::vector<TapeBuffer::TapeSlice> xs;
  TapeCutSet tc = cuts[track-1];

  if (tc.size() == 0) return xs;

  auto first = tc.upper_bound(area.in);
  auto last  = tc.lower_bound(area.out);
  if (last == tc.end()) --last;
  if (first == tc.end()) first = tc.begin();

  for (auto it = first;
       it != tc.end() && it->first < last->first; ++it) {
    if (it->second != CUT_OUT) {
      TapeTime in = it->first;
      ++it;
      TapeSlice ts = {in, it->first, track};
      if (ts.overlaps(area)) xs.push_back(ts);
      if (it->second == CUT_SPLIT) --it;
    }
  }
  return xs;
}
