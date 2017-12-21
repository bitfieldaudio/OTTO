#pragma once

#include "core/ui/drawing.hpp"
#include "core/ui/widget.hpp"
#include "util/audio.hpp"
#include "util/cache.hpp"
#include "util/algorithm.hpp"

namespace otto::ui::widgets {

  /// Draws a waveform from data.
  template<typename Container>
  struct Waveform : Widget {
    using Range = util::audio::Section<int>;

    util::audio::Section<float> radius_range = {2.f, 4.f};

    Waveform(const Container& cont, vg::Size s, float top_val = 1.f)
      : Widget {s},
        _top_val {top_val},
        container {cont}
    {}

    /// Draw the entire waveform using the default plotter (`plotRounded`).
    void draw(vg::Canvas&);

    /// Draw the entire waveform using `Plotter`
    ///
    /// \expects `Plotter` should be invocable as `void(ctx, first, last)`
    template<typename Plotter>
    void draw(vg::Canvas&, Plotter&&);

    /// Draw a subset of the waveform using the default plotter (`plotRounded`).
    ///
    /// Useful for colouring different parts differently.
    ///
    /// \param subrange
    ///        The range to draw, with 0 at `[*Waveform<C>::range]().in`
    ///
    /// \expects `subrange` should be within [*Waveform<C>::range]() -
    /// `range.in`
    void draw_range(vg::Canvas&, Range subrange);

    /// Draw a subset of the waveform using `Plotter`.
    ///
    /// Useful for colouring different parts differently.
    ///
    /// \param subrange
    ///        The range to draw, with 0 at [*Waveform<C>::range]()`().in`
    ///
    /// \expects `subrange` should be within [*Waveform<C>::range]() -
    /// `range.in`
    ///
    /// \expects `Plotter` should be invocable as `void(ctx, first, last)`
    template<typename Plotter>
    void draw_range(vg::Canvas&, Range subrange, Plotter&&);

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
        _range = {std::max(0, r.in), r.out};
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

    /// Get the graphical point for a sample index
    vg::Point point(int index)
    {
      if (point_cache->points.size() == 0) return {0, size.h};
      return point_cache->points[
        std::clamp(
          int(std::round((index - _range.in) / point_cache->sp2r)),
          0, int(point_cache->points.size() - 1))];
    }

    vg::Point point_floor(int index)
    {
      if (point_cache->points.size() == 0) return {0, size.h};
      return point_cache->points[
        std::clamp(
          int(std::floor((index - _range.in) / point_cache->sp2r)),
          0, int(point_cache->points.size() - 1))];
    }

    vg::Point point_ceil(int index)
    {
      if (point_cache->points.size() == 0) return {0, size.h};
      return point_cache->points[
        std::clamp(
          int(std::ceil((index - _range.in) / point_cache->sp2r)),
          0, int(point_cache->points.size() - 1))];
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

  };

  // Implementation ///////////////////////////////////////////////////////////

  template<typename C>
  inline void Waveform<C>::draw(vg::Canvas& ctx)
  {
    draw(ctx, [&] (vg::Canvas& ctx, auto first, auto last) {
        ctx.plotRounded(first, last, point_cache.radius);
      });
  }

  template<typename C>
  template<typename Plotter>
  inline void Waveform<C>::draw(vg::Canvas& ctx, Plotter&& p)
  {
    if (point_cache->points.size() == 0) return;
    std::invoke(std::forward<Plotter>(p),
      ctx,
      std::begin(point_cache->points),
      std::end(point_cache->points));
  }

  template<typename C>
  inline void Waveform<C>::draw_range(vg::Canvas& ctx, Range subrange)
  {
    draw_range(ctx, subrange, [&](vg::Canvas& ctx, auto first, auto last) {
      ctx.plotRounded(first, last, point_cache.radius);
    });
  }

  template<typename C>
  template<typename Plotter>
  inline void Waveform<C>::draw_range(vg::Canvas& ctx,
                                      Range subrange,
                                      Plotter&& p)
  {
    if (point_cache->points.size() == 0) return;
    std::invoke(
      std::forward<Plotter>(p), ctx,
      std::begin(point_cache->points) +
        std::max(0.f,
                 std::floor((subrange.in - _range.in) / point_cache->sp2r)),
      std::begin(point_cache->points) +
        std::max(0.f,
                 std::ceil((subrange.out - _range.in) / point_cache->sp2r)));
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
      // Max
      // float val = 0;
      // for (int j = 0; (j < intprt) && (iter != last); j++, iter++) {
      //   val = std::max(std::abs(*iter), val);
      // }

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
  }
}
