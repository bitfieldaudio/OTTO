#include "audio.hpp"
#include "util/math.hpp"

namespace otto::engines::ottofm {

  // VOICE //
  Voice::Voice(Audio& a) noexcept : audio(a)
  {
    util::tuple_for_each(operators, [](auto& op){op.finish();});
  }

  void Voice::on_note_on(float freq_target) noexcept
  {
    reset_envelopes();
    audio.last_voice = this;
  }

  void Voice::on_note_off() noexcept
  {
    release_envelopes();
  }

  void Voice::reset_envelopes() noexcept
  {
    util::tuple_for_each(operators, [](auto& op){op.reset();});
  }

  void Voice::release_envelopes() noexcept
  {
    util::tuple_for_each(operators, [](auto& op){op.release();});
  }

  void Voice::set_frequencies() noexcept
  {
    util::tuple_for_each(operators, [this](auto& op){ op.freq(frequency()); } );
  }
  
  // Voice process. We apply voice volume and increment voice frequency with next() manually, 
  // since we are overwriting the default process method. 
  audio::ProcessData<1> Voice::process(audio::ProcessData<1> data) noexcept
  {
    switch (audio.algN_) {
      case 0: {
        for (float& f : data.audio) {
          next();
          set_frequencies();
          f += std::get<0>(operators)(std::get<1>(operators)(std::get<2>(operators)(std::get<3>(operators)(0)))) * volume();
        } 
        break; 
      } 
      case 1: {
        for (float& f : data.audio){
          next();
          set_frequencies();
          f += std::get<0>(operators)(std::get<1>(operators)(std::get<2>(operators)(0) + std::get<3>(operators)(0))) * volume();
        } 
        break;
      }
      case 2: {
        for (float& f : data.audio){
          next();
          set_frequencies();
          f +=  std::get<0>(operators)(std::get<1>(operators)(std::get<2>(operators)(0)) + std::get<3>(operators)(0)) * volume();
        }
        break;
      }
      case 3: {
        for (float& f : data.audio) {
          next();
          set_frequencies();
          float aux = std::get<3>(operators)(0);  
          f += std::get<0>(operators)(std::get<1>(operators)(aux) + std::get<2>(operators)(aux)) * volume();
        }
        break;
      }
      case 4: {
        for (float& f : data.audio) {
          next();
          set_frequencies();
          float aux = std::get<2>(operators)(std::get<3>(operators)(0));
          f += (std::get<0>(operators)(aux) + std::get<1>(operators)(aux)) * volume();
        }
        break;
      }
      case 5: {
        for (float& f : data.audio) {
          next();
          set_frequencies();
          f += (std::get<0>(operators)(0) + std::get<1>(operators)(std::get<2>(operators)(std::get<3>(operators)(0)))) * volume();
        }
        break;
      }
      case 6: { 
        for (float& f : data.audio) {
          next();
          set_frequencies();
          f += std::get<0>(operators)(std::get<1>(operators)(0) + std::get<2>(operators)(0) + std::get<3>(operators)(0)) * volume();
        }
        break;
      }
      case 7: { 
        for (float& f : data.audio) {
          next();
          set_frequencies();
          f += (std::get<0>(operators)(std::get<1>(operators)(0)) + std::get<2>(operators)(std::get<3>(operators)(0))) * volume();
        }
        break;
      }
      case 8: { 
        for (float& f : data.audio) { 
          next();
          set_frequencies();
          float aux = std::get<3>(operators)(0);
          f += (std::get<0>(operators)(aux) + std::get<1>(operators)(aux) + std::get<2>(operators)(aux)) * volume();
        }
        break;
      }
      case 9: { 
        for (float& f : data.audio) {
          next();
          set_frequencies();
          f += (std::get<0>(operators)(0) + std::get<1>(operators)(0) + std::get<2>(operators)(std::get<3>(operators)(0))) * volume();
        }
        break;
      }
      case 10: { 
        for (float& f : data.audio){
          next();
          set_frequencies();
          f += (std::get<0>(operators)(0) + std::get<1>(operators)(0) + std::get<2>(operators)(0) + std::get<3>(operators)(0)) * volume();
        }
        break;
      }
      default: break;
    }
    return data;
  }

  // Audio //

  audio::ProcessData<1> Audio::process(audio::ProcessData<1> data) noexcept
  {
    for (auto& m : data.midi) voice_mgr_.handle_midi(m);
    for (auto& v : voice_mgr_.voices()) {
      // Adds to data. Do we need to zero first?
      v.process(data);
    }
    // Set activity values for last triggered voice
    *shared_activity0 = std::get<0>(last_voice->operators).get_activity_level();
    *shared_activity1 = std::get<1>(last_voice->operators).get_activity_level();
    *shared_activity2 = std::get<2>(last_voice->operators).get_activity_level();
    *shared_activity3 = std::get<3>(last_voice->operators).get_activity_level();

    return data;
  }


}