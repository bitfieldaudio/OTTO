#pragma once

#include "util/jsonfile.hpp"

namespace otto {
  class DataFile : public util::JsonFile {
  public:
    void write() override;
    void read() override;
  };
}
