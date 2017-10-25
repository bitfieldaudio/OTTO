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
    using Range = util::audio::Section<std::size_t>;


    Waveform(const Container& cont, vg::Size s, float top_val = 1.f)
      : Widget {s},
        _top_val {top_val},
        container {cont}
    {}

    /// Draw the entire waveform
    void draw(vg::Canvas&);

    /// Draw a subset of the waveform.
    ///
    /// Useful for colouring different parts differently.
    ///
    /// \param subrange
    ///        The range to draw, with 0 at `[*Waveform<C>::range]().in`
    ///
    /// \expects `subrange` should be within [*Waveform<C>::range]() -
    /// `range.in`
    void draw_range(vg::Canvas&, Range subrange);

    /// The viewed range. Start and end indexes into the container coresponding
    /// to left/right edges of the widget
    Range range() const {
      return _range;
    }

    /// Set the viewed range
    ///
    /// Invalidates the cache if the new value is different from the old
    void range(Range r) {
      if (r != _range) {
        _range = r;
        point_cache.invalidate();
      }
    }

    float top_val() const {
      return _top_val;
    }

    void top_val(float v) {
      if (v != _top_val) {
        _top_val = v;
        point_cache.invalidate();
      }
    }

    /// Get the graphical point for an index
    vg::Point point(std::size_t index)
    {
      return point_cache.value()[index / smpl_pr_px];
    }

  private:

    /// Cache of points
    util::cached<std::vector<vg::Point>> point_cache = [this] (auto& cache) {
        // Refresh the cache
        cache.clear();
        if (_range.size() <= 0) {
          return;
        }
        auto iter = std::begin(container) + _range.in;
        float max;
        smpl_pr_px = _range.size() / size.w;
        float err = 0.f;
        for (int i = 0; i < _range.size(); i++, iter++) {
          max = std::max(max, std::abs(*iter));
          double intprt;
          err = std::modf(err + std::fmod(i + 1, smpl_pr_px), &intprt);
          if (intprt == 0) {
            cache.emplace_back(i / smpl_pr_px,
              0);
            max = 0;
          }
        }
        LOGD << "Refreshing waveform cache";
        LOGD << "cache size: " << cache.size();
      };

    /// The range in samples of the full widget width
    Range _range;
    /// The value of the waveform at the top of the widget.
    /// Everything above this will be clipped
    float _top_val;
    /// Sound length / pixel width
    float smpl_pr_px;

    const Container& container;
  };

  // Implementation ///////////////////////////////////////////////////////////

  template<typename C>
  inline void Waveform<C>::draw(vg::Canvas& ctx)
  {
    LOGD << "range size:   " << _range.size();
    LOGD << "widget width: " << size.w;
    LOGD << "smpl_pr_px:   " << smpl_pr_px;
    LOGD << "Cache size:   " << point_cache.value().size();
    LOGD << "Cache width:  " << -(point_cache.value().front() - point_cache.value().back()).x;
    ctx.roundedCurve(
      std::begin(point_cache.value()),
      std::end(point_cache.value()));
  }

  template<typename C>
  inline void Waveform<C>::draw_range(vg::Canvas& ctx, Range subrange)
  {
    LOGD << "range size:   " << _range.size();
    LOGD << "widget width: " << size.w;
    LOGD << "smpl_pr_px:   " << smpl_pr_px;
    LOGD << "Adjusted in:  " << subrange.in / smpl_pr_px;
    LOGD << "Adjusted out: " << subrange.out / smpl_pr_px;
    ctx.roundedCurve(
      std::begin(point_cache.value()) + subrange.in / smpl_pr_px,
      std::begin(point_cache.value()) + subrange.out / smpl_pr_px);
  }
}
