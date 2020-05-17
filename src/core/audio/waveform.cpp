#include "waveform.hpp"

#include "util/iterator.hpp"
#include "util/algorithm.hpp"

#include <Gamma/Analysis.h>

namespace otto::core::audio {

  Waveform::Waveform(gsl::span<float> data, int min_points)
    : input_data_(data),
      max_res_(std::floor(std::log(data.size() / min_points))),
      points_(data.size() * (2 - std::pow(2, -max_res_)))
  {
    DLOGI("Maximum resolution is = {}", max_res_);
    DLOGI("File size: {}", input_data_.size());
    for (int i = 0; i <= max_res_; i++) {
      DLOGI("Generating res = {}", i);
      generate_res(i);
    }
    DLOGI("Done generating");
  }

  gsl::span<float> Waveform::at_resolution(int res)
  {
    // int start = std::ceil(input_data_.size() * (1.f - std::pow(2.f, -float(res - 1.f))));
    // int length = std::ceil(input_data_.size() * std::pow(2.f, -float(res)));
    // return {points_.data() + start, length};

    // return {points_.data() + input_data_.size() * res, input_data_.size()};
    //return {points_.data(), std::ceil(float(input_data_.size()) / float(bin_size))};

    //NOTE: I have changed ceil to floor, to 
    // Calculate start-point in points_.
    // The result of the sum over: input_data_.size()*2^(-n), for n=0 to n=res
    int start = std::ceil(input_data_.size() * (2 - std::pow(2.f, 1-float(res))));
    // Calculate number of points at a certain resolution
    int length = std::ceil(input_data_.size() * std::pow(2.f, -float(res)));
    DLOGI("start: {}, length: {}", start, length);
    return {points_.data() + start, (std::size_t) length};
  }

  void Waveform::generate_res(int res) {
    // Get the span in which to put the points
    auto data = at_resolution(res);
    auto dst = data.begin();

    if (res == 0) {
      // Res=0 is special.
      nano::transform(input_data_, dst, [](float f){return std::abs(f);} );

    } else {
      // For all other resolutions, the source of data is the previous resolution
      auto src_data = at_resolution(res - 1);
      auto src = src_data.begin();
      // Pick out every second point
      *dst = *src;
      while (src < src_data.end()-2) {
        dst++;
        src += 2;
        *dst = *src;
      }
      DLOGI("Done.");
      // Low-pass filter the result.
      // Do it forwards and backwards to get zero phase twists.
      
      for (auto &f : data) {
        f = lpf(f);
      }
      lpf.zero();
      for (auto f = data.rbegin(); f != data.rend(); ++f) {
        *f = lpf(*f);
      }
      

    }
    
  }

  int Waveform::res_for_duration(int dur, int nPoints) const
  {
    if (dur == 0) return 0;
    // The max is to be safe against when dur < nPoints
    return std::max(std::floor(std::log(dur / float(nPoints))),0.f);

    // Highest integer n such that
    //dur > nPoints * n
    // Then
    //res = n-1
    // But 0 =< res
    //return std::max(int(std::floor(dur / float(nPoints)) - 1), 0);

  }


  WaveformView Waveform::view(int nPoints, int first, int last)
  {
    return {*this, nPoints, first, last};
  }

  WaveformView& Waveform::view(WaveformView& v, int first, int last)
  {
    if (points_.size() == 0) {
      nano::fill(v.points_, 0);
      return v;
    }
    DLOGI("Calculating view");
    // nPoints is the number of points we want, e.g. 260 or 300
    auto nPoints = v.size();
    v.points_.clear();

    OTTO_ASSERT(last >= first);

    int res = res_for_duration(last - first, nPoints);
    auto data = at_resolution(res);

    // nDataPoints is how many samples there are in the resolution
    // we have been given. This might be every fourth sample in the original audiofile
    auto nDataPoints = data.size();

    v.start_ = float(first) / float(input_data_.size()) * nDataPoints;
    v.step_ = (last - first) / float(input_data_.size()) * nDataPoints / float(nPoints);

    DLOGI("Calculating view now: {}", res);
    for (int i = 0; i < nPoints; i++) {
      // float max = data[std::min(int(first + idx), last) / bin_size];
      // for (int j = 1; j < v.step_; j++) {
      //   max = std::max(data[std::min(int(first + idx), last) / bin_size], max);
      // }
      // v.points_.push_back(max);
      //TODO: Benchmark difference between start, mean, max.
      //float sum = data[std::min(int(first + idx), last)];
      //for (int j = 1; j < v.step_; j++) {
      //  sum += data[std::min(int(first + idx + j), last)];
        //DLOGI("{}",j);
      //}
      //v.points_.push_back(sum / std::ceil(v.step_));
      //idx += v.step_;

      //For now, just take the first valid point in the resolution
      int pos = std::floor(v.start_ + i * v.step_);
      v.points_.push_back( data[pos] );

    }
    DLOGI("Returning view");
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
