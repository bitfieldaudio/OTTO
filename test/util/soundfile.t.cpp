#include "../testing.t.hpp"

#include "util/soundfile.hpp"

namespace top1 {

  fs::path somePath = test::dir / "test1.wav";
  using Sample = SoundFile::Sample;

  TEST_CASE("Persistance of SndFile header information", "[SoundFile] [util]") {
    SoundFile file;
    REQUIRE_NOTHROW(file.open(somePath));

    REQUIRE(file.position() == 0);

    file.info.samplerate = 32013;

    REQUIRE_NOTHROW(file.close());
    REQUIRE_NOTHROW(file.open(somePath));

    REQUIRE(file.info.samplerate == 32013);
  }

  TEST_CASE("Persistance of sound data", "[SoundFile] [util]") {
    SoundFile file;
    REQUIRE_NOTHROW(file.open(somePath));

    std::vector<Sample> audio;

    std::generate_n(std::back_inserter(audio), 2048,
      []{return Random::get<float>(-1.0, 1.0);});

    REQUIRE_NOTHROW(file.write_samples(audio.begin(), audio.end()));

    REQUIRE(file.position() == 2048);
    REQUIRE(file.length() == 2048);

    REQUIRE_NOTHROW(file.close());

    SECTION("Read all of the data") {
      SoundFile file;
      file.open(somePath);

      std::vector<Sample> rAudio;
      rAudio.reserve(2048);

      REQUIRE(file.position() == 0);
      REQUIRE_NOTHROW(file.read_samples(std::back_inserter(rAudio), 2048)); 

      REQUIRE(file.position() == 2048);

      REQUIRE(std::equal(audio.begin(), audio.end(), rAudio.begin()));
    }

    SECTION("Read half of the data") {
      SoundFile file;
      file.open(somePath);
      file.seek(1024);

      REQUIRE(file.position() == 1024);

      std::vector<Sample> rAudio;
      rAudio.reserve(1024);

      REQUIRE_NOTHROW(file.read_samples(std::back_inserter(rAudio), 1024)); 

      REQUIRE(file.position() == 2048);

      REQUIRE(std::equal(audio.begin() + 1024, audio.end(), rAudio.begin()));
    }

    SECTION("Read data in two turns") {
      SoundFile file;
      file.open(somePath);
      std::vector<Sample> rAudio;
      rAudio.reserve(1024);

      file.seek(0);

      REQUIRE(file.position() == 0);
      REQUIRE_NOTHROW(file.read_samples(std::back_inserter(rAudio), 1024)); 
      REQUIRE(file.position() == 1024);

      REQUIRE(std::equal(audio.begin(), audio.begin() + 1024, rAudio.begin()));

      REQUIRE_NOTHROW(file.read_samples(std::back_inserter(rAudio), 1024)); 
      REQUIRE(file.position() == 2048);

      REQUIRE(std::equal(audio.begin(), audio.end(), rAudio.begin()));
    }

  }
}
