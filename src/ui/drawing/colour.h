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

      // Colours

      Colour BLACK = {0, 0, 0};
      Colour WHITE = {1, 1, 1};
      Colour RED   = {1, 0, 0};
      Colour GREEN = {0, 1, 0};
      Colour BLUE  = {0, 0, 1};
      Colour OPT1  = BLUE;
      Colour OPT2  = WHITE;
      Colour OPT3  = GREEN;
      Colour OPT4  = RED;

      // Consts
      int STROKE_WIDTH = 2;

      // Funcs
      static inline void set_colour(cairo_t *cr, Colour c) {
        cairo_set_source_rgb(cr, c.r, c.g, c.b);
      };

      // Shapes
      static inline void circle(cairo_t *cr, int x, int y, double r) {
        cairo_arc(cr, x, y, r, 0, 2 * M_PI);
      };

      static inline void rectangle(cairo_t *cr, int x, int y, int width, int height) {
        cairo_rectangle(cr, x, y, width, height);
      }

      static inline void fill(cairo_t *cr, Colour c) {
        set_colour(cr, c);
        cairo_fill(cr);
      }

      static inline void stroke(cairo_t *cr, Colour c) {
        set_colour(cr, c);
        cairo_stroke(cr);
      }

      static inline void fill_p(cairo_t *cr, Colour c) {
        set_colour(cr, c);
        cairo_fill_preserve(cr);
      }

      static inline void stroke_p(cairo_t *cr, Colour c) {
        set_colour(cr, c);
        cairo_stroke_preserve(cr);
      }
    }
  }
}

#endif
