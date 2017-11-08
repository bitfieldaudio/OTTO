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

    util::audio::Section<float> radius_range = {2.f, 4.f};

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
    void range(Range r)
    {
      if (r != _range) {
        _range = r;
        point_cache.invalidate();
      }
    }

    float top_val() const {
      return _top_val;
    }

    void top_val(float v)
    {
      if (v != _top_val) {
        _top_val = v;
        point_cache.invalidate();
      }
    }

    /// Get the graphical point for an index
    vg::Point point(std::size_t index)
    {
      if (point_cache->points.size() == 0) return {0, size.h};
      return point_cache->points[std::clamp(
          std::size_t(std::floor(index / point_cache->smpl_pr_px
              / point_cache->radius / 2.f)),
          std::size_t(0),
          std::size_t(point_cache->points.size() - 1))];
    }

  private:

    /// packaged, cached data
    struct PointCache : util::cache_base<PointCache> {
      const Waveform& wf;
      float radius = wf.radius_range.middle();
      /// Samples pr px
      float smpl_pr_px = wf._range.size() / wf.size.w;
      /// Samples pr 2 * radius
      float sp2r;
      std::vector<vg::Point> points;

      PointCache(Waveform* wf)
        : wf (*wf)
      {}

    private:

      void refresh() override;

      /* Helper functions */

      /// Clamp value to container size
      std::size_t clamp(std::size_t) const;

    } point_cache {this};


    using point_iter = typename std::vector<vg::Point>::const_iterator;

    /// The range in samples of the full widget width
    Range _range = {0, 0};
    /// The value of the waveform at the top of the widget.
    /// Everything above this will be clipped
    float _top_val = 1.f;

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
    if (point_cache->points.size() == 0) return;
    roundedCurve(ctx,
      std::begin(point_cache->points),
      std::end(point_cache->points));
  }

  template<typename C>
  inline void Waveform<C>::draw_range(vg::Canvas& ctx, Range subrange)
  {
    if (point_cache->points.size() == 0) return;
    roundedCurve(ctx,
      std::begin(point_cache->points) + subrange.in / point_cache->sp2r,
      std::begin(point_cache->points) + subrange.out / point_cache->sp2r);
  }

  template<typename C>
  inline void Waveform<C>::roundedCurve(vg::Canvas& ctx, point_iter first, point_iter last)
  {
    if (first == last) return;

    ctx.moveTo(*first);
    for (auto [p1, p2] : util::adjacent_pairs(first, last))
    {
      float dx = std::abs(p2.x - p1.x);
      float dy = std::abs(p2.y - p1.y);
      float r = std::min({dx / 2.f, dy / 2.f, point_cache.radius});
      vg::Point md = (p1 + p2) / 2.0;
      vg::Point cp1 = {md.x, p1.y};
      vg::Point cp2 = md;
      vg::Point cp3 = {md.x, p2.y};

      ctx.arcTo(cp1, cp2, r);
      ctx.arcTo(cp3, p2, r);
    }
  }

  template<typename C>
  inline void Waveform<C>::PointCache::refresh()
  {
    float new_spp = wf._range.size() / wf.size.w;
    float ratio = smpl_pr_px / new_spp;
    float new_radius = radius * ratio;
    if (new_radius > wf.radius_range.out) {
      radius = wf.radius_range.in;
    } else if (new_radius < wf.radius_range.in) {
      radius = wf.radius_range.out;
    } else {
      radius = new_radius;
    }
    smpl_pr_px = new_spp;

    // Refresh the cache, but keep allocated memory
    points.clear();

    if (wf._range.size() == 0 || wf.container.size() == 0) {
      return;
    }

    sp2r = 2 * radius * smpl_pr_px;
    double error = 0.f;
    auto first = std::begin(wf.container);
    auto fidx = clamp(std::floor(wf._range.in / sp2r) * sp2r);
    auto lidx = clamp(std::ceil(wf._range.out / sp2r) * sp2r);
    auto iter = first + fidx;
    auto last = first + lidx;
    float start_x = (int(fidx) - int(wf._range.in)) / smpl_pr_px;
    for (int i = 0; iter != last; i++, iter++) {
      double intprt = 0;
      error = std::modf(error + sp2r, &intprt);

      // Average:
      float sum = 0.f;
      for (int j = 0; (j < intprt) && (iter != last); j++, iter++) {
        sum += std::abs(*iter);
      }
      float val = sum / intprt;

      points.emplace_back(
        start_x + i * 2 * radius,
        (1 - std::min(val / wf._top_val, 1.f)) * wf.size.h);
      // Required, as iter might otherwise be incremented twice with no check
      if (iter == last) break;
    }

    // Align points if they are too close
    for (auto [cur, nxt] : util::adjacent_pairs(points)) {
      float dx = std::abs(nxt.x - cur.x);
      float dy = std::abs(nxt.y - cur.y);
      if (dx < radius || dy < radius) {
        nxt.y = cur.y;
      }
    }

    // Move first and last points to edges
    if (!points.empty()) {
      points.front().x = 0.f;
      points.back().x = wf.size.w;
    }
  }

  template<typename C>
  inline std::size_t Waveform<C>::PointCache::clamp(std::size_t val) const {
    return std::clamp(val, std::size_t{0}, wf.container.size());
  };

}
