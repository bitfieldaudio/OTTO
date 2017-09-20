#include "util/bytefile.hpp"

#include <plog/Log.h>
#include <fmt/format.h>

namespace top1 {

  /****************************************/
  /* ByteFile Implementation              */
  /****************************************/

  ByteFile::ByteFile() {}

  ByteFile::ByteFile(const Path& p) {
    open(p);
  }

  ByteFile::ByteFile(ByteFile&&) {
    // TODO: Do moves
  }

  ByteFile::~ByteFile() {
    if (is_open()) {
      close();
    }
  }

  ByteFile& ByteFile::operator=(ByteFile other) {
    swap(*this, other);
    return *this;
  }

  void swap(ByteFile& first, ByteFile& sec) {
    using std::swap;
    // TODO: Do swaps;
  }

  void ByteFile::open(const Path& p) {
    if (is_open()) {
      throw "File already open";
    }
    path = p;
    fstream.open(p, std::ios::in | std::ios::out | std::ios::binary);
    if (!fstream) {
      // File didnt exist, create it
      create_file();
    }
    read_file();
  }

  void ByteFile::close() {
    if (fstream.is_open()) {
      write_file();
      fstream.close();
    };
  }

  void ByteFile::flush() {
    if (fstream.is_open()) {
      write_file();
      fstream.flush();
    };
  }

  void ByteFile::create_file() {
    close();
    fstream.open(path, std::ios::trunc | std::ios::out | std::ios::binary);
    fstream.close();
    fstream.open(path, std::ios::in | std::ios::out | std::ios::binary);
    write_file();
  }

  void ByteFile::read_file() {
    seek(0);
  }
  void ByteFile::write_file() {
    seek(0);
  }

  bool ByteFile::is_open() const {
    return fstream.is_open();
  }

  ByteFile::Position ByteFile::seek(Position p, std::ios::seekdir d) {
    if (!is_open()) throw Error(Error::Type::FileNotOpen, "ByteFile::seek(p, d)");
    if (p < 0 && d == std::ios::beg) {
      p = 0;
    }
    fstream.seekg(p, d);
    return p;
  }

  ByteFile::Position ByteFile::position() {
    if (!is_open()) throw Error(Error::Type::FileNotOpen, "ByteFile::position()");
    auto r = fstream.tellg();
    if (!fstream.good()) {
      fstream.clear();
      throw Error(Error::Type::ExceptionThrown,
        std::strerror(errno));
    }
    return r;
  }

  ByteFile::Position ByteFile::size() {
    if (!is_open()) throw Error(Error::Type::FileNotOpen, "ByteFile::size()");
    auto p = fstream.tellg();
    auto end = fstream.seekg(0, std::fstream::end).tellg();
    fstream.seekg(p);
    return Position(end);
  }

} // top1
