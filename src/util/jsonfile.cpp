#include "jsonfile.hpp"

#include <fstream>
#include <json.hpp>

namespace otto::util {

  using json = nlohmann::json;

  JsonFile::JsonFile(const fs::path& p)
    : _path (p)
  {}

  void JsonFile::write(JsonFile::OpenOptions options)
  {
    if (auto ec = validate(); ec != ErrorCode::none) {
      throw exception(ec, "Error while writing preset file '{}'", _path.c_str());
    }
    errno = 0;
    std::ofstream stream(_path, std::ios::trunc);
    stream << std::setw(2) << _data << std::endl;
    stream.close();
    if (errno) {
      throw std::system_error(errno, std::system_category());
    }
  }

  void JsonFile::read(JsonFile::OpenOptions options)
  {
    std::ifstream stream;
    stream.open(_path);
    if (!stream) {
      if ((options & OpenOptions::create) != OpenOptions::none) {
        stream.close();
        write(options);
        stream.open(_path);
      }
    }
    if (!stream) {
      throw std::system_error(errno, std::system_category());
    }
    _data.clear();
    stream >> _data;
    stream.close();
    if (auto ec = validate(); ec != ErrorCode::none) {
      throw exception(ec, "Error while reading preset file '{}'", _path.c_str());
    }
  }

#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wreturn-type"
  std::string to_string(JsonFile::ErrorCode ec)
  {
    using ErrorCode = JsonFile::ErrorCode;
    switch (ec) {
    case ErrorCode::none: return "";
    case ErrorCode::invalid_json: return "Invalid json";
    case ErrorCode::missing_header: return "OTTO Preset header missing";
    case ErrorCode::unknown_version: return "Unknown preset format version";
    case ErrorCode::invalid_data: return "Invalid preset data. Take a look at the specification again";
    }
  }
#pragma GCC diagnostic pop
}
