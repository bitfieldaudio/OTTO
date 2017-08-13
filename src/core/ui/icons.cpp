#include "icons.h"

#include <cmath>

#include "../util/match.h"

namespace drawing {
namespace icons {

void Arrow::draw(Canvas& ctx) {
  ctx.save();
  ctx.lineJoin(Canvas::LineJoin::ROUND);
  ctx.lineCap(Canvas::LineCap::ROUND);
  ctx.lineWidth(lineWidth);

  if (!looping) {

  float s;
  Size rsize;
  match(dir)
    .c(Up, [&] () {
       s = size.h;
       rsize = size;
     })
    .c(Right, [&] () {
       s = size.w;
       rsize = size.swapWH();
       ctx.rotateAround(0.5 * M_PI, Size(s,s).center());
     })
    .c(Down, [&] () {
       s = size.h;
       rsize = size;
       ctx.rotateAround(1.0 * M_PI, size.center());
     })
    .c(Left, [&] () {
       s = size.w;
       rsize = size.swapWH();
       ctx.rotateAround(0.5 * M_PI, Size(s,s).center());
       ctx.rotateAround(1.0 * M_PI, rsize.center());
     });

  Point start = {rsize.w / 2.f, rsize.h};
  Point end = {rsize.w / 2.f, 0};
  Point cp1 = {
    float(rsize.w - rsize.h * headRatio * M_SQRT2) / 2.f,
    float(rsize.h * headRatio)
  };
  Point cp2 = {
    float(rsize.w + rsize.h * headRatio * M_SQRT2) / 2.f,
    float(rsize.h * headRatio)
  };

  ctx.beginPath();
  ctx.moveTo(start);
  ctx.lineTo(end);
  ctx.lineTo(cp1);
  ctx.lineTo(cp2);
  ctx.lineTo(end);

  if (stopped) {
    ctx.moveTo(cp1.x, end.y);
    ctx.lineTo(cp2.x, end.y);
  }

  ctx.strokeStyle(colour);
  ctx.fillStyle(colour);
  ctx.stroke();
  ctx.fill();

  } else {

    // Draw looping arrow.

    const float scale = std::min(size.w / 12, size.h / 6);
    ctx.translate(size.w / 2 - 6 * scale, size.h / 2 - 3 * scale);

    const float r   = 3 * scale;
    Point cp1 = Point{5, 0} * scale;
    const Point cp2 = Point{3, 0} * scale;
    const Point ap1 = Point{0, 0} * scale;
    const Point cp3 = Point{0, 3} * scale;
    const Point ap2 = Point{0, 6} * scale;
    const Point cp4 = Point{3, 6} * scale;
    const Point cp5 = Point{9, 6} * scale;
    const Point ap3 = Point{12, 6} * scale;
    const Point cp6 = Point{12, 3} * scale;
    const Point ap4 = Point{12, 0} * scale;
    const Point cp7 = Point{9, 0} * scale;
    Point cp8 = Point{7, 0} * scale;

    Point hp1, hp2, hp3;
    switch (dir) {
    case Up:
    case Right:
      hp1 = cp1 + Point(1, 0) * scale;
      hp2 = hp1 - Point(scale * 2, scale * 2 * M_SQRT2 / 2.f);
      hp3 = hp1 - Point(scale * 2, -scale * 2 * M_SQRT2 / 2.f);
      cp8 = Point{8, 0} * scale;
      break;
    case Down:
    case Left:
      hp1 = cp8 - Point(1, 0) * scale;
      hp2 = hp1 + Point(scale * 2, scale * 2 * M_SQRT2 / 2.f);
      hp3 = hp1 + Point(scale * 2, -scale * 2 * M_SQRT2 / 2.f);
      cp1 = Point{4, 0} * scale;
      break;
    }

    ctx.beginPath();
    ctx.moveTo(cp1);
    ctx.lineTo(cp2);
    ctx.arcTo(ap1, cp3, r);
    ctx.arcTo(ap2, cp4, r);
    ctx.lineTo(cp5);
    ctx.arcTo(ap3, cp6, r);
    ctx.arcTo(ap4, cp7, r);
    ctx.lineTo(cp8);

    ctx.strokeStyle(colour);
    ctx.stroke();

    // Arrow head
    ctx.beginPath();
    ctx.moveTo(hp1);
    ctx.lineTo(hp2);
    ctx.lineTo(hp3);
    ctx.lineTo(hp1);
    ctx.fill(colour);
    ctx.stroke(colour);

  }

  ctx.restore();
}

void Note::draw(Canvas& ctx) {
  
}

}
}
