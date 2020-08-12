#include "testing.t.hpp"

#include "lib/util/i2c.hpp"

#include "lib/logging.hpp"

using namespace otto;

struct hex {
  std::uint8_t data;
  friend std::ostream& operator<<(std::ostream& str, const hex& self)
  {
    auto flags = str.flags();
    auto& res = str << std::setfill('0') << std::setw(2) << std::hex << (int) self.data;
    str.flags(flags);
    return res;
  }
};

TEST_CASE ("i2ccli" * doctest::skip()) {
  util::I2C i2c_obj;
  while (std::cin.good()) {
    std::vector<std::uint8_t> buffer;
    std::string line;
    std::cout << "\n> ";
    std::getline(std::cin, line);
    auto stream = std::stringstream(line);
    std::string cmd;
    std::getline(stream, cmd, ' ');
    if (cmd == "o") {
      std::string path;
      int addr = -1;
      stream >> path;
      stream >> addr;
      if (addr < 0 || path.empty()) {
        std::cout << "Usage: o <path> <i2c address>" << std::endl;
        continue;
      }
      std::cout << "Opening " << path << " with address " << hex{static_cast<std::uint8_t>(addr)} << std::endl;
      i2c_obj = addr;
      auto ec = i2c_obj.open(path);
      if (ec) {
        std::cout << "error opening i2c device: " << ec << std::endl;
        continue;
      }
    }
    if (!i2c_obj.is_open()) {
      std::cout << "Use o <path> <i2c address> to open an i2c device first" << std::endl;
      continue;
    }
    if (cmd == "w") {
      std::string arg;
      while (std::getline(stream, arg, ' ')) {
        errno = 0;
        std::uint8_t byte = std::strtol(arg.c_str(), nullptr, 16);
        if (errno != 0) {
          std::cout << "Error parsing: " << strerror(errno) << std::endl;
          continue;
        }
        buffer.push_back(byte);
      }
      if (buffer.size() == 0) {
        std::cout << "Usage: w <space separated bytes>" << std::endl;
        continue;
      }
      std::cout << "Writing ";
      for (auto b : buffer) std::cout << hex{b} << " ";
      std::cout << std::endl;
      if (auto err = i2c_obj.write(buffer)) {
        std::cout << "Error: " << err.message() << std::endl;
      }
    } else if (cmd == "r") {
      int arg = -1;
      stream >> arg;
      if (arg < 1) {
        std::cout << "Expected count larger than 0. Usage: r <count>" << std::endl;
        continue;
      }
      buffer.resize(arg);
      std::cout << std::dec << "Reading " << arg << " bytes" << std::endl;
      if (auto err = i2c_obj.read_into(buffer)) {
        std::cout << "Error: " << err.message() << std::endl;
        continue;
      }
      std::cout << "Result: ";
      for (auto b : buffer) std::cout << hex{b} << " ";
      std::cout << std::endl;
    } else if (cmd == "q") {
      break;
    } else {
      std::cout << R"(
Commands:
  o <path> <i2c address>           Open i2c device
  w <space separated bytes>        write bytes to i2c
  r <count>                        read <count> bytes from i2c
  q                                quit
)";
    }
  }
}
