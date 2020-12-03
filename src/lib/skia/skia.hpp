#pragma once

#include <SkCanvas.h>
#include <SkFont.h>
#include <SkPath.h>
#include <SkTextBlob.h>
#include <SkTypeface.h>

#include "anchor.hpp"
#include "color.hpp"
#include "point.hpp"

/// Thin wrappers on top of skia classes for saner defaults & adding a few useful functions
namespace otto::skia {

  using Font = SkFont;
  using TextBlob = SkTextBlob;
  using Rect = SkRect;
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

  struct Paint : SkPaint {
    Paint()
    {
      setAntiAlias(true);
      setStyle(SkPaint::kStroke_Style);
      setStrokeCap(SkPaint::kRound_Cap);
      setStrokeJoin(SkPaint::kRound_Join);
      setStrokeWidth(6.f);
    }
  };

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
