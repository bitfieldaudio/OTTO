#include "tapebuffer.hpp"

#include <cmath>
#include <algorithm>
#include "core/globals.hpp"
#include "util/tapefile.hpp"

namespace top1 {

  class TapeDiskThread {
  public:

    const static int MinReadSize = 2048;

    TapeBuffer& tb;
    TapeFile file;

    // Keep some space in the middle to avoid overlap fights
    int desLength = tb.buffer.Size / 2 - 2 * sizeof(TapeBuffer::AudioFrame);

    const static uint FrameBufSize = TapeBuffer::RingBuffer::Size / 2;
    top1::DynArray<TapeBuffer::AudioFrame> framebuf {FrameBufSize};
    std::thread thread;

    TapeDiskThread(TapeBuffer& tb)
      : tb (tb), thread (&TapeDiskThread::main, this) {}

    ~TapeDiskThread() {
      thread.join();
    }

  private:

    void readSlices() {
      Track::foreach([&](Track t) {
          auto &slices = file.slices.tracks[t.idx];
          for (uint i = 0; i < slices.count; i++) {
            auto &slice = slices.slices[i];
            tb.trackSlices[t.idx].addSlice({(int)slice.inPos, (int)slice.outPos});
          }
          tb.trackSlices[t.idx].changed = false;
        });
    }

    void writeNewSlices() {
      Track::foreach([&](Track t) {
          auto &tsc = file.slices.tracks[t.idx];
          auto &ts  = tb.trackSlices[t.idx];
          tsc.count = 0;
          for (auto slice : ts) {
            tsc.slices[tsc.count] = {
              (u4b)slice.in,
              (u4b)slice.out
            };
            tsc.count++;
          }
          ts.changed = false;
        });
    }

    void writeNewAudio() {
      int startIdx = tb.buffer.notWritten.in;
      int startTime = tb.buffer.posAt0 + startIdx;
      if (startTime < 0) {
        startIdx = tb.buffer.notWritten.in -= startTime;
        startTime = tb.buffer.posAt0 + tb.buffer.notWritten.in;
      }
      file.seek(startTime);
      file.write(tb.buffer.data.data() + tb.buffer.wrapIdx(startIdx),
                 tb.buffer.notWritten.size());
      file.error.log();
      tb.buffer.notWritten.in = tb.buffer.notWritten.out = tb.buffer.playIdx;
    }

    void readAudioFW() {
      uint startIdx = tb.buffer.playIdx + tb.buffer.lengthFW; 
      file.seek(tb.buffer.posAt0 + startIdx);
      uint nframes = desLength - tb.buffer.lengthFW;
      framebuf.clear();
      file.read(framebuf.data(), nframes);
      file.error.log();
      for (uint i = 0; i < nframes; i++) {
        // TODO: Read directly into buffer
        tb.buffer[startIdx + i] = framebuf[i];
      }
      tb.buffer.lengthFW += nframes;
      int overflow = tb.buffer.lengthFW + tb.buffer.lengthBW - TapeBuffer::RingBuffer::Size;
      if (overflow > 0) {
        tb.buffer.lengthBW -= overflow;
      }
    }

    void readAudioBW() {
      uint nframes = desLength - tb.buffer.lengthBW;
      int startIdx = tb.buffer.playIdx - tb.buffer.lengthBW - nframes; 
      file.seek(tb.buffer.posAt0 + startIdx);
      framebuf.clear();
      file.read(framebuf.data(), nframes);
      file.error.log();
      for (uint i = 0; i < nframes; i++) {
        tb.buffer[startIdx + i] = framebuf[i];
      }
      tb.buffer.lengthBW += nframes;
      int overflow = tb.buffer.lengthFW + tb.buffer.lengthBW - TapeBuffer::RingBuffer::Size;
      if (overflow > 0) {
        tb.buffer.lengthFW -= overflow;
      }
    }

    void maybeReadAllAudio() {
      if (tb.buffer.lengthFW < desLength - MinReadSize) {
        readAudioFW();
      }
      if (tb.buffer.lengthBW < desLength - MinReadSize) {
        readAudioBW(); 
      }
    }

