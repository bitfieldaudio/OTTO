#pragma once

#include <cstdlib>
#include <vector>

/**
 * A bidirectional ringbuffer, used for the tapemodule.
 */
class TapeBuffer {
public:

  /** The current position on the tape, counted in frames from the beginning*/
  uint playPoint;

  /**
   * Reads forwards along the tape, moving the playPoint.
   * @param nframes number of frames to read.
   * @param track track to read from
   * @return a vector of length nframes with the data.
   */
  std::vector<float> readFW(uint nframes, uint track);

  /**
   * Reads backwards along the tape, moving the playPoint.
   * @param nframes number of frames to read.
   * @param track track to read from
   * @return a vector of length nframes with the data. The data will be in the
   *        read order, meaning reverse.
   */
  std::vector<float> readBW(uint nframes, uint track);

  /**
   * Write data to the tape.
   * NB: The data will be written at playPoint - data.size(), meaning the end of
   * the data will be written at the current playPoint.
   * @param data the data to write. data[data.size()-1] will be at playPoint - 1
   * @param track the track to write to
   */
  void writeFW(std::vector<float> data, uint track);

  /**
   * Write data to the tape.
   * NB: The data will be written beginning at playPoint
   * @param data the data to write. data[0] will be at playPoint
   * @param track the track to write to
   */
  void writeBW(std::vector<float> data, uint track);

  /**
   * Jumps to another position in the tape
   * @param tapePos position to jump to
   */
  void goTo(uint tapePos);

};
