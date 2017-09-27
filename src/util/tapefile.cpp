#include "tapefile.hpp"

namespace top1 {

  using Chunk = ByteFile::Chunk;
  using SliceData = TapeFile::SliceData;

  struct TRCKChunk : Chunk {
    uint16_t index = 0;
    TRCKChunk(uint16_t idx) : Chunk("TRCK"), index (idx) {}
    TRCKChunk(const Chunk& c) : Chunk(c) {}

    void write_fields(ByteFile& f) override {
      auto& tf = dynamic_cast<TapeFile&>(f);
      f.write_bytes(bytes<2>::from_u(index));
      f.write_bytes(bytes<2>::from_u(tf.slices[index].count));
      f.write_bytes((std::byte*) tf.slices[index].array.data(),
        2048 * sizeof(SliceData));
    }

    void read_fields(ByteFile& f) override {
      auto& tf = dynamic_cast<TapeFile&>(f);
      bytes<2> temp;
      f.read_bytes(temp).unwrap_ok();
      index = temp.as_u();
      f.read_bytes(temp).unwrap_ok();
      tf.slices[index].count = temp.as_u();
      f.read_bytes((std::byte*) tf.slices[index].array.data(),
        2048 * sizeof(SliceData)).unwrap_ok();
    }
  };

  struct TAPEChunk : Chunk {
    TAPEChunk(const Chunk& c) : Chunk(c) {}
    TAPEChunk() : Chunk("TAPE") {}
    bytes<4> version = {1,0,0,0};

    TRCKChunk tracks[4] = {{0}, {1}, {2}, {3}};

    void write_fields(ByteFile& f) override {
      f.write_bytes(version);
      for (auto&& trck : tracks) {
        trck.write(f);
      }
    }

    void read_fields(ByteFile& f) override {
      f.read_bytes(version).unwrap_ok();
      for (auto&& trck : tracks) {
        trck.read(f);
      }
    }
  };

  void TapeFile::add_custom_chunks(std::vector<std::unique_ptr<Chunk>>& v) {
    v.push_back(std::make_unique<TAPEChunk>());
  }
  void TapeFile::replace_custom_chunk(std::unique_ptr<Chunk>& ptr) {
    if (ptr->id == "TAPE") ptr = std::make_unique<TAPEChunk>(*ptr);
  }
}
