#pragma once
#include "sndfile.h"

namespace top1 {

class TapeFile : public SndFile<4> {
public:
  struct TOP1Chunk : public Chunk {
    ChunkFCC type = "TAPE";
    u4b version = 1;

    TOP1Chunk() : Chunk("TOP1") {
      addField(version);
    };
  };

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
  };

  TOP1Chunk top1Chunk;
  SlicesChunk slices;

  void readSlices();
  void writeSlices();

  TapeFile() : SndFile<4>() {};
  TapeFile(std::string path) : SndFile<4>(path) {};

  TapeFile(TapeFile&) = delete;
  TapeFile(TapeFile&&) = delete;

protected:

  void setupChunks() override {
    top1Chunk.subChunk(slices);
    wavHeader.subChunk(top1Chunk);
  }

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
