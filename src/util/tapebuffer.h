#pragma once

#include <cstdlib>
#include <atomic>
#include <vector>
#include <array>
#include <set>
#include <iterator>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <fmt/format.h>
#include "../utils.h"
#include <plog/Log.h>

namespace top1 {
typedef int TapeTime;

/**
 * A Wrapper for ringbuffers, used for the tapemodule.
 */
class TapeBuffer {
public:
  typedef Section<TapeTime> TapeSlice;
  class CompareTapeSlice {
  public:
    bool operator()(const TapeSlice &e1, const TapeSlice &e2) const {return e1.in < e2.in;}
  };

  class TapeSliceSet {
    std::set<TapeSlice, CompareTapeSlice> slices;
  public:
    bool changed = false;
    TapeSliceSet() {}
    std::vector<TapeSlice> slicesIn(Section<TapeTime> area) const;

    bool inSlice(TapeTime time) const;
    TapeSlice current(TapeTime time) const;

    void addSlice(TapeSlice slice);
    void erase(TapeSlice slice);

    void cut(TapeTime time);
    void glue(TapeSlice s1, TapeSlice s2);

    // Iteration
    auto begin() { return slices.begin(); }
    auto end() { return slices.end(); }
    auto size() { return slices.size(); }
  };
protected:
  const static int MIN_READ_SIZE = 2048;

  /** The current position on the tape, counted in frames from the beginning*/
  std::atomic_uint playPoint;


  std::thread diskThread;
  std::recursive_mutex threadLock;
  std::condition_variable_any readData;

  std::atomic_bool newCuts;

  void threadRoutine();

  void movePlaypointRel(int time);

  void movePlaypointAbs(int pos);

  struct {
    std::vector<float> data;
    uint fromTrack = 0;
    TapeSlice fromSlice = {-1, -2};
    uint toTrack = 0;
    TapeTime toTime = -1;
    std::mutex lock;
    std::condition_variable done;
  } clipboard;

public:

  struct RingBuffer {
    const static uint SIZE = 262144; // 2^18
    std::array<AudioFrame, SIZE> data;
    Section<int> notWritten;
    std::atomic_int lengthFW = {0};
    std::atomic_int lengthBW = {0};
    std::atomic_uint playIdx = {0};
    std::atomic_uint posAt0 = {0};

    AudioFrame& operator[](int i) {
      return data[wrapIdx(i)];
    }

    uint wrapIdx(int index) {
      return ((index %= SIZE) < 0) ? SIZE + index : index;
    }

  } buffer;

  TapeSliceSet trackSlices[4] = {{}, {}, {}, {}};

  const static uint nTracks = 4;

  TapeBuffer();

  void init();
  void exit();

  /**
   * Reads forwards along the tape, moving the playPoint.
   * @param nframes number of frames to read.
   * @return a vector of length nframes with the data.
   */
  std::vector<AudioFrame> readFW(uint nframes);

  /**
   * Reads backwards along the tape, moving the playPoint.
   * @param nframes number of frames to read.
   * @return a vector of length nframes with the data. The data will be in the
   *        read order, meaning reverse.
   */
  std::vector<AudioFrame> readBW(uint nframes);

  /**
   * Write data to the tape.
   * @param data the data to write.
   * @param offset the end of the data will be at playPoint - offset
   * @param writeFunc the function used to write the data. Run for each frame,
   *   recieves the original and the new data as arguments.
   * @return the amount of unwritten frames
   */
  uint writeFW(
    std::vector<AudioFrame> data,
    uint offset = 0,
    std::function<AudioFrame(AudioFrame, AudioFrame)> writeFunc
      = [](AudioFrame o, AudioFrame n) { return n; });

  /**
   * Write data to the tape.
   * @param data the data to write. Will be written in reverse order.
   * @param offset the end of the data will be at playPoint + offset
   * @param writeFunc the function used to write the data. Run for each frame,
   *   recieves the original and the new data as arguments.
   * @return the amount of unwritten frames
   */
  uint writeBW(
    std::vector<AudioFrame> data,
    uint offset = 0,
    std::function<AudioFrame(AudioFrame, AudioFrame)> writeFunc
    = [](AudioFrame o, AudioFrame n) { return n; });

  /**
   * Jumps to another position in the tape
   * @param tapePos position to jump to
   */
  void goTo(TapeTime tapePos);

  TapeTime position() {
    return playPoint;
  }

  void lift(uint track);
  void drop(uint track);

  std::string timeStr() {
    double seconds = playPoint/(1.0 * 44100);
    double minutes = seconds / 60.0;
    return fmt::format("{:0>2}:{:0>5.2f}", (int) minutes, fmod(seconds, 60.0));
  }

};
}
