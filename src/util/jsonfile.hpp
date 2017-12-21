#pragma once

#include <string>
#include <json.hpp>

#include "filesystem.hpp"
#include "util/exception.hpp"
#include "util/macros.hpp"

namespace otto::util {

  struct JsonFile {

    enum struct ErrorCode {
      none = 0,
      invalid_json,
      missing_header,
      unknown_version,
      invalid_data
    };

    using exception = util::as_exception<ErrorCode>;

    enum struct OpenOptions {
      none   = 0b0, /// default options
      create = 0b1  /// create file if it doesnt exist
    };

    /// Constructor
    ///
    /// \postconditions `path() == p`
    /// \remarks remember to `read()` after construction
    explicit JsonFile(const fs::path& p);

    /// Virtual destructor
    virtual ~JsonFile() = default;

    /// Write the data to file
    ///
    /// \effects serialize `data()`, and write it to `path()`. No filestreams
    /// are left open.
    /// 
    /// \throws `exception` on parse failure, `fs::filesystem_error` or
    /// `std::system_error` on IO failure
    virtual void write(OpenOptions = OpenOptions::none);

    /// Read the data from file
    ///
    /// \effects deserialize the data in `path()` and store it in `data()`. No
    /// filestreams are left open.
    /// 
    /// \throws `exception` on parse failure, `fs::filesystem_error` or
    /// `std::system_error` on IO failure
    virtual void read(OpenOptions = OpenOptions::none);

    /// Access the stored data
    nlohmann::json& data() noexcept { return _data; }

    /// Access the stored data
    const nlohmann::json& data() const noexcept { return _data; }

    /// Access the path to the file
    const fs::path& path() const noexcept { return _path; }

  protected:

    /// Validate the json data
    ///
    /// This should be implemented by classes that inherit from this one. It is
    /// called in `read` and `write`, and should be used to validate the json data.
    virtual ErrorCode validate() const { return ErrorCode::none; };

    nlohmann::json _data = {};
    const fs::path _path;
  };

  /// String representation of `JsonFile::ErrorCode`.
  ///
  /// This is used by `util::as_exception` to print the error message.
  std::string to_string(JsonFile::ErrorCode);

  // Defines bitwise operations for JsonFile::OpenOptions
  MAKE_ENUM_OPERATORS(JsonFile::OpenOptions)
}
