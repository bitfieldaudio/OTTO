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
#include "core/ui/screen.hpp"

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

  struct EnvelopeProps : props::Properties<> {
    props::Property<float> attack = {this, "Attack", 0,
                                     props::has_limits::init(0, 6),
                                     props::steppable::init(0.02)};

    props::Property<float> decay = {this, "Decay", 0,
                                    props::has_limits::init(0, 4),
                                    props::steppable::init(0.02)};

    props::Property<float> sustain = {this, "Sustain", 1,
                                      props::has_limits::init(0, 1),
                                      props::steppable::init(0.02)};

    props::Property<float> release = {this, "Release", 0.2,
                                      props::has_limits::init(0, 4),
                                      props::steppable::init(0.02)};

    using Properties::Properties;
  };

  enum struct PlayMode {
		poly, mono, unison
  };

  std::string to_string(PlayMode) noexcept;

  struct SettingsProps : props::Properties<> {

        props::Property<PlayMode, props::wrap> play_mode = {this, "Play Mode", PlayMode::poly,
                                           props::has_limits::init(PlayMode::poly, PlayMode::unison)};

    props::Property<float> portamento = {this, "Portamento", 0,
                                     	   props::has_limits::init(0, 1),
                                         props::steppable::init(0.01)};

    props::Property<int> octave = {this, "Octave", 0,
                                   props::has_limits::init(-2, 7)};

    props::Property<int> transpose = {this, "Transpose", 0,
                                      props::has_limits::init(-12, 12)};
    using Properties::Properties;
  };


  namespace detail {
    std::unique_ptr<ui::Screen> make_envelope_screen(EnvelopeProps& props);
    std::unique_ptr<ui::Screen> make_settings_screen(SettingsProps& props);
  }

  template<int N>
  struct VoiceManager {

    props::Properties<props::no_serialize> voices_props;

    std::array<VoiceProps, N> voices = util::generate_array<N>(
      [this](auto n) { return VoiceProps(&voices_props, std::to_string(n)); });

    EnvelopeProps envelope_props;
    SettingsProps settings_props;

    VoiceManager(props::properties_base& parent)
      : voices_props(&parent, "voices"),
        envelope_props(&parent, "envelope"),
        settings_props(&parent, "voice_settings"),
        envelope_screen_(detail::make_envelope_screen(envelope_props)),
        settings_screen_(detail::make_settings_screen(settings_props))
    {
      for (int i = 0; i < N; ++i){
        free_voices.push_back(i);
      }
    }

    void process_before(audio::ProcessData<0> data);
    void process_after(audio::ProcessData<0> data);

    ui::Screen& envelope_screen() noexcept
    {
      return *envelope_screen_;
    }
    ui::Screen& settings_screen() noexcept
    {
      return *settings_screen_;
    }

    // Voice managagement //

  private:

    auto get_voice(char key) -> Voice;
    void stop_voice(char key);

    std::deque<Voice> free_voices;
    std::vector<NoteVoicePair> note_stack;

    props::properties_base* currently_linked;

    std::unique_ptr<ui::Screen> envelope_screen_;
    std::unique_ptr<ui::Screen> settings_screen_;
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
  auto VoiceManager<N>::get_voice(char key) -> Voice
  {
    if (free_voices.size() > 0) {
      auto it = util::find_if(note_stack, [key] (auto& nvp) { return nvp.note == key; });
      auto fvit = it == note_stack.end() ? free_voices.begin() : util::find(free_voices, it->voice);
      auto v = *fvit;
      free_voices.erase(fvit);
      return v;
    } else {
      auto found =
        util::find_if(note_stack, [](auto& nvp) { return nvp.has_voice(); });
      if (found != note_stack.end()) {
        Voice v = found->voice;
        found->voice = Voice{-1};
        voices[v].midi.trigger = false;
        DLOGI("Stealing voice {} from key {}", v, found->note);
        return v;
      } else {
        DLOGE("No voice found. Using voice 0");
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
        vp.midi.freq     = midi::note_freq(found->note + settings_props.octave * 12 + settings_props.transpose);
      } else {
        auto& vp = voices[v];
        free_voices.push_back(v);
        vp.midi.trigger = false;
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
                  [this](midi::NoteOnEvent ev) {
                    stop_voice(gsl::narrow_cast<char>(ev.key));
                    Voice v = get_voice(ev.key);
                    note_stack.push_back({gsl::narrow_cast<char>(ev.key), v});
                    auto& vp         = voices[v];
                    vp.midi.freq     = midi::note_freq(ev.key + settings_props.octave * 12 + settings_props.transpose);
                    vp.midi.velocity = ev.velocity / 127.f;
                    vp.midi.trigger  = 1;
                    DLOGI("Voice {} begin key {} {}Hz velocity: {}", v, ev.key, vp.midi.freq, vp.midi.velocity);
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
