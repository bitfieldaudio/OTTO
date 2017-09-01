#include "util/bytefile.hpp"

namespace top1 {

  /****************************************/
  /* ByteFile Implementation              */
  /****************************************/

  ByteFile::ByteFile() {}

  ByteFile::ByteFile(const Path& p) {
    open(p).may_throw();
  }

  ByteFile::ByteFile(ByteFile&&) {
    // TODO: Do moves
  }

  ByteFile& ByteFile::operator=(ByteFile other) {
    swap(*this, other);
    return *this;
  }

  void swap(ByteFile& first, ByteFile& sec) {
    using std::swap;
    // TODO: Do swaps;
  }

  ByteFile::result<void> ByteFile::open(const Path& p) {
    try {
      fstream.open(p.c_str());
    } catch (...) {
      return Error{Error::Type::ExceptionThrown};
    }
    return {};
  }

  ByteFile::result<void> ByteFile::close() {
    try {
      fstream.close();
    } catch (...) {
      return Error{Error::Type::ExceptionThrown};
    }
    return {};
  }

  ByteFile::result<void> ByteFile::flush() {
    try {
      fstream.flush();
    } catch (...) {
      return Error{Error::Type::ExceptionThrown};
    }
    return {};
  }

  bool ByteFile::is_open() const {
    return fstream.is_open();
  }

  ByteFile::result<ByteFile::Position> ByteFile::seek(Position p) {
    if (!is_open()) {return {Error::Type::FileNotOpen};}
    try {
      fstream.seekg(p);
      fstream.seekp(p);
      return p;
    } catch (...) {
      return {Error::Type::ExceptionThrown};
    }
  }

  ByteFile::result<ByteFile::Position> ByteFile::position() {
    if (!is_open()) {return {Error::Type::FileNotOpen};}
    return {fstream.seekp(fstream.tellg()).tellp()};
  }

  ByteFile::result<ByteFile::Position> ByteFile::size() {
    if (!is_open()) {return {Error::Type::FileNotOpen};}
    auto p = fstream.tellg();
    auto end = fstream.seekg(0, std::fstream::end).tellg();
    fstream.seekg(p);
    return Position(end);
  }

} // top1
