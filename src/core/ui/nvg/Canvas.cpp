#include "Canvas.hpp"

#include <nanovg.h>
#include "util/type_traits.hpp"

namespace otto::nvg {

  NVGcolor nvgColor(const Color& color)
  {
    return nvgRGBA(color.r, color.g, color.b, color.a);
  }

  NVGpaint nvgPaint(Canvas& canvas, const Paint& paint)
  {
    NVGpaint nvgPaint;
    switch (paint.type) {
      case Paint::Type::Linear: {
        float x0 = paint.xx;
        float y0 = paint.yy;
        float x1 = paint.aa;
        float y1 = paint.bb;
        canvas.local2Global(x0, y0);
        canvas.local2Global(x1, y1);
        nvgPaint =
          nvgLinearGradient(canvas.nvgContext(), x0, y0, x1, y1, nvgColor(paint.sColor), nvgColor(paint.eColor));
      } break;
      case Paint::Type::Box: {
        float x = paint.xx;
        float y = paint.yy;
        canvas.local2Global(x, y);
        nvgPaint = nvgBoxGradient(canvas.nvgContext(), x, y, paint.aa, paint.bb, paint.cc, paint.dd,
                                  nvgColor(paint.sColor), nvgColor(paint.eColor));
      } break;
      case Paint::Type::Radial: {
        float cx = paint.xx;
        float cy = paint.yy;
        canvas.local2Global(cx, cy);
        nvgPaint = nvgRadialGradient(canvas.nvgContext(), cx, cy, paint.aa, paint.bb, nvgColor(paint.sColor),
                                     nvgColor(paint.eColor));
      } break;
      case Paint::Type::ImagePattern: {
        float ox = paint.xx;
        float oy = paint.yy;
        canvas.local2Global(ox, oy);
        nvgPaint = nvgImagePattern(canvas.nvgContext(), ox, oy, paint.aa, paint.bb, paint.cc, paint.imageID, paint.dd);
      } break;
      case Paint::Type::None:
      default: break;
    }
    return nvgPaint;
  }

  /*----------------- Propoties ---------------------*/
  Canvas::Canvas(NVGcontext* ctx, float width, float height, float scaleRatio)
  {
    m_nvgCtx = ctx;
    m_width = width;
    m_height = height;
    m_scaleRatio = scaleRatio;
    m_xPos = m_yPos = 0;
  }

  Canvas::Canvas(NVGcontext* ctx, Size size, float scaleRatio) : Canvas(ctx, size.w, size.h, scaleRatio) {}


  /*-------------------- Style Control -------------------*/

  Canvas& Canvas::globalAlpha(float alpha)
  {
    nvgGlobalAlpha(m_nvgCtx, alpha);
    return *this;
  }

  Canvas& Canvas::lineCap(LineCap cap)
  {
    int nvgCap = NVG_BUTT;
    if (cap == LineCap::SQUARE)
      nvgCap = NVG_SQUARE;
    else if (cap == LineCap::ROUND)
      nvgCap = NVG_ROUND;
    nvgLineCap(m_nvgCtx, nvgCap);
    return *this;
  }

  Canvas& Canvas::lineJoin(LineJoin join)
  {
    int nvgJoin = NVG_BEVEL;
    if (join == LineJoin::ROUND)
      nvgJoin = NVG_ROUND;
    else if (join == LineJoin::MITER)
      nvgJoin = NVG_MITER;
    nvgLineJoin(m_nvgCtx, nvgJoin);
    return *this;
  }

  Canvas& Canvas::lineWidth(float width)
  {
    nvgStrokeWidth(m_nvgCtx, width);
    return *this;
  }

  Canvas& Canvas::miterLimit(float limit)
  {
    nvgMiterLimit(m_nvgCtx, limit);
    return *this;
  }


  Canvas& Canvas::fillStyle(const Color& color)
  {
    nvgFillColor(m_nvgCtx, nvgRGBA(color.r, color.g, color.b, color.a));
    return *this;
  }

  Canvas& Canvas::fillStyle(const Paint& paint)
  {
    if (paint.type != Paint::Type::None) {
      NVGpaint npaint = nvgPaint(*this, paint);
      nvgFillPaint(m_nvgCtx, npaint);
    }
    return *this;
  }

  Canvas& Canvas::strokeStyle(const Paint& paint)
  {
    if (paint.type != Paint::Type::None) {
      NVGpaint npaint = nvgPaint(*this, paint);
      nvgStrokePaint(m_nvgCtx, npaint);
    }
    return *this;
  }

