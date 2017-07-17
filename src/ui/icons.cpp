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

  }

  ctx.restore();
}

void Note::draw(Canvas& ctx) {
  
}

}
}
