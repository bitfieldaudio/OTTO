#pragma once

#include "core/engine/engine.hpp"

#include "core/audio/faust.hpp"
#include "core/audio/voice_manager.hpp"

#include <array>
#include <optional>

#if false

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct Accord : SequencerEngine {
    static constexpr int loop_max_length = 64; //Maximum 8 bars of eighth notes
    static constexpr int hit_max_length = 16; //Maximum length of a hit is 2 bars

    struct Beat : Properties<> {
      Property<int> length = {this, "Length", 1, has_limits::init(0, hit_max_length), steppable::init(1)};
      Property<std::array<int, 6>> notes;

      Beat(int len = 1, std::initializer_list<int> nts = {}) 
        :  notes {this, "Notes", nts}
      {
        length = len;
      }
    };

    struct Notestack
    {
      Notestack() {}
    };

    struct Props : Properties<> {
      //Vector of the chords/hits
      Property<int> loop_length = {this, "Loop_length", 32, has_limits::init(8, loop_max_length), steppable::init(1)};
      Property<int, wrap> cur_step = {this, "Current_step", 0, has_limits::init(0, loop_length)};
      std::vector<std::optional<Beat>> beats;


      Props() {

      }

    } props;

    Accord();

    void on_enable() override;

    audio::ProcessData<0> process(audio::ProcessData<0>) override;

    std::optional<std::array<int, 6>> recording = std::nullopt;

    bool running = false;

  private:
    friend struct AccordScreen;

    int _samples_per_beat = 42050 / 4;
    int _counter = _samples_per_beat;
    bool _should_run = false;

    // Used in recording to clear the current value when the first keyonevent is sent
    bool _has_pressed_keys = false;
  };
} // namespace otto::engines

#endif
