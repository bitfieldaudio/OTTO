#pragma once

#include "util/dyn-array.hpp"
#include <string>

namespace otto::util::dsp {

  class Window
  {
  public:
      enum WindowType
      {
          rectangular,
          triangular,
          hann,
          hamming,
          blackman,
          blackman_harris
      };

      /// Instantiates the Window, and computes the window samples.
      Window (int size, WindowType type, bool normalize = true);

      /// Recomputes the window samples, given the new size, window type, and normalization settings.
      void reset (int size, WindowType type, bool normalize = true) noexcept;

      /// Multiplies the buffer and the window, sample by sample
      void apply_to (double* buffer, int size) noexcept;


      ////////////////////////////////////////////////////////////////////////////////
      /// Window type to string
      static const std::string get_window_type_name (WindowType) noexcept;

      /// Computes the window samples and stores them in the buffer
      static void compute (double* buffer, int size, WindowType, bool normalize = true) noexcept;
  private:
      dyn_array<double> window_buffer;
  };
}
