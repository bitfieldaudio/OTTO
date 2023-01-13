#include "json.hpp"

#include <fstream>

namespace otto::json {

  value parse_file(const std::filesystem::path& path)
  {
    std::ifstream f(path);
    return value::parse(f, nullptr, true, true);
  }

  void write_to_file(const value& v, const std::filesystem::path& path)
  {
    std::ofstream file;
    file.open(path);
    file << v.dump(4) << std::endl;
    file.close();
  }

} // namespace otto::json
