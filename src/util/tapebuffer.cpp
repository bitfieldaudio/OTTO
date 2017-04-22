#include "tapebuffer.h"

#include <cmath>
#include <sndfile.hh>
#include "../globals.h"

/*******************************************/
/*  TapeBuffer Implementation              */
/*******************************************/

TapeBuffer::TapeBuffer() : playPoint (0) {
  // Lambda magic to run member in new thread
  diskThread = std::thread([this]{threadRoutine();});
}

// Disk handling:

void TapeBuffer::threadRoutine() {
  std::unique_lock<std::mutex> lock (threadLock);

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

    int desLength = buffer.SIZE / 2 - 16;

    if (buffer.lengthFW < desLength) {
      uint startIdx = buffer.playIdx + buffer.lengthFW; 
      snd.seek(buffer.posAt0 + startIdx, SEEK_SET);
      uint nframes = desLength - buffer.lengthFW;
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
      buffer.lengthFW += nframes;
      int overflow = buffer.lengthFW + buffer.lengthBW - buffer.SIZE;
      if (overflow > 0) {
        buffer.lengthBW -= overflow;
      }
    }

    if (buffer.lengthBW < desLength) {
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

    readData.wait(lock);
  }
}

void TapeBuffer::movePlaypointRel(int time) {
  movePlaypointAbs(playPoint + time);
}

void TapeBuffer::movePlaypointAbs(uint newPos) {
  uint oldPos = playPoint;
  int diff = newPos - oldPos;
  if (diff <= buffer.lengthFW && diff >= -buffer.lengthBW) {
    // The new position is within the loaded section, so keep that data
    // TOD: This should probably also happen if the new position is just
    //   slightly outside the section.
    //   That could be fixed with setting negative lenghts
    buffer.playIdx = buffer.wrapIdx(newPos - buffer.posAt0);
    buffer.lengthBW += diff;
    buffer.lengthFW -= diff;
  } else {
    // just discard the data
    buffer.lengthBW = 0;
    buffer.lengthFW = 0;
  }
  if (buffer.notWritten) {
    // shit, we need to change posAt0 but then this will be written to the
    // wrong place in file
    // TODO: handle this
  }
  buffer.posAt0 = newPos - buffer.playIdx;
  readData.notify_all();
}


// Fancy wrapper methods!

std::vector<float> TapeBuffer::readFW(uint nframes, uint track) {
  uint n = (nframes > buffer.lengthFW) ? buffer.lengthFW : nframes;

  auto ret = std::vector<float>(n);

  for (uint i = 0; i < n; i++) {
   ret.push_back(buffer[i][track - 1]);
  }

  movePlaypointRel(n);

  return ret;
}

std::vector<float> TapeBuffer::readBW(uint nframes, uint track) {
  uint n = (nframes > buffer.lengthBW) ? buffer.lengthBW : nframes;

  std::vector<float> rev (n);

  for (uint i = 0; i < n; i++) {
    rev.push_back(buffer[-i][track - 1]);
  }

  movePlaypointRel(-n);

  return rev;
}

uint TapeBuffer::writeFW(std::vector<float> data, uint track) {
  uint n = (data.size() > buffer.capacityFW()) ? buffer.capacityFW() : data.size();
  for (uint i = 0; i < n; i++) {
    buffer[i][track-1] = data[i];
  }
  return data.size() - n;
}

uint TapeBuffer::writeBW(std::vector<float> data, uint track) {
  uint n = (data.size() > buffer.capacityBW())
    ? buffer.capacityBW() : data.size();
  for (uint i = 0; i < n; i++) {
    buffer[n-i][track-1] = data[i];
  }
  return data.size() - n;
}

void TapeBuffer::goTo(uint pos) {
  movePlaypointAbs(pos);
}
