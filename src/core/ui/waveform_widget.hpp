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
      if (point_cache->size() == 0) return {0, size.h};
      return point_cache.value()[std::clamp(int(std::round(index / smpl_pr_px / radius)),
          0, int(point_cache->size() - 1))];
    }

  private:

    /// Cache of points
    util::cached<std::vector<vg::Point>> point_cache = [this] (auto& cache)
      {
        // clamp to container size
        auto clamp = [&] (std::size_t val) {
            return std::clamp(val, std::size_t{0}, container.size());
          };

        // Refresh the cache, but keep allocated memory
        cache.clear();

        if (_range.size() == 0 || container.size() == 0) {
          return;
        }
        smpl_pr_px = _range.size() / size.w;

        double error = 0.f;
        auto iter = std::begin(container) + clamp(_range.in);
        auto last = std::begin(container) + clamp(_range.out);
        for (int i = 0; iter != last; i++, iter++)
        {
          double intprt = 0;
          error = std::modf(error + 2 * radius * smpl_pr_px, &intprt);

          // Average:
          // float sum = 0.f;
          // for (int j = 0; (j < intprt) && (iter != last); j++, iter++) {
          //   sum += std::abs(*iter);
          // }
          // float val = sum / intprt;

          // Max:
          float max = 0.f;
          for (int j = 0; (j < intprt) && (iter != last); j++, iter++) {
            max = std::max(max, std::abs(*iter));
          }
          float val = max;

          cache.emplace_back(i * 2 * radius, (1 - val) * size.h);
          // Required, as iter might otherwise be incremented twice with no check
          if (iter == last) break;
        }

        LOGD << "Refreshed waveform cache";
        LOGD << "Cache size: " << cache.size();

      };

    using point_iter = typename std::vector<vg::Point>::const_iterator;

    /// The range in samples of the full widget width
    Range _range = {0, 0};
    /// The value of the waveform at the top of the widget.
    /// Everything above this will be clipped
    float _top_val = 1.f;
    /// Sound length / pixel width
    float smpl_pr_px;

    /// The radius of the curves
    float radius = 3.f;

    const Container& container;


    /// Draw a curve between points using only horizontal and vertical lines and
    /// rounded corners
    ///
    /// This is the algorithm used by the samplers, and in general to display waveforms
    ///
    /// \param first An iterator to the first point
    /// \param last An iterator one past the last point
    /// \param maxR The maximum radius for curves, in pixels. If negative, there
    ///             is no limit
    /// \requires `It` shall be an `InputIterator<Point>`
    void roundedCurve(vg::Canvas& ctx, point_iter first, point_iter last);

  };

  // Implementation ///////////////////////////////////////////////////////////

  template<typename C>
  inline void Waveform<C>::draw(vg::Canvas& ctx)
  {
    if (point_cache->size() == 0) return;
    roundedCurve(ctx,
      std::begin(point_cache.value()),
      std::end(point_cache.value()));
  }

  template<typename C>
  inline void Waveform<C>::roundedCurve(vg::Canvas& ctx, point_iter first, point_iter last)
  {
    if (first == last) return;

    vg::Point cur = *first;
    vg::Point nxt = cur;
    first++;

    ctx.moveTo(cur);
    for (; first != last; ++first) {
      nxt = *first;
      float dx = std::abs(nxt.x - cur.x);
      float dy = std::abs(nxt.y - cur.y);
      float r = radius;
      if (first + 2 < last) {
        // Skip a point if they are too close
        if (dx < radius * 2 || dy < radius * 2) continue;
      } else {
        // But allways draw the last one
        r = std::min(dx, dy);
      }
      vg::Point md = (cur + nxt) / 2.0;
      vg::Point cp1 = {md.x, cur.y};
      vg::Point cp2 = md;
      vg::Point cp3 = {md.x, nxt.y};

      ctx.arcTo(cp1, cp2, r);
      ctx.arcTo(cp3, nxt, r);
      cur = nxt;
    }
  }

  template<typename C>
  inline void Waveform<C>::draw_range(vg::Canvas& ctx, Range subrange)
  {
    if (point_cache->size() == 0) return;
    roundedCurve(ctx,
      std::begin(point_cache.value()) + subrange.in / smpl_pr_px,
      std::begin(point_cache.value()) + subrange.out / smpl_pr_px);
  }
}