  Canvas& Canvas::strokeStyle(const Color& color)
  {
    nvgStrokeColor(m_nvgCtx, nvgRGBA(color.r, color.g, color.b, color.a));
    return *this;
  }

  Paint Canvas::createLinearGradient(float x0, float y0, float x1, float y1, const Color& scolor, const Color& ecolor)
  {
    Paint gdt;
    gdt.type = Paint::Type::Linear;
    gdt.xx = x0;
    gdt.yy = y0;
    gdt.aa = x1;
    gdt.bb = y1;
    gdt.sColor = scolor;
    gdt.eColor = ecolor;
    return gdt;
  }

  Paint Canvas::createRadialGradient(float cx, float cy, float r1, float r2, const Color& icolor, const Color& ocolor)
  {
    Paint gdt;
    gdt.type = Paint::Type::Radial;
    gdt.xx = cx;
    gdt.yy = cy;
    gdt.aa = r1;
    gdt.bb = r2;
    gdt.sColor = icolor;
    gdt.eColor = ocolor;
    return gdt;
  }

  Paint Canvas::createBoxGradient(float x, float y, float w, float h, float r, float f, Color icol, Color ocol)
  {
    Paint gdt;
    gdt.type = Paint::Type::Box;
    gdt.xx = x;
    gdt.yy = y;
    gdt.aa = w;
    gdt.bb = h;
    gdt.cc = r;
    gdt.dd = f;
    gdt.sColor = icol;
    gdt.eColor = ocol;
    return gdt;
  }

  Paint Canvas::createPattern(const Image& image, float ox, float oy, float w, float h, float angle, float alpha)
  {
    Paint gdt;
    gdt.type = Paint::Type::ImagePattern;
    gdt.imageID = image.imageID;
    gdt.xx = ox;
    gdt.yy = oy;
    gdt.aa = w;
    gdt.bb = h;
    gdt.cc = angle;
    gdt.dd = alpha;
    return gdt;
  }

  Canvas& Canvas::font(const Font& font)
  {
    if (font.valid()) nvgFontFaceId(m_nvgCtx, font.face);
    return *this;
  }

  Canvas& Canvas::font(float size)
  {
    nvgFontSize(m_nvgCtx, size);
    return *this;
  }

  Canvas& Canvas::textAlign(HorizontalAlign hAlign, VerticalAlign vAlign)
  {
    nvgTextAlign(m_nvgCtx, util::underlying(hAlign) | util::underlying(vAlign));
    return *this;
  }

  void applyTextStyle(Canvas& canvas, const TextStyle& textStyle)
  {
    if (textStyle.face >= 0) nvgFontFaceId(canvas.nvgContext(), textStyle.face);
    if (!std::isnan(textStyle.lineHeight)) nvgTextLineHeight(canvas.nvgContext(), textStyle.lineHeight);
    if (std::isnan(textStyle.blur)) nvgFontBlur(canvas.nvgContext(), textStyle.blur);
    if (!std::isnan(textStyle.letterSpace)) nvgTextLetterSpacing(canvas.nvgContext(), textStyle.letterSpace);
    nvgTextAlign(canvas.nvgContext(), util::underlying(textStyle.hAlign) | util::underlying(textStyle.vAlign));
    nvgFontSize(canvas.nvgContext(), textStyle.size);
  }

  Canvas& Canvas::fillStyle(const TextStyle& textStyle)
  {
    applyTextStyle(*this, textStyle);
    nvgFillColor(m_nvgCtx, nvgColor(textStyle.color));
    return *this;
  }

  float Canvas::measureText(util::string_ref text, float rowWidth)
  {
    float width = 0;
    if (std::isnan(rowWidth))
      width = nvgTextBounds(m_nvgCtx, 0, 0, text.c_str(), nullptr, nullptr);
    else {
      float bouds[4]{0};
      width = measureText(text, 0, 0, bouds, rowWidth);
    }
    return width;
  }

  float Canvas::measureText(util::string_ref text, float x, float y, float* bounds, float rowWidth)
  {
    local2Global(x, y);
    if (std::isnan(rowWidth))
      nvgTextBounds(m_nvgCtx, x, y, text.c_str(), nullptr, bounds);
    else
      nvgTextBoxBounds(m_nvgCtx, x, y, rowWidth, text.c_str(), nullptr, bounds);
    float width = 0;
    if (bounds) width = bounds[2] - bounds[0];
    return width;
  }


