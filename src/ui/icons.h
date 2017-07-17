#pragma once

#include "base.h"

namespace drawing {
namespace icons {

struct Icon : public SizedDrawable {
  Colour colour;
  float lineWidth = 2;
  virtual void draw(Canvas&) override {};
};

/// A simple arrow
struct Arrow : public Icon {

  enum Direction {
    Up, Down, Left, Right
  };

  Direction dir = Right;
  /// Add stop line ->|
  bool stopped;
  /// Loop arrow - CW for Up/Right, CCW for Down/Left
  bool looping;
  /// headLength/arrowLength
  float headRatio = 0.25;

  void draw(Canvas&) override;

};

/// A musical note
struct Note : public Icon {

  enum Direction {
    Right, Left
  };

  Direction dir;
  /// Whether the head of the note is filled;
  bool filled = true;

  void draw(Canvas&) override;
};

} // namespace icons
} // namespace drawing
