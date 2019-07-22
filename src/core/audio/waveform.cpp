#include "waveform.hpp"

#include "util/iterator.hpp"

#include <Gamma/Analysis.h>

namespace otto::core::audio {

  Waveform::Waveform(gsl::span<float> data, int min_points)
    : input_data_(data),
      max_res_(std::floor(std::log(data.size() / min_points))),
      // points_(data.size() * (2 - std::pow(2, -max_res_)))
      points_(data.size() * max_res_)
  {
    for (int i = 0; i < max_res_; i++) {
    }
    generate_res(0);
  }

  gsl::span<float> Waveform::at_resolution(int res)
  {
    // std::size_t start = std::ceil(input_data_.size() * (1.f - std::pow(2.f, -float(res - 1.f))));
    // std::size_t length = std::ceil(input_data_.size() * std::pow(2.f, -float(res)));
    // return {points_.data() + start, length};

    // return {points_.data() + input_data_.size() * res, input_data_.size()};
    return {points_.data(), std::ceil(float(input_data_.size()) / 30.f)};
  }

  void Waveform::generate_res(int res)
  {
    auto data = at_resolution(res);

    // EnvelopFollower
    // float f = 0;
    // for (auto&& [src, dst] : util::zip(input_data_, data)) {
    //   float f0 = std::abs(src);
    //   if (f0 > f) {
    //     f = f0;
    //   } else {
    //     f -= (f - f0) / (10 * float(std::pow(2, res * res)));
    //   }
    //   dst = f;
    // }

    // 1. abs
    // 2. bin
    // 3. all elements in bin = max of bin
    auto src = input_data_.cbegin();
    auto dst = data.begin();
    int rem = input_data_.size();
    const auto bin_size = 30;
    while (rem > 0) {
      auto len = std::min(bin_size, rem);
      float max = 0.f;
      for (int i = 0; i < len; i++) {
        auto f = std::abs(src[i]);
        max = std::max(f, max);
      }
      *dst = max;
      rem -= len;
      src += len;
      dst++;
    }
    // 4. lpf
    // gam::OnePole<> lpf = {10};
    // for (auto& f : data) {
    //   f = lpf(f);
    // }
  }

  int Waveform::res_for_duration(std::size_t dur, int nPoints) const
  {
    if (dur == 0) return 0;
    return std::floor(std::log(dur / float(nPoints)));
  }
} // namespace otto::core::audio
