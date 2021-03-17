#pragma once

namespace otto::util {

  struct fastrand_in_range {
    fastrand_in_range(unsigned int seed) : g_seed(seed) {}

    inline int operator()(unsigned int n)
    {
      g_seed = (214013 * g_seed + 2531011);
      return ((g_seed >> 16) & 0x7FFF) % n;
    }

  private:
    unsigned int g_seed;
  };

}; // namespace otto::util