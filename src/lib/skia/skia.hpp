#pragma once

#include <SkCanvas.h>
#include <SkFont.h>
#include <SkPath.h>
#include <SkRRect.h>
#include <SkTextBlob.h>
#include <SkTypeface.h>

#include "anchor.hpp"
#include "color.hpp"
#include "lib/logging.hpp"
#include "point.hpp"

/// Thin wrappers on top of skia classes for saner defaults & adding a few useful functions
namespace otto::skia {

  using Font = SkFont;
  using TextBlob = SkTextBlob;
  using Rect = SkRect;
  using RRect = SkRRect;
  using Alpha = SkAlpha;
  using AutoCanvasRestore = SkAutoCanvasRestore;
  using AutoPathBoundsUpdate = SkAutoPathBoundsUpdate;
  using ClipOp = SkClipOp;
  using Color4f = SkColor4f;
  using ColorChannel = SkColorChannel;
  using ColorChannelFlag = SkColorChannelFlag;
  using ColorFilter = SkColorFilter;
  using Data = SkData;
  using Deque = SkDeque;
  using DeserialProcs = SkDeserialProcs;
  using FilterQuality = SkFilterQuality;
  using FontArguments = SkFontArguments;
  using FontStyle = SkFontStyle;
  using GlyphID = SkGlyphID;
  using IDChangeListener = SkIDChangeListener;
  using IRect = SkIRect;
  using ImageFilter = SkImageFilter;
  using MaskFilter = SkMaskFilter;
  using Once = SkOnce;
  using PMColor = SkPMColor;
  using Path = SkPath;
  using PathDirection = SkPathDirection;
  using PathEffect = SkPathEffect;
  using PathFillType = SkPathFillType;
  using PathRef = SkPathRef;
  using PixelGeometry = SkPixelGeometry;
  using Pixmap = SkPixmap;
  using RBuffer = SkRBuffer;
  using RSXform = SkRSXform;
  using Scalar = SkScalar;
  using Semaphore = SkSemaphore;
  using SerialProcs = SkSerialProcs;
  using Shader = SkShader;
  using Stream = SkStream;
  using StreamAsset = SkStreamAsset;
  using SurfaceProps = SkSurfaceProps;
  using TextBlobBuilder = SkTextBlobBuilder;
  using TextEncoding = SkTextEncoding;
  using ThreadID = SkThreadID;
  using WBuffer = SkWBuffer;
  using Canvas = SkCanvas;
  using Paint = SkPaint;

  constexpr float width = 320;
  constexpr float height = 240;

  inline void translate(Canvas& ctx, Point p)
  {
    ctx.translate(p.x(), p.y());
  }

  inline Rect measureText(const Font& font, std::string_view str, const Paint& p = {})
  {
    Rect rect;
    font.measureText(str.data(), str.size(), SkTextEncoding::kUTF8, &rect, &p);
    return rect;
  }

  inline Box place_text(SkCanvas& ctx,
                        std::string_view text,
                        const Font& font,
                        const Paint& paint,
                        Point p,
                        skia::Anchor anchor = anchors::top_left)
  {
    Box box = measureText(font, text, paint);
    box.move_to(p, anchor);
    sk_sp<SkTextBlob> val = SkTextBlob::MakeFromText(text.data(), text.size(), font);
    ctx.drawTextBlob(val.get(), box.x(), box.y() + box.height(), paint);
    return box;
  }

  inline Box place_text(SkCanvas& ctx,
                        std::string_view text,
                        const Font& font,
                        Color color,
                        Point p,
                        skia::Anchor anchor = anchors::top_left)
  {
    Paint paint;
    paint.setAntiAlias(true);
    paint.setStyle(SkPaint::kFill_Style);
    paint.setColor(color);
    return place_text(ctx, text, font, paint, p, anchor);
  }

} // namespace otto::skia

namespace otto::colors {
  constexpr const auto blue = skia::Color::bytes(22, 184, 254);
  constexpr const auto green = skia::Color::bytes(22, 254, 101);
  constexpr const auto yellow = skia::Color::bytes(254, 245, 22);
  constexpr const auto red = skia::Color::bytes(254, 22, 22);
  constexpr const auto white = skia::Color::bytes(255, 255, 255);
  constexpr const auto grey50 = skia::Color::bytes(128, 128, 128);
  constexpr const auto black = skia::Color::bytes(0, 0, 0);
} // namespace otto::colors

namespace otto::paints {
  inline skia::Paint stroke(skia::Color color = colors::white, float width = 6.f)
  {
    skia::Paint res;
    res.setAntiAlias(true);
    res.setStyle(SkPaint::kStroke_Style);
    res.setStrokeCap(SkPaint::kRound_Cap);
    res.setStrokeJoin(SkPaint::kRound_Join);
    res.setStrokeWidth(width);
    res.setColor(color);
    return res;
  }

  inline skia::Paint fill(skia::Color color = colors::white)
  {
    skia::Paint res;
    res.setAntiAlias(true);
    res.setStyle(SkPaint::kFill_Style);
    res.setStrokeCap(SkPaint::kRound_Cap);
    res.setStrokeJoin(SkPaint::kRound_Join);
    res.setColor(color);
    return res;
  }

  inline skia::Paint stroke_and_fill(skia::Color color = colors::white, float stroke_width = 6.f)
  {
    auto res = stroke(color, stroke_width);
    res.setStyle(SkPaint::kStrokeAndFill_Style);
    return res;
  }
} // namespace otto::paints

namespace otto::fonts {
  inline skia::Font black_italic(float size)
  {
    static auto typeface = SkTypeface::MakeFromFile("./data/fonts/Roboto-BlackItalic.ttf");
    OTTO_ASSERT(typeface != nullptr);
    return skia::Font(typeface, size);
  }
  inline skia::Font black(float size)
  {
    static auto typeface = SkTypeface::MakeFromFile("./data/fonts/Roboto-Black.ttf");
    OTTO_ASSERT(typeface != nullptr);
    return skia::Font(typeface, size);
  }
  inline skia::Font light_italic(float size)
  {
    static auto typeface = SkTypeface::MakeFromFile("./data/fonts/Roboto-LightItalic.ttf");
    OTTO_ASSERT(typeface != nullptr);
    return skia::Font(typeface, size);
  }
  inline skia::Font light(float size)
  {
    static auto typeface = SkTypeface::MakeFromFile("./data/fonts/Roboto-Light.ttf");
    OTTO_ASSERT(typeface != nullptr);
    return skia::Font(typeface, size);
  }
  inline skia::Font medium_italic(float size)
  {
    static auto typeface = SkTypeface::MakeFromFile("./data/fonts/Roboto-MediumItalic.ttf");
    OTTO_ASSERT(typeface != nullptr);
    return skia::Font(typeface, size);
  }
  inline skia::Font medium(float size)
  {
    static auto typeface = SkTypeface::MakeFromFile("./data/fonts/Roboto-Medium.ttf");
    OTTO_ASSERT(typeface != nullptr);
    return skia::Font(typeface, size);
  }
  inline skia::Font regular_italic(float size)
  {
    static auto typeface = SkTypeface::MakeFromFile("./data/fonts/Roboto-Italic.ttf");
    OTTO_ASSERT(typeface != nullptr);
    return skia::Font(typeface, size);
  }
  inline skia::Font regular(float size)
  {
    static auto typeface = SkTypeface::MakeFromFile("./data/fonts/Roboto-Regular.ttf");
    OTTO_ASSERT(typeface != nullptr);
    return skia::Font(typeface, size);
  }
} // namespace otto::fonts
