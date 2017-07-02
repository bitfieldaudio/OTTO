#pragma once
#include "top1file.h"

namespace top1 {

class TapeFile : public File {
public:
  struct HeaderChunk : public Chunk {
    u2b version = 1;
    u2b tracks   = 4;
    u4b samplerate = 44100;
    u2b samplesize = 32;

    HeaderChunk() : Chunk("TOP1") {
      addField(version);
      addField(tracks);
      addField(samplerate);
      addField(samplesize);
    };
  } header;

  struct SliceData {
    u4b  inPos;
    u4b  outPos;
  };

  struct TrackSlicesChunk : public Chunk {
    u4b  trackNum;
    u4b  count = 0;
    std::array<SliceData, 2048> slices;

    TrackSlicesChunk(u4b track) : Chunk("trak"), trackNum (track) {
      addField(trackNum);
      addField(count);
      addField(slices);
    };
  };

  struct SlicesChunk : public Chunk {
    TrackSlicesChunk tracks[4] {{0}, {1}, {2}, {4}};

    SlicesChunk() : Chunk("slic") {
      subChunk(tracks[0]);
      subChunk(tracks[1]);
      subChunk(tracks[2]);
      subChunk(tracks[3]);
    };
  } slices;

  struct RiffHeader : public Chunk {
    ChunkFCC format = "WAVE";

    RiffHeader() : Chunk("RIFF") {
      addField(format);
    }
  } riffHeader;

  // Wav
  struct FmtChunk : public Chunk {
    u2b audioFormat = 1;
    u2b numChannels = 4;
    u4b sampleRate = 44100;
    u2b bitsPerSample = 32;
    u4b byteRate = sampleRate * numChannels * bitsPerSample/8;
    u2b blockAlign = numChannels * bitsPerSample/8;
    FmtChunk() : Chunk("fmt ") {
      addField(audioFormat);
      addField(numChannels);
      addField(sampleRate);
      addField(byteRate);
      addField(blockAlign);
      addField(bitsPerSample);
    };
  } fmt;

  struct AudioChunk : public Chunk {

    AudioChunk() : Chunk("data") {};
  } audioChunk;

  void readSlices();
  void writeSlices();

  void seek(int pos);

  uint write(AudioFrame* data, uint nframes);

  uint read(AudioFrame* data, uint nframes);

  TapeFile() : File() {
    riffHeader.subChunk(header);
    riffHeader.subChunk(slices);
    riffHeader.subChunk(fmt);
    riffHeader.subChunk(audioChunk);
    addChunk(riffHeader);
  }

  TapeFile(std::string path) : TapeFile() {
    open(path);
  }

  TapeFile(TapeFile&) = delete;
  TapeFile(TapeFile&&) = delete;

};

// Custom readers/writers

template<>
inline void File::writeBytes<std::array<TapeFile::SliceData, 2048>>(
  std::array<TapeFile::SliceData, 2048> &data) {
  for (auto &slice : data) {
    writeBytes(slice.inPos);
    writeBytes(slice.outPos);
  }
}
template<>
inline void File::readBytes<std::array<TapeFile::SliceData, 2048>>(
  std::array<TapeFile::SliceData, 2048> &data) {
  for (auto &slice : data) {
    readBytes<u4b>(slice.inPos);
    readBytes<u4b>(slice.outPos);
  }
}
}