  Canvas& Canvas::globalCompositeOperation(CompositeOperation op)
  {
    auto nvgOp = [&] {
      switch (op) {
        case CompositeOperation::SOURCE_OVER: return NVG_SOURCE_OVER;
        case CompositeOperation::SOURCE_IN: return NVG_SOURCE_IN;
        case CompositeOperation::SOURCE_OUT: return NVG_SOURCE_OUT;
        case CompositeOperation::ATOP: return NVG_ATOP;
        case CompositeOperation::DESTINATION_OVER: return NVG_DESTINATION_OVER;
        case CompositeOperation::DESTINATION_IN: return NVG_DESTINATION_IN;
        case CompositeOperation::DESTINATION_OUT: return NVG_DESTINATION_OUT;
        case CompositeOperation::DESTINATION_ATOP: return NVG_DESTINATION_ATOP;
        case CompositeOperation::LIGHTER: return NVG_LIGHTER;
        case CompositeOperation::COPY: return NVG_COPY;
        case CompositeOperation::XOR: return NVG_XOR;
      }
      OTTO_UNREACHABLE;
    }();
    nvgGlobalCompositeOperation(m_nvgCtx, nvgOp);
    return *this;
  }

  /* ------------------- Basic Path ----------------------*/

  Canvas& Canvas::moveTo(float x, float y)
  {
    local2Global(x, y);
    nvgMoveTo(m_nvgCtx, x, y);
    return *this;
  }

  Canvas& Canvas::lineTo(float x, float y)
  {
    local2Global(x, y);
    nvgLineTo(m_nvgCtx, x, y);
    return *this;
  }

  Canvas& Canvas::arcTo(float x1, float y1, float x2, float y2, float r)
  {
    local2Global(x1, y1);
    local2Global(x2, y2);
    nvgArcTo(m_nvgCtx, x1, y1, x2, y2, r);
    return *this;
  }

  Canvas& Canvas::quadraticCurveTo(float cpx, float cpy, float x, float y)
  {
    local2Global(cpx, cpy);
    local2Global(x, y);
    nvgQuadTo(m_nvgCtx, cpx, cpy, x, y);
    return *this;
  }

  Canvas& Canvas::bezierCurveTo(float cp1x, float cp1y, float cp2x, float cp2y, float x, float y)
  {
    local2Global(cp1x, cp1y);
    local2Global(cp2x, cp2y);
    local2Global(x, y);
    nvgBezierTo(m_nvgCtx, cp1x, cp1y, cp2x, cp2y, x, y);
    return *this;
  }

  Canvas& Canvas::arc(float x, float y, float r, float sAngle, float eAngle, bool counterclockwise)
  {
    local2Global(x, y);
    int dir = counterclockwise ? NVG_CCW : NVG_CW;
    nvgArc(m_nvgCtx, x, y, r, sAngle, eAngle, dir);
    return *this;
  }


  Canvas& Canvas::closePath()
  {
    nvgClosePath(m_nvgCtx);
    return *this;
  }


  /* ------------------- Advance Path --------------------*/


  Canvas& Canvas::rect(float x, float y, float w, float h)
  {
    local2Global(x, y);
    nvgRect(m_nvgCtx, x, y, w, h);
    return *this;
  }

  Canvas& Canvas::roundedRect(float x, float y, float w, float h, float r)
  {
    local2Global(x, y);
    nvgRoundedRect(m_nvgCtx, x, y, w, h, r);
    return *this;
  }

  Canvas& Canvas::circle(float cx, float cy, float r)
  {
    local2Global(cx, cy);
    nvgCircle(m_nvgCtx, cx, cy, r);
    return *this;
  }

  Canvas& Canvas::ellipse(float cx, float cy, float rx, float ry)
  {
    local2Global(cx, cy);
    nvgEllipse(m_nvgCtx, cx, cy, rx, ry);
    return *this;
  }

  /* ------------------- Draw Action ---------------------*/

  Canvas& Canvas::fill()
  {
    nvgFill(m_nvgCtx);
    return *this;
  }

  Canvas& Canvas::stroke()
  {
    nvgStroke(m_nvgCtx);
    return *this;
  }

  Canvas& Canvas::fillRect(float x, float y, float w, float h)
  {
    local2Global(x, y);
    nvgBeginPath(m_nvgCtx);
    nvgRect(m_nvgCtx, x, y, w, h);
    nvgFill(m_nvgCtx);
    return *this;
  }

  Canvas& Canvas::strokeRect(float x, float y, float w, float h)
  {
    local2Global(x, y);
    nvgBeginPath(m_nvgCtx);
    nvgRect(m_nvgCtx, x, y, w, h);
    nvgStroke(m_nvgCtx);
    return *this;
  }

