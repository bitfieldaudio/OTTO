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
          char c2 = (cut.type == TapeCut::IN) ? 'I'
            : (cut.type == TapeCut::OUT) ? 'O'
            : 'S';
          auto cp = SF_CUES::SF_CUE_POINT {
            cues.cue_count - 1,
            (uint32_t) cut.pos,
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

  auto tc = cuts[track-1];
  tc.addSlice(slice);
  newCuts = true;

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

  auto tc = cuts[track-1];
  tc.addSlice(slice);
  newCuts = true;

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

void TapeBuffer::cutTape(int track) {
  TapeCuts tc = cuts[track - 1];
  if (tc.inSlice(position())) {
    tc.cut({position(), TapeCut::SPLIT});
  }
}

std::vector<TapeBuffer::TapeCut> TapeBuffer::cutsIn(Section<TapeTime> area, int track) {
  return cuts[track-1].cutsIn(area);
}

bool TapeBuffer::inSlice(int track) {
  return cuts[track-1].inSlice(position());
}

TapeBuffer::TapeSlice TapeBuffer::currentSlice(int track) {
  return cuts[track-1].current(position());
}

std::vector<TapeBuffer::TapeSlice> TapeBuffer::slicesIn(Section<TapeTime> area, int track) {
  return cuts[track-1].slicesIn(area);
}

// TapeCuts

void TapeBuffer::TapeCuts::reCache() {
  cache.clear();
  for (auto cut = data.begin(); cut != data.end(); ++cut) {
    if (cut->type == TapeCut::IN) {
      TapeTime in = cut->pos;
      ++cut;
      while (cut->type == TapeCut::SPLIT) {
        cache.insert({in, cut->pos});
        in = cut->pos;
        ++cut;
      }
      if (cut->type == TapeCut::OUT) {
        cache.insert({in, cut->pos});
      } else {
        LOGE << fmt::format("Expected OUT cut at {}. Got {}", cut->pos,
        cut->type == TapeCut::IN ? "IN" : "SPLIT");
        break;
      }
    } else {
      LOGE << fmt::format("Expected IN cut at {}. Got {}", cut->pos,
      cut->type == TapeCut::OUT ? "OUT" : "SPLIT");
      break;
    }
  }
}

std::vector<TapeBuffer::TapeSlice>
  TapeBuffer::TapeCuts::slicesIn(Section<TapeTime> area) {
  std::vector<TapeBuffer::TapeSlice> xs;
  auto it = cache.upper_bound(area);
  if (!it->overlaps(area)) it++;
  for (; it != cache.end(); it++) {
    if (area.overlaps(*it)) {
      xs.push_back(*it);
    } else {
      break;
    }
  }
  return xs;
}

std::vector<TapeBuffer::TapeCut>
  TapeBuffer::TapeCuts::cutsIn(Section<TapeTime> area) {
  std::vector<TapeBuffer::TapeCut> xs;
  auto it = data.lower_bound({area.in, TapeCut::NONE});
  for (; it != data.end(); it++) {
    if (area.contains(it->pos)) {
      xs.push_back(*it);
    } else {
      break;
    }
  }
  return xs;
}

bool TapeBuffer::TapeCuts::inSlice(TapeTime time) {
  if (cache.size() == 0) return false;
  auto it = cache.upper_bound({time, time});
  if (it == cache.end()) {
    it = cache.begin();
  }
  if (it->contains(time)) {
    return true;
  } else {
    it++;
    return it->contains(time);
  }
}

TapeBuffer::TapeSlice TapeBuffer::TapeCuts::current(TapeTime time) {
  auto it = cache.upper_bound({time, time});
  if (it->contains(time)) {
    return *it;
  } else {
    it++;
    if (it->contains(time))
      return *it;
    return {0, 0};
  }
}

TapeBuffer::TapeCut TapeBuffer::TapeCuts::nearest(TapeTime time) {
  auto prev = data.upper_bound({time, TapeCut::NONE});
  auto next = data.lower_bound({time, TapeCut::NONE});
  if (prev != data.end()) {
    if (next == data.end()) {
      return *prev;
    }
    if ((time - prev->pos) > (next->pos - time)) {
      return *next;
    }
    return *prev;
  }
  return {0, TapeCut::NONE};
}

void TapeBuffer::TapeCuts::cut(TapeBuffer::TapeCut cut) {
  data.insert(cut);
  reCache();
}

void TapeBuffer::TapeCuts::addSlice(TapeBuffer::TapeSlice slice) {
  auto typeI = inSlice(slice.in) ? TapeCut::SPLIT : TapeCut::IN;
  auto typeO = inSlice(slice.out) ? TapeCut::SPLIT : TapeCut::OUT;
  for (auto cut : cutsIn(slice)) {
    data.erase(cut);
  }
  data.insert({slice.in, typeI});
  data.insert({slice.out, typeO});
  reCache();
}

void TapeBuffer::TapeCuts::glue(TapeTime time) {
  data.erase(data.find({time, TapeCut::NONE}));
  reCache();
}
