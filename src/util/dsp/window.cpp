#include "window.hpp"
#include <cmath>

namespace otto::util::dsp {

  Window::Window (int size, WindowType type, bool normalize) : windowBuffer(size)
  {
      reset (size, type, normalize);
  }


  void Window::reset (int size, WindowType type, bool normalize) noexcept
  {
      windowBuffer.resize (size);
      compute (windowBuffer.begin(), size, type, normalize);
  }


  void Window::compute (double* buffer, int size, WindowType type, bool normalize) noexcept
  {
      auto cosn = [](int n, int i, int size) { return cos (static_cast<double> (n * M_PI * i) / static_cast<double> (size - 1)); };

      switch (type)
      {
          case rectangular:
          {
              for (int i = 0; i < size; ++i)
                  buffer[i] = 1.0;
          }
          break;

          case triangular:
          {
              auto middlePosition = 0.5 * static_cast<double> (size - 1);

              for (int i = 0; i < size; ++i)
                  buffer[i] = 1.0 - std::abs ((static_cast<double> (i) - middlePosition) / middlePosition);
          }
          break;

          case hann:
          {
              for (int i = 0; i < size; ++i)
              {
                  auto cos2 = cosn (2, i, size);
                  buffer[i] = 0.5 - 0.5 * cos2;
              }
          }
          break;

          case hamming:
          {
              for (int i = 0; i < size; ++i)
              {
                  auto cos2 = cosn (2, i, size);
                  buffer[i] = 0.54 - 0.46 * cos2;
              }
          }
          break;

          case blackman:
          {
              for (int i = 0; i < size; ++i)
              {
                  auto cos2 = cosn (2, i, size);
                  auto cos4 = cosn (4, i, size);

                  buffer[i] = 0.42 - 0.5 * cos2 + 0.08 * cos4;
              }
          }
          break;

          case blackmanHarris:
          {
              for (int i = 0; i < size; ++i)
              {
                  auto cos2 = cosn (2, i, size);
                  auto cos4 = cosn (4, i, size);
                  auto cos6 = cosn (6, i, size);

                  buffer[i] = 0.35875 - 0.48829 * cos2 + 0.14128 * cos4 - 0.01168 * cos6;
              }
          }
          break;
          default:
              break;
      }

      if (normalize)
      {
          double sum = 0.0;
          for (int i = 0; i < size; ++i)
              sum += buffer[i];

          auto factor = static_cast<double> (size) / sum;

          for (int j = 0; j < size; ++j)
            buffer[j] *= factor;
      }
  }


  void Window::applyTo (double* buffer, int size) noexcept
  {
      const int rs = std::min<int>(size, windowBuffer.size());
      for (int j = 0; j < rs; ++j)
        buffer[j] *= windowBuffer[j];
  }


  const std::string Window::getWindowTypeName (WindowType type) noexcept
  {
      switch (type)
      {
          case rectangular:       return "Rectangular";
          case triangular:        return "Triangular";
          case hann:              return "Hann";
          case hamming:           return "Hamming";
          case blackman:          return "Blackman";
          case blackmanHarris:    return "Blackman-Harris";
          default:                return "";
      }
  }

}
