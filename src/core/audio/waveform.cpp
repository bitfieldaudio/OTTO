#include "waveform.hpp"

#include "util/iterator.hpp"
#include "util/algorithm.hpp"

#include <Gamma/Analysis.h>

namespace otto::core::audio {

  constexpr int bin_size = 30;

  Waveform::Waveform(gsl::span<float> data, int min_points)
    : input_data_(data),
      max_res_(std::floor(std::log(data.size() / min_points))),
      // points_(data.size() * (2 - std::pow(2, -max_res_)))
      points_(data.size())
  {
    for (int i = 0; i < max_res_; i++) {
    }
    generate_res(0);
  }

  gsl::span<float> Waveform::at_resolution(int res)
  {
    // int start = std::ceil(input_data_.size() * (1.f - std::pow(2.f, -float(res - 1.f))));
    // int length = std::ceil(input_data_.size() * std::pow(2.f, -float(res)));
    // return {points_.data() + start, length};

    // return {points_.data() + input_data_.size() * res, input_data_.size()};
    //return {points_.data(), std::ceil(float(input_data_.size()) / float(bin_size))};
    return {points_.data(), input_data_.size()};
  }

  void Waveform::generate_res(int res) {
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
    while (rem > 0) {
      auto len = std::min(bin_size, rem);
      float max = 0.f;
      for (int i = 0; i < len; i++) {
        auto f = std::abs(src[i]);
        max = std::max(f, max);
      }
      for (int i = 0; i < len; i++) {
        *dst = max;
        dst++;
      }
      rem -= len;
      src += len;

    }
    // 4. lpf
    // Do it forwards and backwards to get zero phase twists.
    for (auto &f : data) {
      f = lpf(f);
    }
    lpf.zero();
    for (auto f = data.rbegin(); f != data.rend(); ++f) {
      *f = lpf(*f);
    }
  }

  int Waveform::res_for_duration(int dur, int nPoints) const
  {
    if (dur == 0) return 0;
    return std::floor(std::log(dur / float(nPoints)));
  }


  WaveformView Waveform::view(int nPoints, int first, int last)
  {
    return {*this, nPoints, first, last};
  }

  WaveformView& Waveform::view(WaveformView& v, int first, int last)
  {
    if (points_.size() == 0) {
      util::fill(v.points_, 0);
      return v;
    }
    auto nPoints = v.size();
    v.points_.clear();
    OTTO_ASSERT(last >= first);
    int res = res_for_duration(last - first, nPoints);
    auto data = at_resolution(res);
    v.start_ = first;
    v.step_ = (last - first) / float(nPoints);
    float idx = 0;
    for (int i = 0; i < nPoints; i++) {
      // float max = data[std::min(int(first + idx), last) / bin_size];
      // for (int j = 1; j < v.step_; j++) {
      //   max = std::max(data[std::min(int(first + idx), last) / bin_size], max);
      // }
      // v.points_.push_back(max);
      float sum = data[std::min(int(first + idx), last)];
      for (int j = 1; j < v.step_; j++) {
        sum += data[std::min(int(first + idx + j), last)];
        //DLOGI("{}",j);
      }
      v.points_.push_back(sum / std::ceil(v.step_));
      idx += v.step_;
    }
    return v;
  }

  WaveformView::WaveformView(Waveform& wf, int nPoints, int first, int last)
  {
    points_.resize(nPoints, 0);
    wf.view(*this, first, last);
  }

  auto WaveformView::point_for_time(int time) const -> std::pair<float, float> {
    auto idx = (time - start_) / step_;
    if (idx < 0) return {0, points_.front()};
    else if (idx >= points_.size()) return {size() - 1, points_.back()};
    return {idx, points_[idx]};
  }

  auto WaveformView::iter_for_time(int time) const -> iterator {
    auto idx = (time - start_) / step_;
    if (idx < 0) return begin();
    else if (idx >= points_.size()) return end() - 1;
    return begin() + idx;
  }
} // namespace otto::core::audio
