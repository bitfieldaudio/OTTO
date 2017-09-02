#pragma once

#include <string>
// TODO: Replace with c++17 once implementations have it
// #include <experimental/filesystem>
#include <iterator>
#include <utility>
#include <fstream>

#include "util/result.hpp"
#include "util/type_traits.hpp"

namespace top1 {

  // namespace filesystem = std::experimental::filesystem;

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
    using Path = std::string;

    template<std::size_t len>
    struct bytes {
      std::byte data[len];

      bytes() = default;

      bytes(bytes& o) {
        std::copy(o.begin(), o.end(), data);
      }

      bytes(const std::initializer_list<std::byte> bs) {
        data = bs;
      }

      template<typename Num = int_n_bytes_u_t<len>&>
      bytes (int_n_bytes_u_t<len> d) {
        cast<Num>() = d;
      }
      
      std::byte* begin() {return data;}
      std::byte* end() {return data + len;}

      bool operator==(const bytes& rhs) const {
        std::equal(begin(), end(), rhs.begin());
      }

      bool operator==(const char* rhs) const {
        std::equal(begin(), end(), rhs);
      }

      template<typename T>
      T& cast() {
        return *reinterpret_cast<T*>(data);
      }

      int_n_bytes_t<len>& as_i() {
        return cast<int_n_bytes_t<len>>();
      }

      int_n_bytes_u_t<len>& as_u() {
        return cast<int_n_bytes_u_t<len>>();
      }

      operator int_n_bytes_u_t<len>() {
        return as_u();
      }

      explicit operator char*() const {
        return (char*) data;
      }
      
    };
    
    struct Chunk {
      ByteFile& file;
      Position offset;

      bytes<4> id;
      bytes<4> size;

      Chunk(ByteFile& file) : file (file) {}
      Chunk(Chunk& o) : file (o.file), id (o.id), size (o.size) {}

      void seek_to() {
        file.seek(size.cast<std::uint32_t>());
      }

      void seek_past() {
        file.seek(offset + size.cast<std::uint32_t>());
      }

      void write() {
        offset = file.position();
        file.write_bytes(id);
        file.write_bytes(size);
        write_fields();
      }

      virtual void write_fields() {}

      void read() {
        offset = file.position();
        file.read_bytes(id);
        file.read_bytes(size);
        read_fields();
      }

      virtual void read_fields() {}
    };

    // Initialization

    ByteFile();
    ByteFile(const Path&);

    ByteFile(ByteFile&) = delete;
    ByteFile(ByteFile&&);
    virtual ~ByteFile();

    ByteFile& operator=(ByteFile);
    friend void swap(ByteFile&, ByteFile&);

    // Interface

    void open(const Path&);
    void close();
    void flush();
    bool is_open() const;

    Position seek(Position, std::ios::seekdir = std::ios::beg);
    Position position();
    Position size();

    template<typename OutIter,
      typename = std::enable_if<is_iterator_v<OutIter, std::byte,
                                  std::output_iterator_tag>>>
    void read_bytes(OutIter, OutIter);

    template<typename OutIter,
      typename = std::enable_if<is_iterator_v<OutIter, std::byte,
                                  std::output_iterator_tag>>>
    void read_bytes(OutIter, int);

    template<std::size_t N>
    void read_bytes(bytes<N>&);

    template<typename InIter,
      typename = std::enable_if<is_iterator_v<InIter, std::byte,
                                  std::input_iterator_tag>>>
    void write_bytes(InIter, InIter);

    template<typename InIter,
      typename = std::enable_if<is_iterator_v<InIter, std::byte,
                                  std::input_iterator_tag>>>
    void write_bytes(InIter, int);

    template<std::size_t N>
    void write_bytes(const bytes<N>&);

    template<typename F>
    auto for_chunks_in_range(Position, Position, F&& f) ->
    std::enable_if_t<std::is_invocable_v<F, Chunk&>, void>;

    // Data
  protected:
    std::fstream fstream;
  };

  /*
   * Template definitions
   */

  template<typename OutIter, typename>
  void ByteFile::read_bytes(OutIter f, OutIter l) {
    if (!is_open()) throw Error(Error::Type::FileNotOpen);
    // If OutIter is a pointer, copy everything at once
    if constexpr (std::is_pointer_v<OutIter>) {
        fstream.read((char*) f, l - f);
      } else {
      std::for_each(f, l, [&, ptr = (char*) nullptr] (auto& b) {
          fstream.read(ptr, 1);
          *b = *ptr;
        });
    }
  }

  template<typename OutIter, typename>
  void ByteFile::read_bytes(OutIter iter, int n) {
    if (!is_open()) throw Error(Error::Type::FileNotOpen);
    // If OutIter is a pointer, copy everything at once
    if constexpr (std::is_pointer_v<OutIter>) {
        fstream.read((char*) iter, n);
      } else {
      char* ptr;
      for (int i = 0; i < n; i++, iter++) {
        fstream.read(ptr, 1);
        *iter = std::byte(*ptr);
      }
    }
  }

  template<std::size_t N>
  void ByteFile::read_bytes(bytes<N>& bs) {
    fstream.read((char*)bs, N);
  }

  template<typename InIter, typename>
  void ByteFile::write_bytes(InIter f, InIter l) {
    if (!is_open()) throw Error(Error::Type::FileNotOpen);
    // If InIter is a pointer, copy everything at once
    if constexpr (std::is_pointer_v<InIter>) {
        fstream.write((char*)f, l - f);
      } else {
      std::for_each((char*)f, l, [&] (auto& b) {fstream.write((char*)&b, 1);});
    }
  }

  template<typename InIter, typename>
  void ByteFile::write_bytes(InIter iter, int n) {
    if (!is_open()) throw Error(Error::Type::FileNotOpen);
    // If InIter is a pointer, copy everything at once
    if constexpr (std::is_pointer_v<InIter>) {
        fstream.write((char*)iter, n);
      } else {
      for (int i = 0; i < n; i++, iter++) {
        fstream.write((char*)&(*iter), 1);
      }
    }
  }

  template<std::size_t N>
  void ByteFile::write_bytes(const bytes<N>& bs) {
    fstream.write((char*)bs, N);
  }

  template<typename F>
  auto ByteFile::for_chunks_in_range(Position i, Position o, F &&f) ->
  std::enable_if_t<std::is_invocable_v<F, Chunk&>, void> {
    seek(i);
    while (position() < o) {
      Chunk chunk(*this);
      chunk.read();
      chunk.seek_to();

      std::invoke(std::forward<F>(f), chunk);

      chunk.seek_past();
    }
  }
}
