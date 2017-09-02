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

      bytes(const std::initializer_list<unsigned char> bs) {
        std::transform(bs.begin(), bs.end(), begin(),
          [] (auto uc) {return std::byte(uc);});
      }

      bytes(const char str[len + 1]) {
        std::copy(str, str + len + 1,
          reinterpret_cast<char*>(data));
      }

      template<std::size_t N = len, typename Num = int_n_bytes_u_t<N>>
      bytes (Num d) {
        cast<Num>() = d;
      }
      
      std::byte* begin() {return data;}
      std::byte* end() {return data + len;}
      const std::byte* begin() const {return data;}
      const std::byte* end() const {return data + len;}

      bool operator==(const bytes& rhs) const {
        return std::equal(begin(), end(), rhs.begin());
      }

      bool operator==(const char* rhs) const {
        return std::equal(begin(), end(), reinterpret_cast<const std::byte*>(rhs));
      }

      bool operator!=(const bytes& rhs) const {return !(*this == rhs);}
      bool operator!=(const char* rhs) const {return !(*this == rhs);}

      template<typename T>
      T& cast() {
        return *reinterpret_cast<std::decay_t<T>*>(data);
      }

      template<std::size_t N = len, typename Num = int_n_bytes_t<N>>
      Num& as_i() {
        return cast<Num>();
      }

      template<std::size_t N = len, typename Num = int_n_bytes_u_t<N>>
      Num& as_u() {
        return cast<Num>();
      }

      explicit operator char*() const {
        return (char*) data;
      }
      
    };
    
    struct Chunk {
      ByteFile& file;

      bytes<4> id;
      bytes<4> size;

      Position offset;

      Chunk(ByteFile& file, bytes<4> id = "") : file (file), id (id) {}
      Chunk(Chunk& o) : file (o.file), id (o.id), size (o.size) {}
      virtual ~Chunk() = default;

      void seek_to() {
        file.seek(offset);
      }

      void seek_past() {
        file.seek(offset + 8 + size.as_u());
      }

      void write() {
        offset = file.position();
        file.write_bytes(id);
        file.write_bytes(size);
        write_fields();

        // Update size if changed
        if (std::size_t rs = file.position() - offset - 8; rs > size.as_u()) {
          size.as_u() = rs;
          file.seek(offset + 4);
          file.write_bytes(size);
          seek_past();
        }
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
      char buf;
      for (int i = 0; i < n; i++, iter++) {
        fstream.read(&buf, 1);
        *iter = std::byte(buf);
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
      std::for_each(f, l, [&] (auto& b) {fstream.write((char*)&b, 1);});
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
        fstream.write(&(*iter), 1);
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
