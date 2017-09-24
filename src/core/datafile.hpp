#pragma once

#include "util/jsonfile.hpp"

namespace top1 {
  class DataFile : public top1::JsonFile {
    public:
    void write() override;
    void read() override;
  };
}
