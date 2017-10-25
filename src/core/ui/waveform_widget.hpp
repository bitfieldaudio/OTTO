#pragma once

#include "core/ui/drawing.hpp"
#include "core/ui/base.hpp"
#include "util/audio.hpp"
#include "util/cache.hpp"
#include "util/algorithm.hpp"

namespace otto::ui::widgets {

  /// Draws a waveform from data.
  template<typename Container>
  struct Waveform : Widget {
    using Range = util::audio::Section<int>;
    /// The value of the waveform at the top of the widget.
    /// Everything above this will be clipped
    float top_val;

    /// Draw the entire waveform
    void draw(vg::Canvas&);

    /// Draw a subset of the waveform.
    ///
    /// Useful for colouring different parts differently
    void draw_range(vg::Canvas&, Range);

  private:

    /// Cache of points
    util::cached<std::vector<vg::Point>> point_cache = [this] (auto& cache) {
      auto iter = std::begin(c) + range.in;
      float max;
      smpl_pr_px = range.size() / size.w;
      for (int i = 0; i < range.size(); i++, iter++) {
        max = std::max(max, std::abs(*iter));
        if (std::fmod(i + 1, smpl_pr_px)) {
          cache.emplace_back(i * smpl_pr_px,
            std::min(max / top_val, top_val) * size.h);
          max = 0;
        }
      }
    };

    /// Sound length / pixel width
    float smpl_pr_px;
    /// The range in samples of the full widget width
    Range range;
    Container& c;
  };

  // Implementation ///////////////////////////////////////////////////////////

  template<typename C>
  inline void Waveform<C>::draw(vg::Canvas& ctx)
  {
    ctx.roundedCurve(
      std::begin(point_cache.value()),
      std::end(point_cache.value()));
  }

  template<typename C>
  inline void Waveform<C>::draw_range(vg::Canvas& ctx, Range subrange)
  {
    ctx.roundedCurve(
      std::begin(point_cache.value()),
      std::end(point_cache.value()));
  }
}
