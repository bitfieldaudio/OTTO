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
        int note = -1;
        float velocity = 0.8;

        bool triggered() const noexcept {
          return note >= 0;
        }

        void clear() noexcept {
          note = -1;
        }

        DECL_REFLECTION(Step, note, velocity);
      };
      std::array<Step, 16 * substeps> steps;

      DECL_REFLECTION(MonoSequence, steps);
    };

    struct PolySequence {
      struct Step {
        util::local_vector<std::uint8_t, 6> notes = {};
        float velocity = 1.0;
        int length = substeps;

        bool triggered() const noexcept {
          return !notes.empty();
        }

        void clear() noexcept {
          notes.clear();
        }

        DECL_REFLECTION(Step, notes, velocity, length);
      };
      std::array<Step, 16 * substeps> steps;

      DECL_REFLECTION(PolySequence, steps);
    };

    template<std::size_t N>
    struct SamplerGroup {
      util::selectable<std::array<Sampler, N>> samplers;
      MonoSequence seq;
      std::array<bool, N> mutes;

      DECL_REFLECTION(SamplerGroup, samplers, seq, mutes);

      void process(audio::AudioBufferHandle d, int step) noexcept;
    };

    struct Props {
      SamplerGroup<2> group0;
      SamplerGroup<3> group1;
      SamplerGroup<2> group2;
      SamplerGroup<3> group3;

      PolySequence synth_seq;
      PolySequence ext_seq;

      Property<int> cur_step = 0;

      DECL_REFLECTION(Props, group0, group1, group2, group3, synth_seq, ext_seq);
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

    int smpl_counter = 0;
  };

} // namespace otto::engines
