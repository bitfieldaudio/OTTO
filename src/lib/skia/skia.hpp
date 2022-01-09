#pragma once

#include <filesystem>

#include <SkBitmap.h>
#include <SkCanvas.h>
#include <SkFont.h>
#include <SkGradientShader.h>
#include <SkImage.h>
#include <SkImageInfo.h>
#include <SkPath.h>
#include <SkPixelRef.h>
#include <SkPixmap.h>
#include <SkRRect.h>
#include <SkTextBlob.h>
#include <SkTypeface.h>

#include "lib/globals.hpp"
#include "lib/logging.hpp"

#include "anchor.hpp"
#include "color.hpp"
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
  using Bitmap = SkBitmap;
  using PixelRef = SkPixelRef;
  using Pixmap = SkPixmap;
  using ClipOp = SkClipOp;
  using Color4f = SkColor4f;
  using ColorChannel = SkColorChannel;
  using ColorChannelFlag = SkColorChannelFlag;
  using ColorFilter = SkColorFilter;
  using Data = SkData;
  using Deque = SkDeque;
  using DeserialProcs = SkDeserialProcs;
  using FontArguments = SkFontArguments;
  using FontStyle = SkFontStyle;
  using GlyphID = SkGlyphID;
  using GradientShader = SkGradientShader;
  using IDChangeListener = SkIDChangeListener;
  using IRect = SkIRect;
  using Image = SkImage;
  using ImageInfo = SkImageInfo;
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

  inline const Vector screen_size = {320, 240};
  inline const Box screen_box = {{0, 0}, screen_size};

  inline void translate(Canvas& ctx, Point p)
  {
    ctx.translate(p.x(), p.y());
  }

  inline void rotate(Canvas& ctx, float deg, Point p)
  {
    ctx.rotate(deg, p.x(), p.y());
  }

  inline void saved(Canvas& ctx, util::callable<void()> auto&& f)
  {
    ctx.save();
    std::invoke(FWD(f));
    ctx.restore();
  }

  inline Box measureText(const Font& font, std::string_view str, const Paint& p = {})
  {
    Rect rect;
    font.measureText(str.data(), str.size(), SkTextEncoding::kUTF8, &rect, &p);
    Box box = rect;
    return box;
  }

  inline Box place_text(Canvas& ctx,
                        std::string_view text,
                        const Font& font,
                        const Paint& paint,
                        Point p,
                        skia::Anchor anchor = anchors::top_left)
  {
    Box box = measureText(font, text, paint);
    Point offset = box.point();
    box.move_to(p, anchor);
    sk_sp<SkTextBlob> val = SkTextBlob::MakeFromText(text.data(), text.size(), font);
    ctx.drawTextBlob(val, box.x() - offset.x(), box.y() - offset.y(), paint);
    return box;
  }

  inline Box place_text(Canvas& ctx,
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

  inline Box place_text(Canvas& ctx,
                        std::string_view text,
                        const Font& font,
                        const Paint& paint,
                        Box box,
                        skia::Anchor anchor = anchors::top_left)
  {
    return place_text(ctx, text, font, paint, box.point(anchor), anchor);
  }

  inline Box place_text(Canvas& ctx,
                        std::string_view text,
                        const Font& font,
                        Color color,
                        Box box,
                        skia::Anchor anchor = anchors::top_left)
  {
    return place_text(ctx, text, font, color, box.point(anchor), anchor);
  }

} // namespace otto::skia

namespace otto::colors {
  // Test palette (Figma)
  // constexpr const auto blue = skia::Color::bytes(40, 144, 219);
  // constexpr const auto green = skia::Color::bytes(23, 165, 37);
  // constexpr const auto yellow = skia::Color::bytes(242, 207, 23);
  // constexpr const auto red = skia::Color::bytes(228, 48, 36);
  constexpr const auto blue = skia::Color::bytes(22, 184, 254);
  constexpr const auto green = skia::Color::bytes(22, 254, 101);
  constexpr const auto yellow = skia::Color::bytes(254, 245, 22);
  constexpr const auto red = skia::Color::bytes(254, 22, 22);
  constexpr const auto white = skia::Color::bytes(255, 255, 255);
  constexpr const auto grey50 = skia::Color::bytes(128, 128, 128);
  constexpr const auto grey70 = skia::Color::bytes(46, 46, 46);
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
    res.setStyle(skia::Paint::kFill_Style);
    res.setStrokeCap(skia::Paint::kRound_Cap);
    res.setStrokeJoin(skia::Paint::kRound_Join);
    res.setColor(color);
    return res;
  }

  inline skia::Paint stroke_and_fill(skia::Color color = colors::white, float stroke_width = 6.f)
  {
    auto res = stroke(color, stroke_width);
    res.setStyle(skia::Paint::kStrokeAndFill_Style);
    return res;
  }
} // namespace otto::paints

namespace otto::fonts {
  namespace details {
    inline sk_sp<SkTypeface> load_typeface(const std::filesystem::path& path)
    {
      auto tf = SkTypeface::MakeFromFile(path.c_str());
      if (tf == nullptr) {
        LOGE("Could not load font from file '{}'", path);
      }
      return tf;
    }

  }; // namespace details

  inline skia::Font black_italic(float size)
  {
    static auto typeface = details::load_typeface(globals::resource_dir() / "fonts/Roboto-BlackItalic.ttf");
    return {typeface, size};
  }
  inline skia::Font black(float size)
  {
    static auto typeface = details::load_typeface(globals::resource_dir() / "fonts/Roboto-Black.ttf");
    return {typeface, size};
  }
  inline skia::Font light_italic(float size)
  {
    static auto typeface = details::load_typeface(globals::resource_dir() / "fonts/Roboto-LightItalic.ttf");
    return {typeface, size};
  }
  inline skia::Font light(float size)
  {
    static auto typeface = details::load_typeface(globals::resource_dir() / "fonts/Roboto-Light.ttf");
    return {typeface, size};
  }
  inline skia::Font medium_italic(float size)
  {
    static auto typeface = details::load_typeface(globals::resource_dir() / "fonts/Roboto-MediumItalic.ttf");
    return {typeface, size};
  }
  inline skia::Font medium(float size)
  {
    static auto typeface = details::load_typeface(globals::resource_dir() / "fonts/Roboto-Medium.ttf");
    return {typeface, size};
  }
  inline skia::Font regular_italic(float size)
  {
    static auto typeface = details::load_typeface(globals::resource_dir() / "fonts/Roboto-Italic.ttf");
    return {typeface, size};
  }
  inline skia::Font regular(float size)
  {
    static auto typeface = details::load_typeface(globals::resource_dir() / "fonts/Roboto-Regular.ttf");
    return {typeface, size};
  }
} // namespace otto::fonts
