#pragma once

#include "jsonfile.h"

class DataFile : public top1::JsonFile {
public:
  void write() override;
  void read() override;
};
