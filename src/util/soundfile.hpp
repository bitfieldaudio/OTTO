#pragma once

#include <algorithm>

#include "util/bytefile.hpp"
#include "util/algorithm.hpp"

namespace top1 {

  class SoundFile : protected ByteFile {
  public:
    using Position = int;
    using Sample = float;
    using Chunk = ByteFile::Chunk;
    constexpr static std::size_t sample_size = 4;

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
      ByteFile::read_bytes(reinterpret_cast<std::byte*>(f),
                           reinterpret_cast<std::byte*>(l));
    } else {
      bytes<sample_size> buf;
      std::for_each(f, l, [&] (Sample& s) {
          ByteFile::read_bytes(buf);
          s = bytes_to_sample(buf);
        });
    }
  }

  template<typename OutIter, typename>
  void SoundFile::read_samples(OutIter&& i, int n) {
    if constexpr (std::is_pointer_v<OutIter>) {
      ByteFile::read_bytes(reinterpret_cast<std::byte*>(i), n);
    } else {
      bytes<sample_size> buf;
      std::generate_n(std::forward<OutIter>(i), n, [&] () {
          ByteFile::read_bytes(buf);
          return bytes_to_sample(buf);
        });
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
