#pragma once

namespace otto::util::dsp {
  class LogSlider
  {
  public:
      LogSlider();
      ~LogSlider();

      double proportionOfLengthToValue(double proportion);
      double valueToProportionOfLength(double value);
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
