#include "tapebuffer.h"

#include <cmath>
#include <algorithm>
#include "../globals.h"
#include "tapefile.h"

namespace top1 {

/*******************************************/
/*  TapeBuffer Implementation              */
/*******************************************/

TapeBuffer::TapeBuffer() : playPoint (0), newCuts (false) {}

void TapeBuffer::init() {
  diskThread = std::thread([this]{threadRoutine();});
}

void TapeBuffer::exit() {
  readData.notify_all();
  diskThread.join();
}

// Disk handling:

void TapeBuffer::threadRoutine() {
  movePlaypointAbs(0);

  TapeFile file (GLOB.project->path);
  const static uint FRAMEBUF_SIZE = RingBuffer::SIZE / 2;
  std::array<AudioFrame, FRAMEBUF_SIZE> framebuf;

  if (file.error.log()) GLOB.exit();

  for (uint t = 0; t < 4; t++) {
    auto &slices = file.slices.tracks[t];
    for (uint i = 0; i < slices.count; i++) {
      auto &slice = slices.slices[i];
      trackSlices[t].addSlice({(int)slice.inPos, (int)slice.outPos});
    }
    trackSlices[t].changed = false;
  }

  bool runAgain = false;


waitData:
  while(GLOB.running()) {
    std::unique_lock<std::recursive_mutex> lock (threadLock);

    // Keep some space in the middle to avoid overlap fights
    int desLength = buffer.SIZE / 2 - sizeof(AudioFrame);

    if (buffer.notWritten) {
      int startIdx = buffer.notWritten.in;
      int startTime = buffer.posAt0 + startIdx;
      if (startTime < 0) {
        startIdx = buffer.notWritten.in -= startTime;
        startTime = buffer.posAt0 + buffer.notWritten.in;
      }
      file.seek(startTime);
      file.write(
        buffer.data.data() + buffer.wrapIdx(startIdx),
        buffer.notWritten.size());
      file.error.log();
      buffer.notWritten.in = buffer.notWritten.out = buffer.playIdx;
    }

    if (buffer.lengthFW < desLength - MIN_READ_SIZE) {
      uint startIdx = buffer.playIdx + buffer.lengthFW; 
      file.seek(buffer.posAt0 + startIdx);
      uint nframes = desLength - buffer.lengthFW;
      framebuf.fill(0);
      file.read(framebuf.data(), nframes);
      file.error.log();
      for (uint i = 0; i < nframes; i++) {
        // TODO: Read directly into buffer
        buffer[startIdx + i] = framebuf[i];
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
      file.seek(buffer.posAt0 + startIdx);
      framebuf.fill(0);
      file.read(framebuf.data(), nframes);
      file.error.log();
      for (uint i = 0; i < nframes; i++) {
        buffer[startIdx + i] = framebuf[i];
      }
      buffer.lengthBW += nframes;
      int overflow = buffer.lengthFW + buffer.lengthBW - buffer.SIZE;
      if (overflow > 0) {
        buffer.lengthFW -= overflow;
      }
    }

    {
      // Lift frames
      if (clipboard.fromSlice.size() > 0) {
        LOGD << "Lifting " << clipboard.fromSlice.size() << " frames from "
             << clipboard.fromSlice.in;
        std::unique_lock<std::mutex> clipboardLock (clipboard.lock);
        TapeSlice readSlice = {
          clipboard.fromSlice.in,
          clipboard.fromSlice.in
        };
        clipboard.data.clear();
        framebuf.fill(0);
        while(readSlice.out < clipboard.fromSlice.out) {
          readSlice.out = std::min<int>(
            readSlice.in + FRAMEBUF_SIZE,
            clipboard.fromSlice.out);
          file.seek(readSlice.in);
          file.read(framebuf.data(), readSlice.size());
          for (int i = 0; i < readSlice.size(); i++) {
            clipboard.data.push_back(framebuf[i][clipboard.fromTrack]);
            framebuf[i][clipboard.fromTrack] = 0;
          }
          file.seek(readSlice.in);
          file.write(framebuf.data(), readSlice.size());
          readSlice.in = readSlice.out;
        }
        buffer.lengthFW = buffer.lengthBW = 0;
        runAgain = true;
        clipboard.fromSlice = {0,0};
      }

      // Drop frames
      if (clipboard.toTime >= 0 && !clipboard.data.empty()) {
        std::unique_lock<std::mutex> clipboardLock (clipboard.lock);
        LOGD << "Dropping " << clipboard.data.size() << " frames at " << clipboard.toTime;
        TapeSlice writeSlice = {
          clipboard.toTime,
          clipboard.toTime
        };
        while(true) {
          writeSlice.out = writeSlice.in + std::min<int>(
            FRAMEBUF_SIZE, clipboard.data.size() - writeSlice.in + clipboard.toTime);

          if (!((ulong)writeSlice.size() <= clipboard.data.size())) break;
          if (writeSlice.size() == 0) break;

          framebuf.fill(0);
          file.seek(writeSlice.in);
          file.read(framebuf.data(), writeSlice.size());
          uint startIdx = writeSlice.in - clipboard.toTime;
          int i;
          for (i = 0; i < writeSlice.size(); i++) {
            framebuf[i][clipboard.toTrack] = clipboard.data[startIdx + i];
          }
          LOGD << i;
          file.seek(writeSlice.in);
          file.write(framebuf.data(), writeSlice.size());
          writeSlice.in = writeSlice.out;
        }
        file.flush();
        buffer.lengthFW = buffer.lengthBW = 0;
        runAgain = true;
        clipboard.toTime = -1;
      }
      clipboard.done.notify_all();
    }
    if (runAgain) runAgain = false;
    else readData.wait(lock);
  }

writeFileMetadata:
  for (uint i = 0; i < 4; i++) {
    auto &tsc = file.slices.tracks[i];
    auto &ts  = trackSlices[i];
    tsc.count = 0;
    for (auto slice : ts) {
      tsc.slices[tsc.count] = {
        (u4b)slice.in,
        (u4b)slice.out
      };
      tsc.count++;
    }
    ts.changed = false;
  }
  if (GLOB.running()) goto waitData;
  file.close();
}

void TapeBuffer::movePlaypointRel(int time) {
  movePlaypointAbs(playPoint + time);
}

void TapeBuffer::movePlaypointAbs(int newPos) {
  std::unique_lock<std::recursive_mutex> lock (threadLock);
  if (newPos < 0) {
    newPos = 0;
  }
  uint oldPos = playPoint;
  int diff = newPos - oldPos;
  if (diff <= buffer.lengthFW && diff >= -buffer.lengthBW) {
    // The new position is within the loaded section, so keep that data
    // TODO: This should probably also happen if the new position is just
    //   slightly outside the section.
    //   That could be fixed with setting negative FW/BW lenghts
    // NOTE: Section::overlaps has the correct algorithm for this
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
std::vector<AudioFrame> TapeBuffer::readFW(uint nframes) {
  uint n = std::min<int>(nframes, buffer.lengthFW);

  std::vector<AudioFrame> ret;

  for (uint i = 0; i < n; i++) {
    ret.push_back(buffer[buffer.playIdx + i]);
  }

  movePlaypointRel(n);

  return ret;
}

std::vector<AudioFrame> TapeBuffer::readBW(uint nframes) {
  uint n = std::min<int>(nframes, buffer.lengthBW);

  std::vector<AudioFrame> ret;

  for (uint i = 0; i < n; i++) {
    ret.push_back(buffer[buffer.playIdx - i]);
  }

  movePlaypointRel(-n);

  return ret;
}

uint TapeBuffer::writeFW(
  std::vector<AudioFrame> data,
  uint offset,
  std::function<AudioFrame(AudioFrame, AudioFrame)> writeFunc)
{
  std::unique_lock<std::recursive_mutex> lock (threadLock);
  int n = std::min<int>(data.size(), buffer.SIZE - buffer.lengthFW);

  int beginPos = buffer.playIdx - n - offset;

  for (int i = 0; i < n; i++) {
    buffer[beginPos + i] = writeFunc(buffer[beginPos + i], data[i]);
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

  buffer.lengthBW =
    std::max<int>(data.size(), buffer.lengthBW);
  buffer.lengthFW =
    std::min<int>(buffer.lengthFW, buffer.SIZE - buffer.lengthBW);

  return data.size() - n;
}

uint TapeBuffer::writeBW(
  std::vector<AudioFrame> data,
  uint offset,
  std::function<AudioFrame(AudioFrame, AudioFrame)> writeFunc)
{
  std::unique_lock<std::recursive_mutex> lock (threadLock);
  int n = std::min<int>(data.size(), buffer.SIZE - buffer.lengthBW);

  int endPos = buffer.playIdx + n + offset;

  for (int i = 0; i < n; i++) {
    buffer[endPos - i]= writeFunc(buffer[endPos - i], data[i]);
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
  if (it != slices.begin()) {
    it--;
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
  if (it != slices.begin()) {
    it--;
  }
  if (it->contains(time)) {
    return *it;
  } else {
    it++;
    if (it->contains(time))
      return *it;
    return {0, 0};
  }
}

void TapeBuffer::TapeSliceSet::erase(TapeBuffer::TapeSlice slice) {
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
      slices.emplace(slice.out + 1, s.out);
      break;
    case Section<>::CONTAINS_OUT:
      slices.erase(s);
      slices.emplace(s.in, slice.in - 1);
      break;
    }
  }
  changed = true;
}

void TapeBuffer::TapeSliceSet::addSlice(TapeBuffer::TapeSlice slice) {
  erase(slice);
  slices.emplace(slice.in, slice.out);
  changed = true;
}

void TapeBuffer::TapeSliceSet::cut(TapeTime time) {
  if (!inSlice(time)) return;
  TapeSlice slice = current(time);
  addSlice({slice.in, time - 1});
  addSlice({time, slice.out});
}

void TapeBuffer::TapeSliceSet::glue(TapeSlice s1, TapeSlice s2) {
  addSlice({std::min(s1.in, s2.in), std::max(s1.out, s2.out)});
}

void TapeBuffer::lift(uint track) {
  TapeSliceSet &tss = trackSlices[track - 1];
  if (!tss.inSlice(position())) {
    LOGD << "No slice to lift";
    return;
  }
  TapeSlice slice = tss.current(position());
  std::unique_lock<std::mutex> lock(clipboard.lock);
  clipboard.fromTrack = track - 1;
  clipboard.fromSlice = slice;
  readData.notify_all();
  clipboard.done.wait(lock);
  tss.erase(slice);
}

void TapeBuffer::drop(uint track) {
  std::unique_lock<std::mutex> lock(clipboard.lock);
  clipboard.toTrack = track - 1;
  clipboard.toTime = position();
  TapeSlice slice = {
    clipboard.toTime,
    clipboard.toTime + (int)clipboard.data.size()
  };
  readData.notify_all();
  clipboard.done.wait(lock);
  trackSlices[track - 1].addSlice(slice);
}
}
