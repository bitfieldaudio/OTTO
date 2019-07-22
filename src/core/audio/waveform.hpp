#pragma once

#include <gsl/span>
#include <vector>

#include "services/log_manager.hpp"
#include "util/dyn-array.hpp"

namespace otto::core::audio {

  /// Multi-resolution waveform data
  ///
  /// Max size is size of input data.
  struct Waveform {
    Waveform(gsl::span<float> data, int min_points);

    template<typename Func>
    void for_points(int nPoints, std::size_t first, std::size_t last, Func&& f);

    gsl::span<float> at_resolution(int res);

    int res_for_duration(std::size_t dur, int nPoints) const;

  private:
    void generate_res(int res);

    gsl::span<float> input_data_;
    /// res 0 is original resolution, 1 is 1/2, 2 is 1/4 etc.
    int max_res_;
    util::dyn_array<float> points_;
  };

  template<typename Func>
  void Waveform::for_points(int nPoints, std::size_t first, std::size_t last, Func&& f)
  {
    OTTO_ASSERT(last >= first);
    int res = res_for_duration(last - first, nPoints);
    auto data = at_resolution(res);
    float stride = (last - first) / float(nPoints) / (float(input_data_.size()) / float(data.size()));
    float idx = 0;
    if (stride > 1) {
      for (int i = 0; i < nPoints; i++) {
        int j = 0;
        float max = 0;
        for (; j < stride; j++) {
          max = std::max(data[std::min(std::size_t(first + idx), last)], max);
        }
        f(max);
        idx += stride;
      }
    } else {
      for (int i = 0; i < nPoints; i++) {
        f(data[std::min(std::size_t(first + idx), last)]);
        idx += stride;
      }
    }
  }

} // namespace otto::core::audio
