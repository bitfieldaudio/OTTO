#pragma once

#include <algorithm>

#include "util/bytefile.hpp"
#include "util/algorithm.hpp"

namespace top1 {

  class SoundFile : public ByteFile {
    public:
    using Position = int;
    using Sample = float;
    using Chunk = ByteFile::Chunk;
    constexpr static std::size_t sample_size = sizeof(Sample);

    enum class Error {
      UnrecognizedFileType,
    };

    struct Info {
      enum class Type {
        WAVE,
        AIFF,
      } type;

      int channels = 1;
      int samplerate = 44100;
    } info;

    SoundFile();
    virtual ~SoundFile() = default;

    using ByteFile::open;
    using ByteFile::close;
    using ByteFile::flush;
    using ByteFile::is_open;

    void write_file() override;
    void read_file() override;

    Position seek(Position);
    Position position();
    Position length();

    template<typename OutIter,
      typename = std::enable_if<
        is_iterator_v<OutIter, Sample, std::output_iterator_tag>>>
      void read_samples(OutIter, OutIter);

    template<typename OutIter,
      typename = std::enable_if<
        is_iterator_v<OutIter, Sample, std::output_iterator_tag>>>
      void read_samples(OutIter&&, int);

    template<typename InIter,
      typename = std::enable_if<
        is_iterator_v<InIter, Sample, std::input_iterator_tag>>>
      void write_samples(InIter, InIter);

    template<typename InIter,
      typename = std::enable_if<
        is_iterator_v<InIter, Sample, std::input_iterator_tag>>>
      void write_samples(InIter&&, int);

    protected:

    /// When extending <SoundFile>, override this function.
    ///
    /// It should push back any custom metadata chunks to `v`
    virtual void add_custom_chunks(std::vector<std::unique_ptr<Chunk>>& v) {}

    /// When extending <SoundFile>, override this function.
    ///
    /// It should check the id of `ptr`, and if it matches,
    /// swap it with an instance of the correct class.
    /// If the chunk is unknown, leave it alone. After this,
    /// <Chunk::read> will be invoked on `ptr`.
    virtual void replace_custom_chunk(std::unique_ptr<Chunk>& ptr) {}

    friend struct Header;
    friend struct WAVE_fmt;
    friend struct WAVE_data;

    ByteFile::Position audioOffset;

    Sample bytes_to_sample(bytes<sample_size> bytes) {
      return bytes.cast<Sample>();
    }

    bytes<sample_size> sample_to_bytes(Sample sample) {
      bytes<sample_size> bytes;
      bytes.cast<Sample>() = sample;
      return bytes;
    }

  };

  /*
   * Template Specializations
   */

  template<typename OutIter, typename>
    void SoundFile::read_samples(OutIter f, OutIter l) {
    if constexpr (std::is_pointer_v<OutIter>) {
        auto r = ByteFile::read_bytes(reinterpret_cast<std::byte*>(f),
          reinterpret_cast<std::byte*>(l));
        r.if_err([&] (auto&& e) {
            std::generate(e, l, [] { return 0; });
          });
      } else {
      bytes<sample_size> buf;
      uint i = 0;
      for (auto iter = f; iter != l; iter++, i++) {
        if (ByteFile::read_bytes(buf).is_err()) {
          std::generate(iter, l, [] { return 0; });
          break;
        }
        *iter = bytes_to_sample(buf);
      }
    }
  }

  template<typename OutIter, typename>
    void SoundFile::read_samples(OutIter&& iter, int n) {
    if constexpr (std::is_pointer_v<OutIter>) {
        ByteFile::read_bytes(reinterpret_cast<std::byte*>(iter),
          n * sample_size).if_err(
            [&] (auto&& e) {
              std::generate_n(iter + e, n - e, [] { return 0; });
            });
      } else {
      bytes<sample_size> buf;
      uint i = 0;
      for (auto cur = iter; i < n; iter++, i++) {
        auto r = ByteFile::read_bytes(buf);
        if (r.is_err()) {
          std::generate_n(cur, n - r.unwrap_err(), [] { return 0; });
          break;
        }
        *cur = bytes_to_sample(buf);
      }
    }
  }

  template<typename InIter, typename>
  void SoundFile::write_samples(InIter f, InIter l) {
    if constexpr (std::is_pointer_v<InIter>) {
      ByteFile::write_bytes(reinterpret_cast<std::byte*>(f),
                            reinterpret_cast<std::byte*>(l));
    } else {
      std::for_each(f, l, [&] (Sample s) {
          ByteFile::write_bytes(sample_to_bytes(s));
        });
    }
  }

  template<typename InIter, typename>
  void SoundFile::write_samples(InIter&& i, int n) {
    if constexpr (std::is_pointer_v<InIter>) {
      ByteFile::write_bytes(reinterpret_cast<std::byte*>(i), n);
    } else {
      for_each_n(std::forward<InIter>(i), n, [&] (Sample s) {
          ByteFile::write_bytes(sample_to_bytes(s));
        });
    }
  }
}
