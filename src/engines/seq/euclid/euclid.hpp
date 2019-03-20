#pragma once

#include "core/engine/engine.hpp"

#include <array>
#include <optional>

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct Euclid : ArpeggiatorEngine<Euclid> {
    static constexpr util::string_ref name = "Euclid";
    static constexpr int max_length = 16;

    struct Channel {
      Property<int> length = {max_length, limits(0, max_length), step_size(1)};
      Property<int> hits = {0, limits(0, max_length), step_size(1)};
      Property<int> rotation = {0, limits(0, max_length), step_size(1)};

      Property<std::array<int, 6>> notes = {std::array<int, 6>{{-1, -1, -1, -1, -1, -1}}};

      void update_notes();

      int _beat_counter = 0;
      std::array<bool, max_length> _hits_enabled;

      DECL_REFLECTION(Channel, length, hits, rotation, notes);
    };

    struct Props {
      Property<int, wrap> channel = {0, limits(0, 3)};
      std::array<Channel, 4> channels;
      DECL_REFLECTION(Props, channel, channels);
    } props;

    Euclid();

    void on_enable() override;

    audio::ProcessData<0> process(audio::ProcessData<0>) override;

    Channel& current_channel()
    {
      return props.channels.at(props.channel);
    }

    std::optional<std::array<int, 6>> recording = std::nullopt;

    bool running = false;

  private:
    friend struct EuclidScreen;

    int _samples_per_beat = 22050 / 4;
    int _counter = _samples_per_beat;
    // Used to make sure NoteOff events are sent when stopped
    bool _should_run = false;

    // Used in recording to clear the current value when the first keyonevent is sent
    bool _has_pressed_keys = false;
  };
} // namespace otto::engines
