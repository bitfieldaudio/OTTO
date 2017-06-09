#pragma once

#include <fstream>
#include <string>
#include <plog/Log.h>

#include "tree.h"

namespace top1 {

class JsonFile {
public:

  std::string path;

  tree::Node data;

  JsonFile() {}

  JsonFile(std::string path) : JsonFile() {
    path = path;
  }

  JsonFile(JsonFile&) = delete;
  JsonFile(JsonFile&&) = delete;

  virtual void write();
  virtual void read();
};

}
