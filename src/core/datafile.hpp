#pragma once

#include "util/jsonfile.hpp"

namespace top1 {
  class DataFile : public util::JsonFile {
  public:
    void write() override;
    void read() override;
  };
}
