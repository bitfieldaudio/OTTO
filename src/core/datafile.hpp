#pragma once

#include "util/jsonfile.hpp"

namespace otto {

  /// The `data/modules.json` file.
  ///
  /// This file contains all the data serialized, and takes care of calling the
  /// correct serialization/deserilization functions on write/read.
  class DataFile : public util::JsonFile {
  public:
    void write() override;
    void read() override;
  };
}
