#ifndef UI_DRAWING_COLOURS_H
#define UI_DRAWING_COLOURS_H

#include <cairo.h>
#include <math.h>

namespace ui {
  namespace drawing {
    namespace tools {

      struct Colour {
        double r;
        double g;
        double b;
      };

      // Consts
      // Colours
      const Colour BLACK = {0, 0, 0};
      const Colour WHITE = {1, 1, 1};
      const Colour RED   = {1, 0, 0};
      const Colour GREEN = {0, 1, 0};
      const Colour BLUE  = {0, 0, 1};
      const Colour OPT1  = BLUE;
      const Colour OPT2  = WHITE;
      const Colour OPT3  = GREEN;
      const Colour OPT4  = RED;

      const int STROKE_WIDTH = 2;

      // Funcs
      inline void set_colour(cairo_t *cr, Colour c) {
        cairo_set_source_rgb(cr, c.r, c.g, c.b);
      };

      // Shapes
      inline void circle(cairo_t *cr, double x, double y, double r) {
        cairo_arc(cr, x, y, r, 0, 2 * M_PI);
      };

      inline void rectangle(cairo_t *cr, double x, double y, double width, double height) {
        cairo_rectangle(cr, x, y, width, height);
      }

      inline void line(cairo_t *cr, double fx, double fy, double tx, double ty) {
        cairo_move_to(cr, fx, fy);
        cairo_line_to(cr, tx, ty);
      }

      // Style
      inline void fill(cairo_t *cr, Colour c) {
        set_colour(cr, c);
        cairo_fill(cr);
      }

      inline void stroke(cairo_t *cr, Colour c) {
        set_colour(cr, c);
        cairo_stroke(cr);
      }

      inline void fill_p(cairo_t *cr, Colour c) {
        set_colour(cr, c);
        cairo_fill_preserve(cr);
      }

      inline void stroke_p(cairo_t *cr, Colour c) {
        set_colour(cr, c);
        cairo_stroke_preserve(cr);
      }
    }
  }
}

#endif
