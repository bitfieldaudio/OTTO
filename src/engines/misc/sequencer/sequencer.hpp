#pragma once

#include "core/engine/engine.hpp"
#include "util/local_vector.hpp"
#include "util/selectable.hpp"

#include "engines/misc/sampler/sampler.hpp"

namespace otto::engines {

  using namespace otto::core;
  using namespace otto::core::engine;

  struct Sequencer : MiscEngine<Sequencer> {
    constexpr static int substeps = 12;

    constexpr static util::string_ref name = "Sequencer";

    struct MonoSequence {
      struct Step {
        bool trig = false;
        float velocity = 0.8;

        bool triggered() const noexcept
        {
          return trig;
        }

        void clear() noexcept
        {
          trig = false;
        }

        DECL_REFLECTION(Step, trig, velocity);
      };
      std::array<Step, 16 * substeps> steps;

      DECL_REFLECTION(MonoSequence, steps);
    };

    struct PolySequence {
      struct Step {
        util::local_vector<std::uint8_t, 6> notes = {};
        float velocity = 1.0;
        int length = substeps;

        bool triggered() const noexcept
        {
          return !notes.empty();
        }

        void clear() noexcept
        {
          notes.clear();
        }

        DECL_REFLECTION(Step, notes, velocity, length);
      };
      std::array<Step, 16 * substeps> steps;

      DECL_REFLECTION(PolySequence, steps);
    };

    struct SamplerSequence : MonoSequence {
      Sampler sampler;
      bool muted;

      DECL_REFLECTION(SamplerSequence, sampler, muted, steps);

      void process(audio::AudioBufferHandle d, int step) noexcept;
    };

    struct Props {
      std::array<SamplerSequence, 10> sampler_seqs;
      PolySequence synth_seq;
      PolySequence ext_seq;

      Property<int> cur_step = -1;

      DECL_REFLECTION(Props, sampler_seqs, synth_seq, ext_seq);
    } props;

    Sequencer();

    ui::Screen& sampler_screen() noexcept;
    ui::Screen& envelope_screen() noexcept;

    audio::ProcessData<1> process(audio::ProcessData<0>) noexcept;

  private:
    friend struct SeqScreen;

    /// @param f callable as `f(SamplerGroup, int idx)`
    template<typename F>
    auto for_cur_chan(F&& f);

    /// @param f callable as `f(SamplerGroup, int idx)`
    template<typename F>
    auto for_chan(services::ChannelEnum, F&& f);

    /// @param f callable as `f(ChannelEnum, SamplerGroup, int idx)`
    template<typename F>
    void for_all_chans(F&& f);
  };

} // namespace otto::engines
