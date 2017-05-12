#include <exception>
#include <fmt/format.h>
#include "top1file.h"

struct ReadException : public std::exception {
  std::string message = "No error message";

  const char * what () const throw () {
    return message.c_str();
   }

  ReadException() {};
  ReadException(std::string message) : message (message) {};
};

void TOP1File::readBytes(byte *bytes, int length) {
  fileStream.read(bytes, length);
  if (fileStream.eof()) throw ReadException("EOF");
}
void TOP1File::readBytes(ChunkFCC &bytes) {
  fileStream.read((char*) &bytes, sizeof(bytes));
  if (fileStream.eof()) throw ReadException("EOF");
}
void TOP1File::readBytes(u4b &bytes) {
  fileStream.read((char*) &bytes, sizeof(bytes));
  if (fileStream.eof()) throw ReadException("EOF");
}
void TOP1File::readBytes(u2b &bytes) {
  fileStream.read((char*) &bytes, sizeof(bytes));
  if (fileStream.eof()) throw ReadException("EOF");
}

void TOP1File::writeBytes(byte *bytes, int length) {
  // LOGD << *bytes;
  fileStream.write(bytes, length);
}
void TOP1File::writeBytes(ChunkFCC &bytes) {
  // LOGD << bytes.str();
  fileStream.write((char*) &bytes, sizeof(bytes));
}
void TOP1File::writeBytes(u4b &bytes) {
  // LOGD << bytes;
  fileStream.write((char*) &bytes, sizeof(bytes));
}
void TOP1File::writeBytes(u2b &bytes) {
  // LOGD << bytes;
  fileStream.write((char*) &bytes, sizeof(bytes));
}

void TOP1File::fseek(uint pos) {
  fileStream.seekg(pos);
  fileStream.peek();
  if (fileStream.eof() || fileStream.fail()) {
    // LOGD << "EOF";
    fileStream.seekp(0, fileStream.end);
    fileStream.write(0, pos - fileStream.tellp());
    fileStream.clear();
    fileStream.seekg(pos);
  }
  if (fileStream.tellp() != pos) {
    LOGE << fmt::format("Couldnt seek past {:#x}", fileStream.tellp());
  }
}

bool TOP1File::skipChunkR(TOP1File::Chunk chunk) {
uint newPos = chunk.offset + 4 + 4 + chunk.size;
if (fileStream.tellg() != newPos) {
  // LOGD << fmt::format("From {:#x} to {:#x}", fileStream.tellg(), newPos);
  fseek(newPos);
  if (fileStream.eof()) throw ReadException("EOF");
  return true;
}
return false;
}

bool TOP1File::skipChunkW(TOP1File::Chunk chunk) {
  uint newPos = chunk.offset + 4 + 4 + chunk.size;
  if (fileStream.tellp() != newPos) {
    // LOGD << fmt::format("Skipping chunk {} at {:#x}", chunk.id.str(), chunk.offset);
    // LOGD << fmt::format("From {:#x} to {:#x}", fileStream.tellp(), newPos);
    fseek(newPos);
    if (fileStream.eof()) throw ReadException("EOF");
    return true;
  }
  return false;
}

template<>
TOP1File::Chunk TOP1File::readChunk<TOP1File::Chunk>() {
  Chunk chunk;
  chunk.offset = fileStream.tellg();
  readBytes(chunk.id);
  readBytes(chunk.size);
  return chunk;
}

template<>
TOP1File::HeaderChunk TOP1File::readChunk<TOP1File::HeaderChunk>(Chunk chunk) {
if (chunk.id == header.id) {
  HeaderChunk hc = chunk;
  readBytes(hc.version);
  readBytes(hc.tracks);
  readBytes(hc.samplerate);
  readBytes(hc.samplesize);
  if (skipChunkR(hc)) {
    LOGW << "Unexpected header size";
  }
  return hc;
} else {
  throw ReadException();
}
}

template<>
TOP1File::TrackSlicesChunk TOP1File::readChunk<TOP1File::TrackSlicesChunk>(Chunk chunk) {
TrackSlicesChunk stc;
if (chunk.id == stc.id) {
  stc = chunk;
  readBytes(stc.trackNum);
  readBytes(stc.count);
  readBytes((byte*) stc.slices, 2048 * sizeof(SliceChunk));
  if (skipChunkR(stc)) {
    LOGW << "Unexpected chunk size";
  }
  return stc;
} else {
  throw ReadException();
}
}

template<>
TOP1File::SlicesChunk TOP1File::readChunk<TOP1File::SlicesChunk>(Chunk chunk) {
if (chunk.id == slices.id) {
  SlicesChunk sc = chunk;
  for (int i = 0; i < 4; i++) {
    sc.tracks[i] = readChunk<TrackSlicesChunk>();
  }
  if (skipChunkR(sc)) {
    LOGW << "Unexpected chunk size";
  }
  return sc;
} else {
  throw ReadException();
}
}

template<>
TOP1File::AudioChunk TOP1File::readChunk<TOP1File::AudioChunk>(Chunk chunk) {
  // LOGD << fmt::format("Reading AudioChunk at {:#x}", chunk.offset);
  return AudioChunk(chunk);
}

