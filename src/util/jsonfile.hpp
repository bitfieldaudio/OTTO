#pragma once

#include <fstream>
#include <string>
#include <plog/Log.h>

#include "util/tree.hpp"

namespace top1 {

class JsonFile {
public:

  std::string path;

  tree::Node data;

  JsonFile() {}

  JsonFile(const std::string& _path) : JsonFile() {
    path = _path;
  }

  JsonFile(JsonFile&) = delete;
  JsonFile(JsonFile&&) = delete;

  virtual void write();
  virtual void read();
};

}
