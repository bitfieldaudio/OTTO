#pragma once

#include "top1file.h"

namespace top1 {

class DataFile : public File {
  std::vector<Chunk> moduleChunks;
public:
  struct HeaderChunk : public Chunk {
    u2b version = 1;

    HeaderChunk() : Chunk("TP1D") {
      addField(version);
    };
  } header;

  DataFile();

  DataFile(std::string path) : DataFile() {
    open(path);
  }

  DataFile(DataFile&) = delete;
  DataFile(DataFile&&) = delete;

};
}
