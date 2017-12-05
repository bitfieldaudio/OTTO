#pragma once

#include "util/jsonfile.hpp"

namespace otto {

  /// The `data/modules.json` file.
  ///
  /// This file contains all the data serialized, and takes care of calling the
  /// correct serialization/deserilization functions on write/read.
  struct DataFile : util::JsonFile {

    using util::JsonFile::ErrorCode;
    using util::JsonFile::exception;
    using util::JsonFile::OpenOptions;

    using util::JsonFile::JsonFile;

    /// Write the data to file
    ///
    /// \effects serialize `data()`, and write it to `path()`. No filestreams
    /// are left open.
    ///
    /// \throws `exception` on parse failure, `fs::filesystem_error` or
    /// `std::system_error` on IO failure
    void write(OpenOptions = OpenOptions::none) override;

    /// Read the data from file
    ///
    /// \effects deserialize the data in `path()` and store it in `data()`. No
    /// filestreams are left open.
    ///
    /// \throws `exception` on parse failure, `fs::filesystem_error` or
    /// `std::system_error` on IO failure
    void read(OpenOptions = OpenOptions::none) override;

  };
}
