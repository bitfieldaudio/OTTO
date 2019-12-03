#include "audio.hpp"
#include "util/math.hpp"

namespace otto::engines::ottofm {

  // VOICE //
  Voice::Voice(Audio& a) noexcept : audio(a)
  {
    for (auto& op : operators) op.finish();
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
    for (auto& op : operators) op.reset();
  }

  void Voice::release_envelopes() noexcept
  {
    for (auto& op : operators) op.release();
  }

  void Voice::set_frequencies() noexcept
  {
    for (auto& op : operators) {
      op.freq(frequency() * op.freq_ratio_ + op.detune_amount_);
    }
  }

  // Actionhandlers
  void Audio::action(itc::prop_change<&Props::algN>, int a) noexcept
  {
    algN_ = a;
  }
  
  // Voice process. We apply voice volume and increment voice frequency with next() manually, 
  // since we are overwriting the default process method. 
  audio::ProcessData<1> Voice::process(audio::ProcessData<1> data) noexcept
  {
    switch (audio.algN_) {
      case 0: {
        for (float& f : data.audio) {
          next();
          f += operators[0](operators[1](operators[2](operators[3](0)))) * volume();
        } 
        break; 
      } 
      case 1: {
        for (float& f : data.audio){
          next();
          f +=  operators[0](operators[1](operators[2](0) + operators[3](0))) * volume();
        } 
        break;
      }
      case 2: {
        for (float& f : data.audio){
          next();
          f +=  operators[0](operators[1](operators[2](0)) + operators[3](0)) * volume();
        }
        break;
      }
      case 3: {
        for (float& f : data.audio) {
          next();
          float aux = operators[3](0);  
          f += operators[0](operators[1](aux) + operators[2](aux)) * volume();
        }
        break;
      }
      case 4: {
        for (float& f : data.audio) {
          next();
          float aux = operators[2](operators[3](0));
          f += operators[0](aux) + operators[1](aux) * volume();
        }
        break;
      }
      case 5: {
        for (float& f : data.audio) {
          next();
          f += operators[0](0) + operators[1](operators[2](operators[3](0))) * volume();
        }
        break;
      }
      case 6: { 
        for (float& f : data.audio) {
          next();
          f += operators[0](operators[1](0) + operators[2](0) + operators[3](0)) * volume();
        }
        break;
      }
      case 7: { 
        for (float& f : data.audio) {
          next();
          f += operators[0](operators[1](0)) + operators[2](operators[3](0)) * volume();
        }
        break;
      }
      case 8: { 
        for (float& f : data.audio) { 
          next();
          float aux = operators[3](0);
          f += operators[0](aux) + operators[1](aux) + operators[2](aux) * volume();
        }
        break;
      }
      case 9: { 
        for (float& f : data.audio) {
          next();
          f += operators[0](0) + operators[1](0) + operators[2](operators[3](0)) * volume();
        }
        break;
      }
      case 10: { 
        for (float& f : data.audio){
          next();
          f += operators[0](0) + operators[1](0) + operators[2](0) + operators[3](0) * volume();
        }
        break;
      }
      return data;
    }
  }

  // Audio //
  float Audio::get_activity_level(int op) noexcept
  {
    if (last_voice->operators[op].modulator)
      return last_voice->operators[op].level();
    else
      return last_voice->env_.value() * last_voice->operators[op].outlevel;
  }

  audio::ProcessData<1> Audio::process(audio::ProcessData<1> data) noexcept
  {
    for (auto& m : data.midi) voice_mgr_.handle_midi(m);
    for (auto& v : voice_mgr_.voices()) {
      // Adds to data. Do we need to zero first?
      v.process(data);
    }
    // Set activity values for last triggered voice
    *shared_activity0 = get_activity_level(0);
    *shared_activity1 = get_activity_level(1);
    *shared_activity2 = get_activity_level(2);
    *shared_activity3 = get_activity_level(3);

    return data;
  }


}