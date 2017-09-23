#include "util/soundfile.hpp"

namespace top1 {

  class TapeFile : public SoundFile {
  public:
    using SoundFile::Info;

    struct SliceData {
      uint32_t in = 0;
      uint32_t out = 0;
    };

    struct SliceArray {
      std::array<SliceData, 2048> array;
      uint16_t count = 0;
    };

    std::array<SliceArray, 4> slices;

    TapeFile()
    {
      info.channels = 4;
    }

    virtual ~TapeFile() = default;

  protected:

    void add_custom_chunks(std::vector<std::unique_ptr<Chunk>>& v) override;
    void replace_custom_chunk(std::unique_ptr<Chunk>& ptr) override;

  };

}
