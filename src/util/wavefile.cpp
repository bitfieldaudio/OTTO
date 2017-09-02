#include "util/wavefile.hpp"

namespace top1 {

  using Chunk = ByteFile::Chunk;

  template<std::size_t N>
  using bytes = ByteFile::bytes<N>;

  struct Header : Chunk {
    using Chunk::Chunk;
    Header(Chunk& o) : Chunk(o) {}

    bytes<4> format;
    std::vector<std::unique_ptr<Chunk>> chunks;

    void read_fields() override {
      file.read_bytes(format);
      file.for_chunks_in_range(offset, offset + size.cast<std::uint32_t>(),
        [&](Chunk& c) {
          chunks.emplace_back(new Chunk(c));
        });
    }

    void write_fields() override {
      file.write_bytes(format);
      for (auto&& c : chunks) {
        c->write();
      }
    }
  };

  struct WAVE_fmt : Chunk {
    using Chunk::Chunk;
    WAVE_fmt(Chunk& o) : Chunk(o) {}

    bytes<2> audioFormat = 3;
    bytes<2> numChannels;
    bytes<4> sampleRate;
    bytes<4> byteRate;
    bytes<2> blockAlign;
    bytes<2> bitsPerSample;

    void read_fields() override {
      file.read_bytes(audioFormat);
      file.read_bytes(numChannels);
      file.read_bytes(sampleRate);
      file.read_bytes(byteRate);
      file.read_bytes(blockAlign);
      file.read_bytes(bitsPerSample);
    }

    void write_fields() override {
      file.write_bytes(audioFormat);
      file.write_bytes(numChannels);
      file.write_bytes(sampleRate);
      file.write_bytes(byteRate);
      file.write_bytes(blockAlign);
      file.write_bytes(bitsPerSample);
    }
  };

  struct WAVE_data : Chunk {
    using Chunk::Chunk;
    WAVE_data(Chunk& c) : Chunk(c) {}

    // TODO: I probably dont want the entire file in memory
    std::vector<std::byte> data;

    void read_fields() override {
      file.read_bytes(std::back_inserter(data), size.as_u());
    }

    void write_fields() override {
      file.write_bytes(data.data(), data.size());
      size = data.size();
    }
  };

  struct AIFF_COMM : Chunk {
    
  };

  void SoundFile::open(const Path& p) {
    ByteFile::open(p);
    Header header(*this);
    header.read();

    if (header.id == "RIFF" && header.format == "WAVE") {
      info.type = Info::Type::WAVE;
    } else if (header.id == "FORM" && header.format == "AIFF") {
      info.type = Info::Type::AIFF;
    } else {
      throw Error::UnrecognizedFileType;
    }

    switch (info.type) {
    case Info::Type::WAVE:
      for (auto&& chunk : header.chunks) {
        if (chunk->id == "fmt ") {
          WAVE_fmt* fmt = new WAVE_fmt(*chunk);
          fmt->read();

          if (fmt->audioFormat.as_u() != 3) {
            throw "Unsupported audio format. \
               Currently only float is supported";
          }

          info.channels = fmt->numChannels.as_u();
          info.samplerate = fmt->sampleRate.as_u();

          if (fmt->bitsPerSample.as_u() != 32) {
            throw "Unsupported sample size. \
              Currently only 32bit float is supported";
          }

          chunk = std::unique_ptr<Chunk>(fmt);
        }
      } break;
    case Info::Type::AIFF:
      throw "Unsupported file type. Currently only wav is supported";
    }
  }
}