// writeChunk
template<>
void TOP1File::writeChunk<TOP1File::Chunk>(Chunk &chunk) {
  if (chunk.offset < 0) {
    chunk.offset = fileStream.tellp();
    // LOGD << "Calculated offset";
  }
  // LOGD << fmt::format("Writing chunk of type {} at {:#x}", chunk.id.str(), chunk.offset);
  fseek(chunk.offset);
  writeBytes(chunk.id);
  writeBytes(chunk.size);
}

template<>
void TOP1File::writeChunk<TOP1File::HeaderChunk>(TOP1File::HeaderChunk &chunk) {
  // LOGD << "Writing header";
  writeChunk<Chunk>(chunk);

  writeBytes(chunk.version);
  writeBytes(chunk.tracks);
  writeBytes(chunk.samplerate);
  writeBytes(chunk.samplesize);

  if (skipChunkW(chunk)) {
    LOGW << "Unexpected header size";
  }
}

template<>
void TOP1File::writeChunk<TOP1File::TrackSlicesChunk>(TOP1File::TrackSlicesChunk &chunk) {
  writeChunk<Chunk>(chunk);

  writeBytes(chunk.trackNum);
  writeBytes(chunk.count);
  writeBytes((byte*)chunk.slices, 2048 * sizeof(SliceChunk));

  if (skipChunkW(chunk)) {
    LOGW << "Unexpected chunk size";
  }

  // LOGD << "Wrote TrackSlicesChunk\n";
}

template<>
  void TOP1File::writeChunk<TOP1File::SlicesChunk>(TOP1File::SlicesChunk &chunk) {
  writeChunk<Chunk>(chunk);
  for (int i = 0; i < 4; i++) {
    writeChunk<TrackSlicesChunk>(chunk.tracks[i]);
  }

  if (skipChunkW(chunk)) {
    LOGW << "Unexpected chunk size";
  }
}

template<>
void TOP1File::writeChunk<TOP1File::AudioChunk>(TOP1File::AudioChunk &chunk) {
  writeChunk<Chunk>(chunk);
}

template<class CT> CT TOP1File::readChunk() {
  return readChunk<CT>(readChunk<Chunk>());
}
/****************************************/
/* TOP1File Implementation              */
/****************************************/

void TOP1File::open(std::string path) {
  fileStream.open(path, std::ios::in | std::ios::out | std::ios::binary);
  if (!fileStream) {
    LOGI << "Empty file, creating";
    fileStream.open(path, std::ios::trunc | std::ios::out | std::ios::binary);
    fileStream.close();
    fileStream.open(path, std::ios::in | std::ios::out | std::ios::binary);
    createFile();
  }
  try {
    header = readChunk<HeaderChunk>();
  } catch(ReadException e) {
    error = {Error::ERROR, "Invalid file. Header not found"};
    LOGE << e.message;
  }
  // LOGD << "Reading chunk";
  Chunk chunk = readChunk<Chunk>();
  while (true) {
    try {
      if (chunk.id == SlicesChunk::fcc) {
        this->slices = readChunk<SlicesChunk>(chunk);
      }
      if (chunk.id == AudioChunk::fcc) {
        this->audioChunk = readChunk<AudioChunk>(chunk);
        break;
      }
      chunk = readChunk<Chunk>();
    } catch(ReadException e) {
      error = {Error::ERROR, e.message};
      error.log();
    }
  }
}

void TOP1File::close() {
  fileStream.close();
}

void TOP1File::flush() {
  fileStream.flush();
}

void TOP1File::createFile() {
  writeChunk<HeaderChunk>(header);
  writeChunk<SlicesChunk>(slices);
  writeChunk<AudioChunk>(audioChunk);
}

void TOP1File::readSlices() {
  try {
    readChunk<SlicesChunk>(slices);
  } catch (ReadException e) {
    error = {Error::ERROR, e.message};
    error.log();
  }
}

void TOP1File::writeSlices() {
  writeChunk<SlicesChunk>(slices);
}

void TOP1File::seek(int pos) {
  if (pos < 0) return;
  int offsetPos = audioChunk.offset + 8 + pos * sizeof(float) * header.tracks;
  // LOGD << fmt::format("Audio pos: {}, File pos: {:#x}", pos, offsetPos);
  fseek(offsetPos);
}

uint TOP1File::write(AudioFrame *data, uint nframes) {
  //LOGD << fmt::format("Writing {} frames at {:#x}", nframes, fileStream.tellp());
  fileStream.write((byte*) data, nframes * sizeof(float) * header.tracks);
  return nframes;
}

uint TOP1File::read(AudioFrame *data, uint nframes) {
  fileStream.read((byte*) data, nframes * sizeof(float) * header.tracks);
  return nframes;
};

const TOP1File::ChunkFCC TOP1File::HeaderChunk::fcc = ChunkFCC("TOP1");
const TOP1File::ChunkFCC TOP1File::SlicesChunk::fcc = ChunkFCC("slic");
const TOP1File::ChunkFCC TOP1File::TrackSlicesChunk::fcc = ChunkFCC("trak");
const TOP1File::ChunkFCC TOP1File::AudioChunk::fcc = ChunkFCC("data");
