#include "datafile.h"
#include "../module.h"
#include "../globals.h"

namespace top1 {

struct ModuleChunk : public File::Chunk {
  module::Module *m;

  ModuleChunk(fourCC id, module::Module *m) : Chunk(id), m (m) {}

  void read(File *file) override {
    if (offset < 0) {
      offset = file->rpos();
    }
    file->fseek(offset);
    if (id.name != file->readBytes<u4b>()) {
      throw ReadException(
        ReadException::UNEXPECTED_CHUNK, "UNEXPECTED_CHUNK");
    }
    uint fsize = file->readBytes<u4b>();
    uint end = file->rpos() + fsize;
    std::vector<byte> vect;
    vect.reserve(fsize);
    file->readBytes(vect.data(), fsize);
    m->deserialize(vect);
    file->fseek(end);
  }

  void write(File *file) override {
    auto data = m->serialize();
    size = data.size();
    if (offset < 0) {
      offset = file->wpos();
    }
    file->fseek(offset);
    file->writeBytes(id);
    file->writeBytes(size);

    uint end = file->wpos() + size;
    file->writeBytes(data.data(), size);
    if (end != file->wpos()) {
      // ERROR
    }
  }
};

DataFile::DataFile() : File() {
  addChunk(header);
  moduleChunks.push_back(ModuleChunk('TAPE', &GLOB.tapedeck));
  moduleChunks.push_back(ModuleChunk('MIXE', &GLOB.mixer));
  moduleChunks.push_back(ModuleChunk('SNTH', &GLOB.synth));
  moduleChunks.push_back(ModuleChunk('EFCT', &GLOB.effect));
  for (auto m : moduleChunks) {
    addChunk(m);
  }
}
}
