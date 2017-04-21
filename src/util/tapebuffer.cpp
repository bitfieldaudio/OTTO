#include "tapebuffer.h"

#include <cmath>

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

  while(1) {

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
    buffer.playIdx = buffer.wrapIdx(newPos - buffer.posAt0);
    buffer.lengthBW += diff;
    buffer.lengthFW -= diff;
  } else {
    buffer.lengthBW = 0;
    buffer.lengthFW = 0;
  }
  if (buffer.notWritten) {
    // shit
    // TODO: handle this
  }
  buffer.posAt0 = newPos - buffer.playIdx;
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
