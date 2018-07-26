#include <cmath>
#include "window.hpp"

namespace otto::util::dsp {

  Window::Window (int size, WindowType type, bool normalize) : window_buffer(size)
  {
      reset (size, type, normalize);
  }


  void Window::reset (int size, WindowType type, bool normalize) noexcept
  {
      window_buffer.resize (size);
      compute (gsl::span(window_buffer.begin(), size), type, normalize);
  }


  void Window::compute (gsl::span<double> buffer, WindowType type, bool normalize) noexcept
  {
      auto cosn = [](int n, int i, int size) { return cos (static_cast<double> (n * M_PI * i) / static_cast<double> (size - 1)); };
      auto size = buffer.size();

      switch (type)
      {
          case rectangular:
          {
              for (auto& sample : buffer)
                  sample = 1.0;
          }
          break;

          case triangular:
          {
              auto middle_position = 0.5 * static_cast<double> (size - 1);
              for (int i = 0; i < size; ++i)
                  buffer[i] = 1.0 - std::abs ((static_cast<double> (i) - middle_position) / middle_position);
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

          case blackman_harris:
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
          for (auto& sample : buffer)
              sum += sample;

          auto factor = static_cast<double> (size) / sum;

          for (auto& sample : buffer)
              sample *= factor;
      }
  }


  void Window::apply_to (gsl::span<double> buffer) noexcept
  {
      const int rs = std::min<int>(buffer.size(), window_buffer.size());
      for (int j = 0; j < rs; ++j)
        buffer[j] *= window_buffer[j];
  }


  const std::string Window::get_window_type_name (WindowType type) noexcept
  {
      switch (type)
      {
          case rectangular:       return "Rectangular";
          case triangular:        return "Triangular";
          case hann:              return "Hann";
          case hamming:           return "Hamming";
          case blackman:          return "Blackman";
          case blackman_harris:    return "Blackman-Harris";
          default:                return "";
      }
  }

}