    void maybeLiftToClipboard() {
      if (tb.clipboard.fromSlice.size() > 0) {
        LOGD << "Lifting " << tb.clipboard.fromSlice.size() << " frames from "
             << tb.clipboard.fromSlice.in;
        std::unique_lock<std::mutex> clipboardLock (tb.clipboard.lock);
        TapeBuffer::TapeSlice readSlice = {
          tb.clipboard.fromSlice.in,
          tb.clipboard.fromSlice.in
        };
        tb.clipboard.data.clear();
        framebuf.clear();
        while(readSlice.out < tb.clipboard.fromSlice.out) {
          readSlice.out = std::min<int>(readSlice.in + FrameBufSize,
                                        tb.clipboard.fromSlice.out);
          file.seek(readSlice.in);
          file.read(framebuf.data(), readSlice.size());
          for (int i = 0; i < readSlice.size(); i++) {
            tb.clipboard.data.push_back(framebuf[i][tb.clipboard.fromTrack.idx]);
            framebuf[i][tb.clipboard.fromTrack.idx] = 0;
          }
          file.seek(readSlice.in);
          file.write(framebuf.data(), readSlice.size());
          readSlice.in = readSlice.out;
        }
        tb.buffer.lengthFW = tb.buffer.lengthBW = 0;
        maybeReadAllAudio();
        tb.clipboard.fromSlice = {0,0};
      }
    }

    void maybeDropFromClipboard() {
      if (tb.clipboard.toTime >= 0 && !tb.clipboard.data.empty()) {
        std::unique_lock clipboardLock (tb.clipboard.lock);
        LOGD << "Dropping "   << tb.clipboard.data.size()
             << " frames at " << tb.clipboard.toTime;
        TapeBuffer::TapeSlice writeSlice = {
          tb.clipboard.toTime,
          tb.clipboard.toTime
        };
        while(true) {
          uint startIdx = writeSlice.in - tb.clipboard.toTime;
          writeSlice.out = writeSlice.in + std::min<int>(
            FrameBufSize, tb.clipboard.data.size() - startIdx);

          if ((ulong)writeSlice.size() > tb.clipboard.data.size()) break;
          if (writeSlice.size() == 0) break;

          framebuf.clear();
          file.seek(writeSlice.in);
          file.read(framebuf.data(), writeSlice.size());
          int i;
          for (i = 0; i < writeSlice.size(); i++) {
            framebuf[i][tb.clipboard.toTrack.idx] = tb.clipboard.data[startIdx + i];
          }
          LOGD << i;
          file.seek(writeSlice.in);
          file.write(framebuf.data(), writeSlice.size());
          writeSlice.in = writeSlice.out;
        }
        tb.buffer.lengthFW = tb.buffer.lengthBW = 0;
        maybeReadAllAudio();
        tb.clipboard.toTime = -1;
      }
    }

    void main() {

      // TODO: figure out why this is needed for GDB to not crash
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      tb.movePlaypointAbs(0);

      // FIXME: Hardcoded
      file.open("data/tape.wav");
      file.samplerate = Globals::samplerate;

      if (file.error.log()) Globals::exit();

      readSlices();

      while(Globals::running()) {
        std::unique_lock lock (file.mutex);

        if (tb.buffer.notWritten.size() > 4096) {
          writeNewAudio();
        }
        maybeReadAllAudio();

        maybeLiftToClipboard();
        maybeDropFromClipboard();

        tb.clipboard.done.notify_all();

        tb.readData.wait(lock);
      }

      file.close();
    }

    };

    /*******************************************/
    /*  TapeBuffer Implementation              */
    /*******************************************/

  TapeBuffer::TapeBuffer() : playPoint (0), newCuts (false) {}

  TapeBuffer::~TapeBuffer() {}

  void TapeBuffer::init() {
    diskThread = std::make_unique<TapeDiskThread>(*this);
  }

  void TapeBuffer::exit() {
    readData.notify_all();
    diskThread.reset();
  }

  // Disk handling:

    void TapeBuffer::threadRoutine() {
    }

    void TapeBuffer::movePlaypointRel(int time) {
      movePlaypointAbs(playPoint + time);
    }

