#pragma once

#include <memory>
#include <algorithm>
#include <iterator>

#include "util/waveform.hpp"
#include "core/ui/base.hpp"
#include "util/audio.hpp"

namespace otto::ui {

  template<typename Container>
  class WaveformWidget : public Widget {
  public:

    using Range = util::audio::Section<std::size_t>;

    struct iterator {

      using value_type = vg::Point;
      using difference_type = std::ptrdiff_t;
      using reference = vg::Point;
      using pointer = vg::Point*;
      using iterator_category = std::bidirectional_iterator_tag;

      const WaveformWidget &w;
      int idx;
      float inc;
      Range range;

      iterator(const WaveformWidget &w, int idx, float inc, Range r) :
        w (w), idx (idx), inc (inc) , range (r) {}

      vg::Point get() const {
        return w.point(idx);
      }

      vg::Point operator*() const {
        return get();
      }

      iterator operator++() {
        int nx = std::round(inc * std::round(idx / inc + 1));
        if (idx < range.out && nx > range.out) {
          idx = range.out;
        } else {
          int mx = nx;
          for (int i = idx + 1; i < nx; i++) {
            if ((*w.wf)[i] > (*w.wf)[mx]) {
              mx = i;
            }
          }
          idx = mx;
        }
        return *this;
      }

      iterator operator--() {
        int nx = std::round(inc * std::round(idx / inc - 1));
        if (idx > range.in && nx < range.in) {
          idx = range.in;
        } else {
          int mx = nx;
          for (int i = idx - 1; i > nx; i++) {
            if ((*w.wf)[i] > (*w.wf)[mx]) {
              mx = i;
            }
          }
          idx = mx;
        }
        return *this;
      }

      bool operator==(iterator rhs) const {return idx == rhs.idx;}
      bool operator!=(iterator rhs) const {return idx != rhs.idx;}
      bool operator>(iterator rhs) const {return idx > rhs.idx;}
      bool operator<(iterator rhs) const {return idx < rhs.idx;}
      bool operator>=(iterator rhs) const {return idx >= rhs.idx;}
      bool operator<=(iterator rhs) const {return idx <= rhs.idx;}
    };

    Range viewRange;
    vg::Colour lineCol;
    float minPx;
    float scale = 1;

    WaveformWidget() {};

    WaveformWidget(std::shared_ptr<Container> wf, vg::Size s )
      : Widget (s),
        wf (wf)
    {
      viewRange = {0, wf->size() - 1};
    }

    void draw(vg::Canvas &) override;

    void drawRange(vg::Canvas&, Range range, vg::Colour);

    void drawRange(vg::Canvas& ctx, Range range) {
      drawRange(ctx, range, lineCol);
    }

    iterator begin() const {
      return begin(viewRange);
    }
    iterator begin(Range range) const;
    iterator end() const {
      return end(viewRange);
    }
    iterator end(Range range) const;

    vg::Point point(std::size_t idx) const;

  private:
    std::shared_ptr<Container> wf;
  };

  /****************************************/
  /* WaveformWidget Implementation        */
  /****************************************/

  template<typename C>
  inline void WaveformWidget<C>::draw(vg::Canvas &ctx) {
    drawRange(ctx, viewRange);
  }

  template<typename C>
  inline void WaveformWidget<C>::drawRange(
                                           vg::Canvas &ctx,
                                           Range range,
                                           vg::Colour colour)
  {
    using namespace vg;

    const float pxPrPt = size.w / float(viewRange.size());

    ctx.beginPath();
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    if (range.size() < 3) {
      ctx.moveTo(range.in / pxPrPt, size.h);
      ctx.lineTo(range.out / pxPrPt, size.h - 0);
    } else {
      ctx.plotRounded(begin(range), end(range), 1);
    }
    ctx.strokeStyle(colour);
    ctx.stroke();
  }

  template<typename C>
  inline typename WaveformWidget<C>::iterator WaveformWidget<C>::begin(Range r) const {
    float pxPrPt = size.w / float(viewRange.size());
    float inc = std::max(1.0f, std::round(minPx/pxPrPt));
    return iterator(*this,  r.in, inc, r);
  }

  template<typename C>
  inline typename WaveformWidget<C>::iterator WaveformWidget<C>::end(Range r) const {
    float pxPrPt = size.w / float(viewRange.size());
    float inc = std::round(std::max(1.0f, minPx/pxPrPt));
    return iterator(*this,  r.out + 1, inc, r);
  }

  template<typename C>
  inline vg::Point WaveformWidget<C>::point(std::size_t idx) const {
    if (idx < wf->size() && idx >= 0) {
      return {
        (idx - viewRange.in) / float(viewRange.size()) * size.w,
          (1 - scale * (*wf)[idx]) * size.h
          };
    }
    return {
      (idx - viewRange.in) / float(viewRange.size()) * size.w,
        size.h
        };
  }

} // otto::ui
