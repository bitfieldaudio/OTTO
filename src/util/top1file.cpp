#include <exception>
#include <fmt/format.h>
#include "top1file.hpp"

namespace top1 {

  void File::Chunk::read(File *file) {
    if (offset < 0) {
      offset = file->rpos();
    }
    file->fseek(offset);
    ChunkFCC rName = file->readBytes<u4b>();
    if (id.name != rName.name) {
      throw ReadException(
                          ReadException::UNEXPECTED_CHUNK,
                          fmt::format("Unexpected chunk name at {:#x}: Got {:#x} expected {:#x}",
                                      offset, rName.name, id.name));
    }
    uint fsize;
    if ((fsize = file->readBytes<u4b>()) < size) {
      throw ReadException(
                          ReadException::INVALID_SIZE, "INVALID_CHUNK_SIZE");
    }
    this->size = fsize;
    uint end = file->rpos() + fsize;
    for (auto field : fields) {
      field->read(file);
    }
    uint chunksStart = file->rpos();
    for (auto chunk : chunks) {
      if (chunk->offset < 0) {
        file->fseek(chunksStart);
        uint lastPos = file->rpos();
        while (file->rpos() < end) {
          try {
            Chunk c = file->getChunk();
            if (c.id == chunk->id) {
              chunk->read(file);
            } else if (c.id.name == 0) {
              break;
            } else {
              file->skipChunkR(c);
              if (file->rpos() == lastPos) break;
              lastPos = file->rpos();
            }
          } catch (const ReadException& e) {
            if (e.type != e.END_OF_FILE) LOGE << e.what();
            break;
          }
        }
      } else {
        chunk->read(file);
      }
    }
    file->fseek(end);
  }

  void File::Chunk::write(File *file) {
    if (offset < 0) {
      offset = file->wpos();
    }
    file->fseek(offset);
    file->writeBytes(id);
    file->writeBytes(size);

    uint end = file->wpos() + size;
    for (auto &&field : fields) {
      field->write(file);
    }
    for (auto &&chunk : chunks) {
      chunk->write(file);
    }
    if (end != file->wpos()) {
      // ERROR
    }
  }

  /****************************************/
  /* TOP1File Implementation              */
  /****************************************/

  // File handling
  void File::open(const std::string& path) {
    fileStream.open(path, std::ios::in | std::ios::out | std::ios::binary);
    if (!fileStream) {
      LOGI << "Empty file, creating";
      fileStream.open(path, std::ios::trunc | std::ios::out | std::ios::binary);
      fileStream.close();
      fileStream.open(path, std::ios::in | std::ios::out | std::ios::binary);
      writeFile();
      fileStream.flush();
    }
    fseek(0);
    readFile();
    this->path = path;
  }

  void File::close() {
    if (fileStream.is_open()) {
      LOGI << "Closing TOP1File '" << path << "'";
      writeFile();
      fileStream.close();
    }
  }

  void File::flush() {
    if (fileStream.is_open()) {
      writeFile();
      fileStream.flush();
    }
  }

  // Read/Write

  void File::fseek(uint pos) {
    fileStream.seekg(pos);
    fileStream.peek();
    if (fileStream.eof() || fileStream.fail()) {
      // LOGD << "EOF";
      fileStream.seekp(0, fileStream.end);
      fileStream.write(0, pos - fileStream.tellp());
      fileStream.clear();
      fileStream.seekg(pos);
    }
    if (fileStream.tellp() != pos) {
      LOGE << fmt::format("Couldnt seek past {:#x}", fileStream.tellp());
    }
  }

  // Chunk handling

  bool File::skipChunkR(Chunk &chunk) {
    uint newPos = chunk.offset + 4 + 4 + chunk.size;
    if (fileStream.tellg() != newPos) {
      fseek(newPos);
      if (fileStream.eof()) throw ReadException(ReadException::END_OF_FILE, "skipChunk: EOF");
      return true;
    }
    return false;
  }

  bool File::skipChunkW(Chunk &chunk) {
    uint newPos = chunk.offset + 4 + 4 + chunk.size;
    if (fileStream.tellp() != newPos) {
      fseek(newPos);
      if (fileStream.eof()) throw ReadException(ReadException::END_OF_FILE, "skipChunk: EOF");
      return true;
    }
    return false;
  }

  File::Chunk File::getChunk() {
    Chunk chunk (ChunkFCC(readBytes<u4b>()));
    chunk.size = readBytes<u4b>();
    fseek(rpos() - 8);
    chunk.offset = rpos();
    return chunk;
  }

  // Chunk registry

  void File::addChunk(Chunk &chunk) {
    chunks.emplace_back(&chunk);
  }

  void File::readChunks() {
    for (auto chunk : chunks) {
      if (chunk->offset < 0) {
        fseek(0);
        uint lastPos = rpos();
        while (!fileStream.eof()) {
          try {
            Chunk c = getChunk();
            if (c.id == chunk->id) {
              chunk->read(this);
            } else if (c.id.name == 0) {
              break;
            } else {
              skipChunkR(c);
              if (rpos() == lastPos) break;
              lastPos = rpos();
            }
          } catch (const ReadException& e) {
            if (e.type != e.END_OF_FILE) LOGE << e.what();
            break;
          }
        }
      } else {
        chunk->read(this);
      }
    }
  }

  void File::writeChunks() {
    for (auto chunk : chunks) {
      chunk->write(this);
    }
  }

  void File::writeFile() {
    writeChunks();
  }

  void File::readFile() {
    readChunks();
  }

}