    void TapeBuffer::movePlaypointAbs(int newPos) {
      std::unique_lock lock{diskThread->file.mutex};
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
    std::vector<TapeBuffer::AudioFrame> TapeBuffer::readFW(uint nframes) {
      uint n = std::min<int>(nframes, buffer.lengthFW);

      std::vector<AudioFrame> ret;

      for (uint i = 0; i < n; i++) {
        ret.push_back(buffer[buffer.playIdx + i]);
      }

      movePlaypointRel(n);

      return ret;
    }

    std::vector<TapeBuffer::AudioFrame> TapeBuffer::readBW(uint nframes) {
      uint n = std::min<int>(nframes, buffer.lengthBW);

      std::vector<AudioFrame> ret;

      for (uint i = 0; i < n; i++) {
        ret.push_back(buffer[buffer.playIdx - i]);
      }

      movePlaypointRel(-n);

      return ret;
    }

    uint TapeBuffer::writeFW(std::vector<AudioFrame> data,
                             uint offset,
                             std::function<AudioFrame(AudioFrame, AudioFrame)> writeFunc)
    {
      std::unique_lock lock{diskThread->file.mutex};
      int n = std::min<int>(data.size(), buffer.Size - buffer.lengthFW);

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
        std::min<int>(buffer.lengthFW, buffer.Size - buffer.lengthBW);

      return data.size() - n;
    }

    uint TapeBuffer::writeBW(std::vector<AudioFrame> data,
                           uint offset,
                           std::function<AudioFrame(AudioFrame, AudioFrame)> writeFunc)
  {
    std::unique_lock<std::recursive_mutex> lock (diskThread->file.mutex);
    int n = std::min<int>(data.size(), buffer.Size - buffer.lengthBW);

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
      std::min<int>(buffer.lengthBW, buffer.Size - buffer.lengthFW);

    return data.size() - n;
  }

  void TapeBuffer::goTo(TapeTime pos) {
    movePlaypointAbs(pos);
  }

  // Cuts & Slices
  std::vector<TapeBuffer::TapeSlice>
  TapeBuffer::TapeSliceSet::slicesIn(audio::Section<TapeTime> area) const {
    std::vector<TapeBuffer::TapeSlice> xs;
    if (slices.size() == 0) {
      return xs;
    }
    auto it = slices.upper_bound(area);
    if (it != slices.begin()) --it;
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
      case audio::Section<>::None:
        break;
      case audio::Section<>::Contains:
        slices.erase(s);
        break;
      case audio::Section<>::Contained:
        slices.erase(s);
        if (s.in != slice.in)
          slices.emplace(s.in, slice.in - 1);
        if (s.out != slice.out)
          slices.emplace(slice.out + 1, s.out);
        break;
      case audio::Section<>::ContainsIn:
        slices.erase(s);
        slices.emplace(slice.out + 1, s.out);
        break;
      case audio::Section<>::ContainsOut:
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

      void TapeBuffer::lift(Track track) {
        TapeSliceSet &tss = trackSlices[track.idx];
        if (!tss.inSlice(position())) {
          LOGD << "No slice to lift";
          return;
        }
        TapeSlice slice = tss.current(position());
        std::unique_lock<std::mutex> lock(clipboard.lock);
        clipboard.fromTrack = track;
        clipboard.fromSlice = slice;
        readData.notify_all();
        clipboard.done.wait(lock);
        tss.erase(slice);
      }

      void TapeBuffer::drop(Track track) {
        std::unique_lock<std::mutex> lock(clipboard.lock);
        clipboard.toTrack = track;
        clipboard.toTime = position();
        TapeSlice slice = {
          clipboard.toTime,
          clipboard.toTime + (int)clipboard.data.size()
        };
        readData.notify_all();
        clipboard.done.wait(lock);
    trackSlices[track.idx].addSlice(slice);
  }

  std::string TapeBuffer::timeStr() {
    double seconds = playPoint/(1.0 * Globals::samplerate);
    double minutes = seconds / 60.0;
    return fmt::format("{:0>2}:{:0>5.2f}", (int) minutes, fmod(seconds, 60.0));
  }

}
