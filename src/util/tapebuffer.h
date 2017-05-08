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
#include <fmt/format.h>
#include "../utils.h"

typedef int TapeTime;

/**
 * A Wrapper for ringbuffers, used for the tapemodule.
 */
class TapeBuffer {
public:
  typedef Section<TapeTime> TapeSlice;
  class CompareTapeSlice {
  public:
    bool operator()(TapeSlice e1, TapeSlice e2) {return e1.in < e2.in;}
  };


  struct TapeCut {
    class Compare {
    public:
      bool operator()(TapeCut e1, TapeCut e2) {return e1.pos < e2.pos;}
    };
    enum TapeCutType {
      NONE = 0,
      IN,
      OUT,
      SPLIT,
    };
    TapeTime pos;
    TapeCutType type;

    bool operator<  (TapeCut other) {return pos <  other.pos;}
    bool operator>  (TapeCut other) {return pos >  other.pos;}
    bool operator<= (TapeCut other) {return pos <= other.pos;}
    bool operator>= (TapeCut other) {return pos >= other.pos;}
  };

  class TapeCuts {
    std::set<TapeCut, TapeCut::Compare> data;
    std::set<TapeSlice, CompareTapeSlice> cache;
  public:

    void reCache();
    std::vector<TapeSlice> slicesIn(Section<TapeTime> area);
    std::vector<TapeCut> cutsIn(Section<TapeTime> area);

    bool inSlice(TapeTime time);
    TapeSlice current(TapeTime time);
    TapeCut nearest(TapeTime time);

    void cut(TapeCut cut);
    void glue(TapeTime time);

    void addSlice(TapeSlice slice);

    // Iteration
    auto begin() { return data.begin(); }
    auto end() { return data.end(); }
  };
protected:
  const static int MIN_READ_SIZE = 2048;

  /** The current position on the tape, counted in frames from the beginning*/
  std::atomic_uint playPoint;


  std::thread diskThread;
  std::mutex threadLock;
  std::condition_variable readData;

  TapeCuts cuts[4];

  std::atomic_bool newCuts;

  void threadRoutine();

  void movePlaypointRel(int time);

  void movePlaypointAbs(int pos);

public:

  struct RingBuffer {
    const static uint SIZE = 262144; // 2^18
    std::array<AudioFrame, SIZE> data;
    Section<int> notWritten;
    int lengthFW = 0;
    int lengthBW = 0;
    uint playIdx = 0;
    uint posAt0 = 0;

    AudioFrame& operator[](int i) {
      return data[wrapIdx(i)];
    }

    uint wrapIdx(int index) {
      return ((index %= SIZE) < 0) ? SIZE + index : index;
    }

  } buffer;

  const static uint nTracks = 4;

  TapeBuffer();

  /**
   * Reads forwards along the tape, moving the playPoint.
   * @param nframes number of frames to read.
   * @param track track to read from
   * @return a vector of length nframes with the data.
   */
  std::vector<float> readFW(uint nframes, uint track);
  std::vector<AudioFrame> readAllFW(uint nframes);

  /**
   * Reads backwards along the tape, moving the playPoint.
   * @param nframes number of frames to read.
   * @param track track to read from
   * @return a vector of length nframes with the data. The data will be in the
   *        read order, meaning reverse.
   */
  std::vector<float> readBW(uint nframes, uint track);
  std::vector<AudioFrame> readAllBW(uint nframes);

  /**
   * Write data to the tape.
   * NB: The data will be written at playPoint - data.size(), meaning the end of
   * the data will be written at the current playPoint.
   * @param data the data to write. data.back() will be at playPoint - 1
   * @param track the track to write to
   * @param slice this slice will be extended by this recorded data
   * @return the amount of unwritten frames
   */
  uint writeFW(std::vector<float> data, uint track, TapeSlice &slice);

  /**
   * Write data to the tape.
   * NB: The data will be written beginning at playPoint
   * @param data the data to write, in reverse order. data.back() will be at
   *          playPoint, data.front() will be at playPoint + data.size();
   * @param track the track to write to
   * @param slice this slice will be extended by this recorded data
   * @return the amount of unwritten frames
   */
  uint writeBW(std::vector<float> data, uint track, TapeSlice &slice);

  /**
   * Jumps to another position in the tape
   * @param tapePos position to jump to
   */
  void goTo(TapeTime tapePos);

  TapeTime position() {
    return playPoint;
  }

  std::string timeStr() {
    double seconds = playPoint/(1.0 * 44100);
    double minutes = seconds / 60.0;
    return fmt::format("{:0>2}:{:0>5.2f}", (int) minutes, fmod(seconds, 60.0));
  }

  // Tape Slices

  bool inSlice(int track);

  TapeSlice currentSlice(int track);

  std::vector<TapeSlice> slicesIn(Section<TapeTime> area, int track);

  std::vector<TapeCut> cutsIn(Section<TapeTime> area, int track);

  void cutTape(int track);

  void addSlice(TapeSlice slice, int track) { cuts[track-1].addSlice(slice); }

};
