#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <cinttypes>
#include <mutex>
#include <plog/Log.h>

#include "../utils.h"

namespace top1 {

using byte = char;
using u4b = uint32_t;
using u2b = uint16_t;

struct ReadException : public std::exception {
  enum Type {
    END_OF_FILE,
    UNEXPECTED_CHUNK,
    INVALID_SIZE,
    POSITION_MISMATCH,
  } type;

  std::string message = "No error message";

  const char * what () const throw () {
    return message.c_str();
  }

  ReadException() {};
  ReadException(std::string message) : message (message) {};
  ReadException(Type type) : type (type) {};
  ReadException(Type type, std::string message) :
    type (type),
    message (message) {};
};

class File {
public:

  /**
   * Provided here for when accessing the file.
   * This class will never lock the mutex itself.
   */
  std::recursive_mutex mutex;

  std::string path;

  struct Field {
    virtual size_t size() const = 0;
    virtual void read(File *file) = 0;
    virtual void write(File *file) = 0;
  };

  struct ChunkFCC {
    u4b name;

    ChunkFCC() {};
    ChunkFCC(u4b name) : name(name) {};
    ChunkFCC(const char *str) {
      name = *((u4b *)str);
    }

    bool operator==(const ChunkFCC &other) const {
      return name == other.name;
    }
    bool operator!=(const ChunkFCC &other) const {
      return name != other.name;
    }

    std::string str() const {
      return std::string((char *) &name, 4);
    }
  };

  class Chunk {
  protected:
    std::vector<Field*> fields;
  public:
    const ChunkFCC id;
    u4b size = 0;
    int offset = -1;

    Chunk() {};
    Chunk(ChunkFCC id) : id ( id) {};

    template<class T>
    void addField(T &field);

    void subChunk(Chunk &subChunk);

    virtual void read(File *file);
    virtual void write(File *file);
  };
protected:
  std::fstream fileStream;
  std::vector<Chunk *> chunks;

  void addChunk(Chunk &chunk);

public:

  template<class T>
  void readBytes(T *ptr, int length);
  template<class T>
  void readBytes(T &bytes);

  template<class T>
  T readBytes();

  template<class T>
  void writeBytes(T *ptr, int length);
  template<class T>
  void writeBytes(T &bytes);

  void fseek(uint pos);
  uint rpos() {return fileStream.tellg(); }
  uint wpos() {return fileStream.tellp(); }

  bool skipChunkR(Chunk &chunk);
  bool skipChunkW(Chunk &chunk);

  Chunk getChunk();

  void writeChunks();

  void readChunks();

  struct Error {
    enum {
      NONE,
      ERROR
    } status;

    std::string message;

    operator bool() {
      return status != NONE;
    }

    bool log() {
      LOGE_IF(*this) << message;
      return bool(*this);
    }
  } error;

  File() {}
  File(std::string path) {
    open(path);
  }

  virtual ~File() {};

  virtual void open(std::string path);
  virtual void close();
  virtual void flush();

  virtual void writeFile();
  virtual void readFile();
};

template<class T>
struct TypedField : public File::Field {
  T *data;

  TypedField(T *data) : data (data) {}

  size_t size() const override {
    return sizeof(T);
  }

  void read(File *file) override {
    *data = file->readBytes<T>();
  }
  void write(File *file) override {
    file->writeBytes<T>(*data);
  }
};

template<>
struct TypedField<File::Chunk> : public File::Field {
  File::Chunk *chunk;

  TypedField(File::Chunk *data) : chunk (data) {}

  size_t size() const override {
    return chunk->size;
  }

  void read(File *file) override {
    chunk->read(file);
  }
  void write(File *file) override {
    chunk->write(file);
  }
};

inline void File::Chunk::subChunk(File::Chunk &chunk) {
  addField<File::Chunk>(chunk);
}

template<class T>
void File::Chunk::addField(T &field) {
  Field *tField = new TypedField<T>(&field);
  fields.push_back(tField);
  size += tField->size();
}

template<class T>
void File::readBytes(T *ptr, int length) {
  fileStream.read((char *)ptr, sizeof(T) * length);
  if (fileStream.eof())
    throw ReadException(ReadException::END_OF_FILE, "readBytes: EOF");
}

template<class T>
void File::readBytes(T &bytes) {
  fileStream.read((char*) &bytes, sizeof(bytes));
  if (fileStream.eof())
    throw ReadException(ReadException::END_OF_FILE, "readBytes: EOF");
}

template<class T>
T File::readBytes() {
  T bytes;
  readBytes<T>(bytes);
  return bytes;
}

template<class T>
void File::writeBytes(T *ptr, int length) {
  fileStream.write((char *) ptr, sizeof(T) * length);
}

template<class T>
void File::writeBytes(T &bytes) {
  // LOGD << bytes.str();
  fileStream.write((char*) &bytes, sizeof(bytes));
}

}
