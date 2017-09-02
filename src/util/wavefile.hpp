#pragma once

#include "util/bytefile.hpp"

namespace top1 {

  class SoundFile : ByteFile {
  public:
    using Position = int;
    using Sample = float;

    enum class Error {
      UnrecognizedFileType,
    };

    struct Info {
      enum class Type {
        AIFF,
        WAVE,
      } type;

      int channels;
      int samplerate;
    } info;

    Path path;

    SoundFile();

    void open(const Path&);
    void close();
    void flush();

    Position seek();
    Position position();
    Position length();

    template<typename OutIter,
      typename = std::enable_if<
        is_iterator_v<OutIter, Sample, std::output_iterator_tag>>>
    void read_samples(OutIter, OutIter);

    template<typename OutIter,
      typename = std::enable_if<
        is_iterator_v<OutIter, Sample, std::output_iterator_tag>>>
    void read_samples(OutIter, int);

    template<typename InIter,
      typename = std::enable_if<
        is_iterator_v<InIter, Sample, std::input_iterator_tag>>>
    void write_samples(InIter, InIter);

    template<typename InIter,
      typename = std::enable_if<
        is_iterator_v<InIter, Sample, std::input_iterator_tag>>>
    void write_samples(InIter, int);
  };

  /*
   * Template Specializations
   */

  template<typename OutIter, typename>
  void SoundFile::read_samples(OutIter, OutIter) {
    // TODO
  }

  template<typename OutIter, typename>
  void SoundFile::read_samples(OutIter, int) {
    // TODO
  }

  template<typename InIter, typename>
  void SoundFile::write_samples(InIter, InIter) {
    // TODO
  }

  template<typename InIter, typename>
  void SoundFile::write_samples(InIter, int) {
    // TODO
  }
  
}
