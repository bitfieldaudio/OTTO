#pragma once

namespace otto::util::dsp {
  /**
   * This utility transforms a linear proportion between 0 and 1 to
   * logarithmically scaled values in a given range. It also does them
   * inverse transformation.
   *
   *   x: proportion          (0)   |-----------|(1)
   *   y: value        (min_value)  |-----------|(max_value)
   *
   * Internally solves the following system of equations:
   *   ```
   *   y = a * exp(b * x)
   *   (x1;y1) = (0;min_value)
   *   (x2;y2) = (1;max_value)
   *   ```
   *
   * Particularly useful, e.g. for logarithmically scaled frequency cutoff knobs.
   */
  struct LogSlider {
    LogSlider() = default;
    ~LogSlider() = default;

    /// Transforms a linear proportion between 0 and 1 to logarithmically scaled values.
    /// \param proportion must be in range [0;1]
    double proportion_of_length_to_value(double proportion) noexcept;

    /// Transforms a logarithmically scaled value to the slider's
    /// corresponding proportion of length.
    /// \param value is expected to be between `min_value` and `max_value`
    double value_to_proportion_of_length(double value) noexcept;

    /// Sets the desired logarithmically scaled output range.
    /// \param new_minimum
    /// \param new_maximum
    void set_range(double new_minimum = 1, double new_maximum = 10);

  private:
    // below log transform coefficients
    double a;
    double b;
    void update_log_coefficients();
    double min_value;
    double max_value;
  };
} // namespace otto::util::dsp
