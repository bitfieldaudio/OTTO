#pragma once

#include "..\dyn-array.hpp"
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
          blackmanHarris
      };

      /// Instantiates the Window, and computes the window samples.
      Window (int size, WindowType type, bool normalize = true);

      /// Recomputes the window samples, given the new size, window type, and normalization settings.
      void reset (int size, WindowType type, bool normalize = true) noexcept;

      /// Multiplies the buffer and the window, sample by sample
      void applyTo (double* buffer, int size) noexcept;


      ////////////////////////////////////////////////////////////////////////////////
      /// Window type to string
      static const std::string getWindowTypeName (WindowType) noexcept;

      /// Computes the window samples and stores them in the buffer
      static void compute (double* buffer, int size, WindowType, bool normalize = true) noexcept;
  private:
      dyn_array<double> windowBuffer;
  };
}