  Canvas& Canvas::clearColor(const Color& color)
  {
    nvgCancelFrame(m_nvgCtx);
    nvgFillColor(m_nvgCtx, nvgRGBA(color.r, color.g, color.b, color.a));
    nvgBeginPath(m_nvgCtx);
    nvgRect(m_nvgCtx, m_xPos, m_yPos, m_width, m_height);
    nvgFill(m_nvgCtx);

    return *this;
  }

  Canvas& Canvas::fillText(util::string_ref text, float x, float y, float rowWidth)
  {
    if (text.length()) {
      local2Global(x, y);
      if (std::isnan(rowWidth))
        nvgText(m_nvgCtx, x, y, text.c_str(), nullptr);
      else
        nvgTextBox(m_nvgCtx, x, y, rowWidth, text.c_str(), nullptr);
    }
    return *this;
  }

  Canvas& Canvas::drawImage(Image& image,
                            float x,
                            float y,
                            float width,
                            float height,
                            float sx,
                            float sy,
                            float swidth,
                            float sheight)
  {
    if (image.valid()) {
      save();

      local2Global(x, y);
      int w, h;
      image.size(w, h);

      if (std::isnan(swidth)) swidth = w - sx;
      if (std::isnan(sheight)) sheight = h - sy;
      if (std::isnan(width)) width = swidth;
      if (std::isnan(height)) height = sheight;

      resetClip();
      clip(x, y, width, height);

      float sw = width / swidth;
      float sh = height / sheight;
      float rx, ry, rw, rh;
      rw = w * sw;
      rh = h * sh;
      rx = x - sx * sw;
      ry = y - sy * sh;

      Paint pattern = createPattern(image, rx, ry, rw, rh, 0, 1.0f);
      fillStyle(pattern);
      rect(rx, ry, rw, rh).fill();
      restore();
    }
    return *this;
  }

  /*------------------- State Handling -----------------*/

  Canvas& Canvas::save()
  {
    nvgSave(m_nvgCtx);
    return *this;
  }

  Canvas& Canvas::restore()
  {
    nvgRestore(m_nvgCtx);
    return *this;
  }

  Canvas& Canvas::reset()
  {
    nvgReset(m_nvgCtx);
    return *this;
  }

  /*--------------------- Transformations ----------------*/

  Canvas& Canvas::scale(float scalewidth, float scaleheight)
  {
    nvgScale(m_nvgCtx, scalewidth, scaleheight);
    return *this;
  }

  Canvas& Canvas::rotate(float angle)
  {
    nvgRotate(m_nvgCtx, angle);
    return *this;
  }

  Canvas& Canvas::translate(float x, float y)
  {
    nvgTranslate(m_nvgCtx, x, y);
    return *this;
  }

  Canvas& Canvas::transform(float a, float b, float c, float d, float e, float f)
  {
    nvgTransform(m_nvgCtx, a, b, c, d, e, f);
    return *this;
  }

  Canvas& Canvas::setTransform(float a, float b, float c, float d, float e, float f)
  {
    nvgResetTransform(m_nvgCtx);
    nvgTransform(m_nvgCtx, a, b, c, d, e, f);
    return *this;
  }

  Canvas& Canvas::restTransform()
  {
    nvgResetTransform(m_nvgCtx);
    return *this;
  }

  /*---------------- Canvas Control -----------------*/
  Canvas& Canvas::beginFrame(int windowWidth, int windowHeight)
  {
    nvgBeginFrame(m_nvgCtx, windowWidth, windowHeight, m_scaleRatio);
    // Clip out side area
    nvgScissor(m_nvgCtx, m_xPos, m_yPos, m_width, m_height);

    return *this;
  }

  Canvas& Canvas::cancelFrame()
  {
    nvgCancelFrame(m_nvgCtx);
    return *this;
  }

  void Canvas::endFrame()
  {
    nvgEndFrame(m_nvgCtx);
  }

  Canvas& Canvas::beginPath()
  {
    nvgBeginPath(m_nvgCtx);
    return *this;
  }

  Canvas& Canvas::pathWinding(Winding dir)
  {
    int windingDir = NVG_CW;
    if (dir == Winding::CCW) windingDir = NVG_CCW;
    nvgPathWinding(m_nvgCtx, windingDir);
    return *this;
  }

  Canvas& Canvas::clip(float x, float y, float w, float h)
  {
    local2Global(x, y);
    nvgIntersectScissor(m_nvgCtx, x, y, w, h);
    return *this;
  }

  Canvas& Canvas::resetClip()
  {
    nvgResetScissor(m_nvgCtx);
    return *this;
  }


