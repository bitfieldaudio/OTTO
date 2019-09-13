#pragma once

#include <gsl/span>
#include <vector>
#include <Gamma/Filter.h>

#include "services/log_manager.hpp"
#include "util/dyn-array.hpp"

namespace otto::core::audio {

  struct WaveformView;

  /// Multi-resolution waveform data
  ///
  /// Max size is size of input data.
  struct Waveform {
    Waveform() = default;
    Waveform(gsl::span<float> data, int min_points);

    /// Get a view of the waveform
    WaveformView view(int nPoints, int first, int last);

    /// Update a view with a new area.
    WaveformView& view(WaveformView& v, int first, int last);

  private:
    gsl::span<float> at_resolution(int res);

    int res_for_duration(int dur, int nPoints) const;

    void generate_res(int res);

    gsl::span<float> input_data_;
    /// res 0 is original resolution, 1 is 1/2, 2 is 1/4 etc.
    int max_res_;

    // The structure of this becomes
    // [ - - res=0 - - | - res=1 - | res=2 |.... ]
    // Each new sector is half the size of the previous
    util::dyn_array<float> points_ = {0};

    /// Frequency controls grainyness of waveform.
    gam::OnePole<> lpf{8000};
  };

  struct WaveformView {
    using iterator = std::vector<float>::const_iterator;

    auto begin() const noexcept
    {
      return points_.begin();
    }

    auto end() const noexcept
    {
      return points_.end();
    }

    auto operator[](int idx) const {
      OTTO_ASSERT(0 <= idx and idx < points_.size());
      return points_[idx];
    }

    auto size() const noexcept{
      return points_.size();
    }

    std::pair<float, float> point_for_time(int idx) const;

    iterator iter_for_time(int idx) const;

  private:
    WaveformView(Waveform&, int nPoints, int first, int last);

    friend Waveform;

    std::vector<float> points_;
    int start_;
    float step_;
  };

} // namespace otto::core::audio
