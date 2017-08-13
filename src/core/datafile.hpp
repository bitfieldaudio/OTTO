#pragma once

#include "util/jsonfile.hpp"

class DataFile : public top1::JsonFile {
public:
  void write() override;
  void read() override;
};
