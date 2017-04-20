#pragma once

#include <cstdlib>

enum TapeDirection {
  DIR_FW,
  DIR_BW
};

/**
 * A bidirectional ringbuffer, used for the tapemodule.
 */
class TapeBuffer {
public:
  const static uint SIZE = 2^24;

  uint read(
    uint nframes, float *dest,
    TapeDirection dir = DIR_FW,
    double speed = 1.0);

  uint write(
    uint nframes, float *src,
    TapeDirection dir = DIR_FW,
    double speed = 1.0);

  uint goAbs(uint tapePos);

  uint goRel(int amount);

protected:
  float data[SIZE];
  uint dataPos;

  uint tapePosition;

};
