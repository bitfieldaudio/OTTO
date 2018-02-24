#pragma once

#include <array>
#include <stack>
#include <queue>
#include <gsl/gsl_util>

#include "util/utility.hpp"
#include "util/algorithm.hpp"

#include "core/audio/faust.hpp"
#include "core/audio/processor.hpp"

#include "core/props/props.hpp"

namespace otto::core::audio {

    using Voice = int;

    /// A pair of a note and a voice. Kept in the `notes_` stack
    struct NoteVoicePair {
      char note;
      Voice voice;

      bool has_voice() const noexcept
      {
        return voice >= 0;
      }

    };

  template<int N>
  struct VoiceManager {
    struct VoiceProps : props::Properties<props::no_serialize> {
      struct Midi : props::Properties<props::no_serialize> {
        props::Property<float> freq     = {this, "freq", 440};
        props::Property<float> velocity = {this, "velocity", 1.0,
                                           props::has_limits::init(0.f, 1.f)};
        props::Property<bool> trigger   = {this, "trigger", false};

        using Properties::Properties;
      } midi = {this, "midi"};

      using Properties::Properties;
    };

    props::Properties<props::no_serialize> voices_props;

    std::array<VoiceProps, N> voices = util::generate_array<N>(
      [this](auto n) { return VoiceProps(&voices_props, std::to_string(n)); });

    VoiceManager(props::properties_base& parent)
      : voices_props(&parent, "voices")
    {
      for (int i = 0; i < N; ++i){
        free_voices.push_back(i);
      }
    }

    void process_before(audio::ProcessData<0> data);
    void process_after(audio::ProcessData<0> data);

    // Voice managagement //
  private:

    auto get_voice() -> Voice;
    void stop_voice(char key);

    std::deque<Voice> free_voices;
    std::vector<NoteVoicePair> note_stack;

  };

  inline std::ostream& operator<<(std::ostream& o, NoteVoicePair nvp)
  {
    return o << "{n: " << (int) nvp.note << ", v: " << nvp.voice << "}";
  }

  template<typename T>
  std::ostream& operator<<(std::ostream& o, std::vector<T> const& v)
  {
    o << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
      o << v[i];
      if (i != (v.size() - 1)) o << ", ";
    }
    return o << "]";
  }

  template<typename T>
  std::ostream& operator<<(std::ostream& o, std::deque<T> const& v)
  {
    o << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
      o << v[i];
      if (i != (v.size() - 1)) o << ", ";
    }
    return o << "]";
  }

  template<int N>
  auto VoiceManager<N>::get_voice() -> Voice
  {
    if (free_voices.size() > 0) {
      auto v = free_voices.front();
      free_voices.pop_front();
      return v;
    } else {
      auto found =
        util::find_if(note_stack, [](auto& nvp) { return nvp.has_voice(); });
      if (found != note_stack.end()) {
        Voice v = found->voice;
        found->voice = Voice{-1};
        voices[v].midi.trigger = false;
        return v;
      } else {
        LOGE("No voice found. Using voice 0");
        return Voice{0};
      }
    }
  }

  template<int N>
  void VoiceManager<N>::stop_voice(char key)
  {
    auto free_voice = [this](Voice v) {
      auto found = std::find_if(note_stack.rbegin(), note_stack.rend(),
                                [](auto nvp) { return !nvp.has_voice(); });
      if (found != note_stack.rend()) {
        found->voice = v;
        auto& vp = voices[v];
        vp.midi.trigger = true;
        vp.midi.freq    = midi::note_freq(found->note);
      } else {
        auto& vp = voices[v];
        free_voices.push_back(v);
        vp.midi.trigger = false;
        // CHECK_F(nvp.note == key, "WHAT? %d", nvp.note);
        // LOGI("OFF: K{} V{}; NS: {}", int(key), nvp.voice, note_stack);
      }
    };
    auto it = util::remove_if(note_stack, [key, &free_voice](auto nvp) {
      if (nvp.note == key) {
        if (nvp.has_voice()) free_voice(nvp.voice);
        return true;
      }
      return false;
    });
    note_stack.erase(it, note_stack.end());
  }

  template<int N>
  void VoiceManager<N>::process_before(audio::ProcessData<0> data)
  {
    for (auto&& ev : data.midi) {
      util::match(ev,
                  [this](midi::NoteOnEvent& ev) {
                    stop_voice(gsl::narrow_cast<char>(ev.key));
                    Voice v = get_voice();
                    note_stack.push_back({gsl::narrow_cast<char>(ev.key), v});
                    auto& vp         = voices[v];
                    vp.midi.freq     = midi::note_freq(ev.key);
                    vp.midi.velocity = ev.velocity / 127.f;
                    vp.midi.trigger     = 1;
                    LOGI(" ON: K{} V{}; NS: {}", ev.key, v, note_stack);
                  },
                  [](auto&&) {});
    }
  }

  template<int N>
  void VoiceManager<N>::process_after(audio::ProcessData<0> data)
  {
    for (auto&& ev : data.midi) {
      util::match(ev,
                  [this](midi::NoteOffEvent& ev) {
                    stop_voice(gsl::narrow_cast<char>(ev.key));
                  },
                  [](auto&&) {});
    }
  }

} // namespace otto::core::audio
