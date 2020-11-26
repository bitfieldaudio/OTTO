#pragma once

/// Equal-power 2-channel panner (Stereo-to-Mono)
struct PanSM {
  /// \param[in] pos	Position, in [-1, 1]
  PanSM(float pos = 0)
  {
    this->pos(pos);
  }

  /// Filter sample (mono to stereo)
  float operator()(float position, float in1, float in2)
  {
    pos(position);
    return in1 * w1 + in2 * w2;
  }

  /// Filter sample (mono to stereo)
  float operator()(float in1, float in2)
  {
    return in1 * w1 + in2 * w2;
  }

  /// Set position (constant power law)
  /// \param[in] v	Position, in [-1, 1]
  void pos(float v)
  {
    static const float c0 = 1. / sqrt(2);
    static const float c1 = 0.5 - c0;
    static const float c2 = -0.5 / c1;
    v = gam::scl::clip(v, 1.f, -1.f);
    w1 = c1 * v * (v + c2) + c0;
    w1 *= vol1;

    w2 = w1 + v;
    w2 *= vol2;
  }

  void volume1(float v)
  {
    vol1 = v;
  }
  void volume2(float v)
  {
    vol2 = v;
  }

protected:
  float w1, w2; // channel weights
  float vol1 = 0.5;
  float vol2 = 0.5; // Channel volumes
};