  /// Get the canvas size
  Size Canvas::size() const noexcept
  {
    return {m_width, m_height};
  }

  Canvas& Canvas::moveTo(Point p)
  {
    moveTo(p.x, p.y);
    return *this;
  }

  Canvas& Canvas::lineTo(Point p)
  {
    lineTo(p.x, p.y);
    return *this;
  }

  Canvas& Canvas::arcTo(Point p1, Point p2, float r)
  {
    arcTo(p1.x, p1.y, p2.x, p2.y, r);
    return *this;
  }

  Canvas& Canvas::quadraticCurveTo(Point control, Point end)
  {
    quadraticCurveTo(control.x, control.y, end.x, end.y);
    return *this;
  }

  Canvas& Canvas::bezierCurveTo(Point cp1, Point cp2, Point end)
  {
    bezierCurveTo(cp1.x, cp1.y, cp2.x, cp2.y, end.x, end.y);
    return *this;
  }

  Canvas& Canvas::arc(Point cp, float r, float sAngle, float eAngle, bool counterclockwise)
  {
    arc(cp.x, cp.y, r, sAngle, eAngle, counterclockwise);
    return *this;
  }

  Canvas& Canvas::rect(Point p, Size s)
  {
    rect(p.x, p.y, s.w, s.h);
    return *this;
  }

  Canvas& Canvas::rect(Box b)
  {
    rect(b.x, b.y, b.width, b.height);
    return *this;
  }

  Canvas& Canvas::centeredSquare(Point p, float side_length)
  {
    rect(p.x - side_length / 2, p.y - side_length / 2, side_length, side_length);
    return *this;
  }

  Canvas& Canvas::roundedRect(Point p, Size s, float r)
  {
    roundedRect(p.x, p.y, s.w, s.h, r);
    return *this;
  }

  Canvas& Canvas::roundedRect(Box b, float r)
  {
    roundedRect(b.x, b.y, b.width, b.height, r);
    return *this;
  }

  Canvas& Canvas::circle(Point p, float r)
  {
    circle(p.x, p.y, r);
    return *this;
  }

  Canvas& Canvas::ellipse(Point p, float rx, float ry)
  {
    ellipse(p.x, p.y, rx, ry);
    return *this;
  }

  Canvas& Canvas::font(const Font& f, float size)
  {
    font(f);
    font(size);
    return *this;
  }

  Canvas& Canvas::fillText(util::string_ref text, Point p, float rowWidth)
  {
    fillText(text, p.x, p.y, rowWidth);
    return *this;
  }

  Box Canvas::measureText(util::string_ref text, Point p, float rowWidth)
  {
    float bounds[4] = {0};
    measureText(text, p.x, p.y, bounds);
    return Box(Point{bounds[0], bounds[1]}, Point{bounds[2], bounds[3]});
  }

  Canvas& Canvas::fill(const Color& color)
  {
    fillStyle(color);
    fill();
    return *this;
  }

  Canvas& Canvas::stroke(const Color& color)
  {
    strokeStyle(color);
    stroke();
    return *this;
  }

  Canvas& Canvas::stroke(const Color& color, float line_width)
  {
    lineWidth(line_width);
    strokeStyle(color);
    stroke();
    return *this;
  }


  Canvas& Canvas::translate(Point p)
  {
    translate(p.x, p.y);
    return *this;
  }

  Canvas& Canvas::rotateAround(Point p, float r)
  {
    translate(p);
    rotate(r);
    translate(-p);
    return *this;
  }

  Canvas& Canvas::scaleTowards(float s, Point p)
  {
    translate(p);
    scale(s, s);
    translate(-p);
    return *this;
  }

  Canvas& Canvas::scaleTowards(Point s, Point p)
  {
    translate(p);
    scale(s.x, s.y);
    translate(-p);
    return *this;
  }

  Canvas& Canvas::draw(Drawable& d)
  {
    d.draw(*this);
    return *this;
  }

  Canvas& Canvas::draw(Drawable&& d)
  {
    d.draw(*this);
    return *this;
  }

  Canvas& Canvas::drawAt(Point p, Drawable&& d)
  {
    save();
    translate(p);
    d.draw(*this);
    restore();
    return *this;
  }

  Canvas& Canvas::drawAt(Point p, Drawable& d)
  {
    save();
    translate(p);
    d.draw(*this);
    restore();
    return *this;
  }
  // Debuging

  Canvas& Canvas::debugDot(Point p, Color c)
  {
    beginPath();
    circle(p, 1);
    fill(c);
    return *this;
  }
} // namespace otto::nvg
