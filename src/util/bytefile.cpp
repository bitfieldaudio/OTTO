#include "util/bytefile.hpp"

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
    fstream.open(p, std::ios::in | std::ios::out | std::ios::binary);
    if (!fstream) {
      // File didnt exist, create it
      fstream.open(p, std::ios::trunc | std::ios::out | std::ios::binary);
      fstream.close();
      fstream.open(p, std::ios::in | std::ios::out | std::ios::binary);
    }
  }

  void ByteFile::close() {
    fstream.close();
  }

  void ByteFile::flush() {
    fstream.flush();
  }

  bool ByteFile::is_open() const {
    return fstream.is_open();
  }

  ByteFile::Position ByteFile::seek(Position p, std::ios::seekdir d) {
    if (!is_open()) throw Error(Error::Type::FileNotOpen);
    fstream.seekg(p, d);
    fstream.seekp(p, d);
    return p;
  }

  ByteFile::Position ByteFile::position() {
    if (!is_open()) throw Error(Error::Type::FileNotOpen);
    return fstream.seekp(fstream.tellg()).tellp();
  }

  ByteFile::Position ByteFile::size() {
    if (!is_open()) throw Error(Error::Type::FileNotOpen);
    auto p = fstream.tellg();
    auto end = fstream.seekg(0, std::fstream::end).tellg();
    fstream.seekg(p);
    return Position(end);
  }

} // top1
