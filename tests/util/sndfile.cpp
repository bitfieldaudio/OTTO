#include "../testing.h"

#include "util/sndfile.hpp"
#include "util/dyn-array.hpp"

// TEST_CASE("Persistance of SndFile header information", "[SndFile]") {
//   using Sf = top1::BasicSndFile<float, 2>;
//   Sf sf;

//   REQUIRE_NOTHROW(sf.open("test1.wav"));

//   REQUIRE(sf.position() == 0);

//   sf.samplerate = 32013;

//   REQUIRE_NOTHROW(sf.close());
//   REQUIRE_NOTHROW(sf.open("test1.wav"));

//   REQUIRE(sf.samplerate == 32013);

// }

// TEST_CASE("Persistance of sound data", "[SndFile]") {

//   const std::string path = "test2.wav";

//   using Sf = top1::BasicSndFile<float, 2>;
//   Sf sf;

//   std::vector<Sf::AudioFrame> audio;

//   for (uint i = 0; i < 2048; i++) {
//     Sf::AudioFrame frm;
//     for (uint j = 0; j < Sf::channels; j++) {
//       frm[j] = test::fRand(-1.0, 1.0);
//     }
//     audio.push_back(frm);
//   }

//   REQUIRE_NOTHROW(sf.open(path));

//   sf.write(audio.data(), audio.size());

//   REQUIRE(sf.position() == 2048);
//   REQUIRE(sf.size() == 2048);

//   REQUIRE_NOTHROW(sf.close());

//   sf.open(path);

//   SECTION("Read all of the data") {

//     top1::DynArray<Sf::AudioFrame> rAudio (2048);

//     REQUIRE(sf.position() == 0);
//     REQUIRE(sf.read(rAudio.data(), 2048) == 2048); 

//     REQUIRE(sf.position() == 2048);

//     for (uint i = 0; i < 2048; i++) {
//       for (uint j = 0; j < Sf::channels; j++) {
//         REQUIRE(rAudio[i][j] == audio[i][j]);
//       }
//     }
//   }

//   SECTION("Read half of the data") {
//     sf.seek(1024);

//     REQUIRE(sf.position() == 1024);

//     top1::DynArray<Sf::AudioFrame> rAudio (1024);

//     REQUIRE(sf.read(rAudio.data(), 1024) == 1024);

//     for (uint i = 0; i < 1024; i++) {
//       for (uint j = 0; j < Sf::channels; j++) {
//         REQUIRE(rAudio[i][j] == audio[i + 1024][j]);
//       }
//     }
//   }

//   SECTION("Read data in two turns") {
//     top1::DynArray<Sf::AudioFrame> rAudio (1024);

//     sf.seek(0);

//     REQUIRE(sf.position() == 0);
//     REQUIRE(sf.read(rAudio.data(), 1024) == 1024);
//     REQUIRE(sf.position() == 1024);

//     for (uint i = 0; i < 1024; i++) {
//       for (uint j = 0; j < Sf::channels; j++) {
//         REQUIRE(rAudio[i][j] == audio[i][j]);
//       }
//     }

//     REQUIRE(sf.read(rAudio.data(), 1024) == 1024);
//     REQUIRE(sf.position() == 2048);

//     for (uint i = 0; i < 1024; i++) {
//       for (uint j = 0; j < Sf::channels; j++) {
//         REQUIRE(rAudio[i][j] == audio[i + 1024][j]);
//       }
//     }
//   }


// }
