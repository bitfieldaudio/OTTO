#include "../testing.t.hpp"

#include "util/soundfile.hpp"

namespace top1 {

  SoundFile file;
  ByteFile::Path somePath = "testdata/test1.wav";
  using Sample = SoundFile::Sample;

  TEST_CASE("Persistance of SndFile header information", "[SoundFile] [util]") {
    test::truncateFile(somePath);
    REQUIRE_NOTHROW(file.open(somePath));

    REQUIRE(file.position() == 0);

    file.info.samplerate = 32013;

    REQUIRE_NOTHROW(file.close());
    REQUIRE_NOTHROW(file.open(somePath));

    REQUIRE(file.info.samplerate == 32013);

  }

  TEST_CASE("Persistance of sound data", "[SoundFile] [util]") {
    test::truncateFile(somePath);

    REQUIRE_NOTHROW(file.open(somePath));

    std::vector<Sample> audio;

    for (uint i = 0; i < 2048; i++) {
      Sample s;
      s = test::fRand(-1.0, 1.0);
      audio.push_back(s);
    }

    REQUIRE_NOTHROW(file.write_samples(audio.begin(), audio.end()));

    REQUIRE(file.position() == 2048);
    REQUIRE(file.length() == 2048);

    REQUIRE_NOTHROW(file.close());

    file.open(somePath);

    SECTION("Read all of the data") {

      std::vector<Sample> rAudio;
      rAudio.reserve(2048);

      REQUIRE(file.position() == 0);
      REQUIRE_NOTHROW(file.read_samples(std::back_inserter(rAudio), 2048)); 

      REQUIRE(file.position() == 2048);

      REQUIRE(std::equal(audio.begin(), audio.end(), rAudio.begin()));
    }

    SECTION("Read half of the data") {
      file.seek(1024);

      REQUIRE(file.position() == 1024);

      std::vector<Sample> rAudio;
      rAudio.reserve(1024);

      REQUIRE_NOTHROW(file.read_samples(std::back_inserter(rAudio), 1024)); 

      REQUIRE(file.position() == 2048);

      REQUIRE(std::equal(audio.begin() + 1024, audio.end(), rAudio.begin()));
    }

    SECTION("Read data in two turns") {
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
