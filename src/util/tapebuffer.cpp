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

    if (false) {
      SF_CUES cues {0};
      for (int track = 0;track < 4; track++) {
        char tchar = std::to_string(track + 1).at(0);
        auto ts = trackSlices[track];
        for (auto slice : ts) {
          auto cpin = SF_CUES::SF_CUE_POINT {
            cues.cue_count - 1,
            (uint32_t) slice.in,
            0, 0, 0, 0,
            {tchar, 'I'},
          };
          cues.cue_count++;
          cues.cue_points[cues.cue_count] = cpin;
          auto cpout = SF_CUES::SF_CUE_POINT {
            cues.cue_count - 1,
            (uint32_t) slice.out,
            0, 0, 0, 0,
            {tchar, 'O'},
          };
          cues.cue_count++;
          cues.cue_points[cues.cue_count] = cpout;
        }
      }
      snd.command(0x10CF, &cues, sizeof(cues));
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

uint TapeBuffer::writeFW(std::vector<float> data, uint track, TapeBuffer::TapeSlice &slice) {
  int n = std::min<int>(data.size(), buffer.SIZE - buffer.lengthFW);

  int beginPos = buffer.playIdx - n;

  for (int i = 0; i < n; i++) {
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

  slice.out = playPoint;
  trackSlices[track-1].addSlice(slice);

  buffer.lengthBW =
    std::max<int>(data.size(), buffer.lengthBW);
  buffer.lengthFW =
    std::min<int>(buffer.lengthFW, buffer.SIZE - buffer.lengthBW);

  return data.size() - n;
}

uint TapeBuffer::writeBW(std::vector<float> data, uint track, TapeBuffer::TapeSlice &slice) {
  int n = std::min<int>(data.size(), buffer.SIZE - buffer.lengthBW);

  int endPos = buffer.playIdx + n;

  for (int i = 0; i < n; i++) {
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

  slice.in = playPoint;
  trackSlices[track-1].addSlice(slice);

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
std::vector<TapeBuffer::TapeSlice>
TapeBuffer::TapeSliceSet::slicesIn(Section<TapeTime> area) const {
  std::vector<TapeBuffer::TapeSlice> xs;
  if (slices.size() == 0) {
    return xs;
  }
  auto it = slices.upper_bound(area);
  --it;
  if (it == slices.end()) it = slices.begin();
  if (!it->overlaps(area)) it++;
  for (; it != slices.end(); it++) {
    if (area.overlaps(*it)) {
      xs.push_back(*it);
    } else {
      break;
    }
  }
  return xs;
}

bool TapeBuffer::TapeSliceSet::inSlice(TapeTime time) const {
  if (slices.size() == 0) return false;
  auto it = slices.upper_bound({time, time});
  if (it == slices.end()) {
    it = slices.begin();
  }
  if (it->contains(time)) {
    return true;
  } else {
    it++;
    return it->contains(time);
  }
}

TapeBuffer::TapeSlice TapeBuffer::TapeSliceSet::current(TapeTime time) const {
  auto it = slices.upper_bound({time, time});
  if (it->contains(time)) {
    return *it;
  } else {
    it++;
    if (it->contains(time))
      return *it;
    return {0, 0};
  }
}

void TapeBuffer::TapeSliceSet::addSlice(TapeBuffer::TapeSlice slice) {
  if (slice.size() < 1) return;
  for (auto &s : slicesIn(slice)) {
    switch (slice.overlaps(s)) {
    case Section<>::NONE:
      break;
    case Section<>::CONTAINS:
      slices.erase(s);
      break;
    case Section<>::CONTAINED:
      slices.erase(s);
      slices.emplace(s.in, slice.in - 1);
      slices.emplace(slice.out + 1, s.out);
      break;
    case Section<>::CONTAINS_IN:
      slices.erase(s);
      slices.emplace(slice.out + 1, s.out); // TODO: Is the + 1 necessary?
      break;
    case Section<>::CONTAINS_OUT:
      slices.erase(s);
      slices.emplace(s.in, slice.in - 1); // TODO: Is the - 1 necessary?
      break;
    }
  }
  slices.emplace(slice.in, slice.out);
  LOGD << slices.size();
}

void TapeBuffer::TapeSliceSet::cut(TapeTime time) {
  //TODO
}

void TapeBuffer::TapeSliceSet::glue(TapeTime time) {
  // TODO
}
