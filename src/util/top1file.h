#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cinttypes>
#include <plog/Log.h>

#include "../utils.h"

class TOP1File {
public:
  typedef char byte;
  typedef uint32_t u4b;
  typedef uint16_t u2b;

  struct ChunkFCC {
    u4b name;

    ChunkFCC() {};
    ChunkFCC(const char *str) {
      name = *((u4b *)str);
    }

    bool operator==(ChunkFCC other) {
      return name == other.name;
    }
    bool operator!=(ChunkFCC other) {
      return name != other.name;
    }

    std::string str() {
      return std::string((char *) &name, 4);
    }
  };

  struct Chunk {
    ChunkFCC id;
    u4b  size = 0;

    int offset = -1;

    Chunk() {};
    Chunk(ChunkFCC id, u4b size) : id (id), size (size) {};
  };

  struct HeaderChunk : public Chunk {
    u2b  version = 1;
    u2b  tracks   = 4;
    u4b  samplerate = 44100;
    u2b  samplesize = 32;

    const static ChunkFCC fcc;

    HeaderChunk() : Chunk(fcc, 10){};
    HeaderChunk(Chunk chunk) : Chunk(chunk) {}
  } header;

  struct SliceChunk {
    u4b  inPos;
    u4b  outPos;
  };

  struct TrackSlicesChunk : public Chunk {
    u4b  trackNum;
    u4b  count = 0;
    SliceChunk slices[2048];

    const static ChunkFCC fcc;
    const static uint chunkSize = 4 + 4 + sizeof(SliceChunk) * 2048;

    TrackSlicesChunk(u4b track) : trackNum(track), Chunk(fcc, chunkSize) {};
    TrackSlicesChunk() : Chunk(fcc, chunkSize) {};
    TrackSlicesChunk(Chunk chunk) : Chunk(chunk) {}
  };

  struct SlicesChunk : public Chunk {
    TrackSlicesChunk tracks[4] {{0}, {1}, {2}, {4}};

    const static ChunkFCC fcc;

    SlicesChunk() : Chunk(fcc, 4 * 8 + 4 * TrackSlicesChunk::chunkSize) {};
    SlicesChunk(Chunk chunk) : Chunk(chunk) {}
  } slices;

  struct AudioChunk : public Chunk {
    const static ChunkFCC fcc;

    AudioChunk() : Chunk(fcc, 0) {};
    AudioChunk(Chunk chunk) : Chunk(chunk) {}
  } audioChunk;

private:
  std::fstream fileStream;

  void readBytes(byte *bytes, int length);
  void readBytes(ChunkFCC &bytes);
  void readBytes(u4b &bytes);
  void readBytes(u2b &bytes);

  void writeBytes(byte *bytes, int length);
  void writeBytes(ChunkFCC &bytes);
  void writeBytes(u4b &bytes);
  void writeBytes(u2b &bytes);

  void fseek(uint pos);

  bool skipChunkR(Chunk chunk);
  bool skipChunkW(Chunk chunk);

  template<class CT>
  CT readChunk();

  template<class CT>
  CT readChunk(Chunk chunk);

  template<class CT>
  void writeChunk(CT &chunk);

public:
  struct Error {
    enum {
      NONE,
      ERROR
    } status;

    std::string message;

    operator bool() {
      return status != NONE;
    }

    bool log() {
      LOGE_IF(*this) << message;
      return bool(*this);
    }
  } error;

  TOP1File(std::string path) {
    open(path);
  }

  void open(std::string path);
  void close();
  void flush();

  void writeFile();

  void readSlices();
  void writeSlices();

  void seek(int pos);

  uint write(AudioFrame* data, uint nframes);

  uint read(AudioFrame* data, uint nframes);

};
