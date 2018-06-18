#pragma once

namespace otto::util::dsp {
  struct LogSlider
  {
    LogSlider() = default;
    ~LogSlider() = default;

    double proportion_of_length_to_value(double proportion) noexcept;
    double value_to_proportion_of_length(double value) noexcept;
    void set_range(double new_minimum = 1, double new_maximum = 10);

  private:
      // below log transform coefficients
      double a;
      double b;
      void update_log_coefficients();
      double min_value;
      double max_value;
  };
}
