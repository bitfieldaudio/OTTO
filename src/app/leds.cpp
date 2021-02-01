#include "leds.hpp"

#include <string>

#include "lib/util/exception.hpp"

namespace otto {

  std::ostream& operator<<(std::ostream& os, LEDColor lc)
  {
    return os << fmt::format("#{:02X}{:02X}{:02X}", lc.r, lc.g, lc.b);
  }

  void LEDColor::serialize_into(json::value& json) const
  {
    json = fmt::format("#{:02X}{:02X}{:02X}", r, g, b);
  }

  void LEDColor::deserialize_from(const json::value& json)
  {
    auto str = std::string(json);
    if (str.size() != 7) {
      throw util::exception("Expected string of length 7 when deserializing LEDColor. Got string '{}'", str);
    }
    if (str[0] != '#') {
      throw util::exception("Expected first character of string to be '#' when deserializing LEDColor. Got string '{}'",
                            str);
    }
    str = std::move(str).substr(1);
    if (str.find_first_not_of("0123456789ABCDEFabcdef") != str.npos) {
      throw util::exception("Invalid character in hex code when deserializing LEDColor. Got string '#{}'", str);
    }
    int num = std::stoi(str, nullptr, 16);
    r = (num & 0xFF0000) >> 16;
    g = (num & 0x00FF00) >> 8;
    b = (num & 0x0000FF);
  }
} // namespace otto
