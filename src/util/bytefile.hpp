#pragma once

#include <string>
// TODO: Replace with c++17 once implementations have it
#include <experimental/filesystem>
#include <iterator>
#include <utility>
#include <fstream>

#include "util/result.hpp"
#include "util/type_traits.hpp"

namespace top1 {

  namespace filesystem = std::experimental::filesystem;

  /// TODO: Documentation
  class ByteFile {
  public:

    struct Error {
      enum class Type {
        FileNotOpen,
        ExceptionThrown,
        BoundsExceeded
      } type;

      Error(Type t) : type (t) {}
    };

    using Position = int;
    using Path = filesystem::path;

    template<typename Ok, typename Err = Error>
    using result = result<Ok, Err>;

    // Initialization

    ByteFile();
    ByteFile(const Path&);

    ByteFile(ByteFile&) = delete;
    ByteFile(ByteFile&&);

    ByteFile& operator=(ByteFile);
    friend void swap(ByteFile&, ByteFile&);

    // Interface

    result<void> open(const Path&);
    result<void> close();
    result<void> flush();
    bool is_open() const;

    result<void> read_file();
    result<void> write_file();

    result<Position> seek(Position);
    result<Position> position();
    result<Position> size();

    template<typename OutIter,
      typename = std::enable_if<is_iterator_v<OutIter, std::byte,
                                  std::output_iterator_tag>>>
    result<void> read_bytes(OutIter&&, OutIter&&);

    template<typename OutIter,
      typename = std::enable_if<is_iterator_v<OutIter, std::byte,
                                  std::output_iterator_tag>>>
    result<void> read_bytes(OutIter&&, int);


    template<typename InIter,
      typename = std::enable_if<is_iterator_v<InIter, std::byte,
                                  std::input_iterator_tag>>>
    result<void> write_bytes(InIter&&, InIter&&);

    template<typename InIter,
      typename = std::enable_if<is_iterator_v<InIter, std::byte,
                                  std::input_iterator_tag>>>
    result<void> write_bytes(InIter&&, int);

    // Data
  protected:
    std::fstream fstream;
  };

  /*
   * Template definitions
   */

  template<typename OutIter, typename>
  ByteFile::result<void> ByteFile::read_bytes(OutIter&& f, OutIter&& l) {
    if (!is_open()) {return {Error::Type::FileNotOpen};}
    // If OutIter is a pointer, copy everything at once
    if constexpr (std::is_pointer_v<OutIter>) {
      fstream.read(f, l - f);
    } else {
      std::for_each(f, l, [&] (auto& b) {fstream.read(&b, 1);});
    }
  }

  template<typename OutIter, typename>
  ByteFile::result<void> ByteFile::read_bytes(OutIter&& iter, int n) {
    if (!is_open()) {return {Error::Type::FileNotOpen};}
    // If OutIter is a pointer, copy everything at once
    if constexpr (std::is_pointer_v<OutIter>) {
      fstream.read(iter, n);
    } else {
      for (int i = 0; i < n; i++, iter++) {
        fstream.read(&(*iter), 1);
      }
    }
  }

  template<typename InIter, typename>
  ByteFile::result<void> ByteFile::write_bytes(InIter&& f, InIter&& l) {
    if (!is_open()) {return {Error::Type::FileNotOpen};}
    // If InIter is a pointer, copy everything at once
    if constexpr (std::is_pointer_v<InIter>) {
      fstream.write(f, l - f);
    } else {
      std::for_each(f, l, [&] (auto& b) {fstream.write(&b, 1);});
    }
  }

  template<typename InIter, typename>
  ByteFile::result<void> ByteFile::write_bytes(InIter&& iter, int n) {
    if (!is_open()) {return {Error::Type::FileNotOpen};}
    // If InIter is a pointer, copy everything at once
    if constexpr (std::is_pointer_v<InIter>) {
      fstream.write(iter, n);
    } else {
      for (int i = 0; i < n; i++, iter++) {
        fstream.write(&(*iter), 1);
      }
    }
  }
}
