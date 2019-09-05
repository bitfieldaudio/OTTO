#pragma once

#include "core/engine/engine.hpp"
#include "core/voices/voice_manager.hpp"

#include <Gamma/Oscillator.h>

namespace otto::engines {

    using namespace core;
    using namespace core::engine;
    using namespace props;

    struct EngineClassName : SynthEngine<EngineClassName> {
        static constexpr util::string_ref name = "EngineClassName";
        struct Props {

            Property<float> level = {0.8, limits(0, 1), step_size(0.01)};

            DECL_REFLECTION(Props, level);
        } props;

        EngineClassName();

        audio::ProcessData<1> process(audio::ProcessData<1>) override;

        voices::IVoiceManager& voice_mgr() override
        {
          return voice_mgr_;
        }

        DECL_REFLECTION(EngineClassName, props, ("voice_manager", &EngineClassName::voice_mgr_));

    private:
        struct Pre : voices::PreBase<Pre, Props> {
            Pre(Props&) noexcept;

            //
            // Here you declare variables needed for Pre. These variables are also available
            // in each voice.
            //

            // The call operator calculates what is needed for the next audio sample,
            // and is called before the individual voices.
            void operator()() noexcept;
        };

        struct Voice : voices::VoiceBase<Voice, Pre> {
            Voice(Pre&) noexcept;

            //
            // Here you declare variables needed for each voice.
            // Example:
            gam::Sine<> sine_osc;

            //Call operator calculates one new sample from the voice
            float operator()() noexcept;

            // on_note_on is called every time a voice is retriggered.
            // Note that it might not be called, depending on legato settings
            // freq_target is the frequency the note will be playing. It might not
            // be the current frequency of the voice, if portamento is on. However,
            // this is rarely relevant.
            void on_note_on(float freq_target) noexcept;

            // If anything needs to be done when the key is lifted.
            // Examples could be internal envelopes not related to the amp envelope.
            void on_note_off() noexcept;
        };

        struct Post : voices::PostBase<Post, Voice> {
            Post(Pre&) noexcept;

            //
            // Here you declare variables needed for Post.
            // Example:
            float output_level = 1;

            // The call operator is called after the individual voices.
            float operator()(float) noexcept;
        };

        voices::VoiceManager<Post, 6> voice_mgr_;
    };
} // namespace otto::engines
