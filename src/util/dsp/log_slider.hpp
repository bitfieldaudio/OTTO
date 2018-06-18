#pragma once

namespace otto::util::dsp {
  struct LogSlider
  {
    LogSlider() = default;
    ~LogSlider() = default;

    double proportionOfLengthToValue(double proportion) noexcept;
    double valueToProportionOfLength(double value) noexcept;
    void setRange(double newMinimum = 1, double newMaximum = 10);

  private:
      // below log transform coefficients
      double a;
      double b;
      void updateLogCoefficients();
      double minValue;
      double maxValue;
  };
}
