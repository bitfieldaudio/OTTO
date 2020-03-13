#pragma once

#include <Gamma/Domain.h>

#include "services/application.hpp"
#include "services/audio_manager.hpp"
#include "services/clock_manager.hpp"
#include "services/engine_manager.hpp"
#include "services/log_manager.hpp"
#include "services/preset_manager.hpp"
#include "services/state_manager.hpp"
#include "services/ui_manager.hpp"

namespace otto::services::test {

  struct DummyStateManager final : StateManager {
    void load() override
    {
      LOGI("DummyStateManager::load()");
    }
    void save() override
    {
      LOGI("DummyStateManager::save()");
    }
    void attach(std::string name, Loader load, Saver save) override
    {
      // LOGI("DummyStateManager::attach({})", name);
    }
    void detach(std::string name) override
    {
      LOGI("DummyStateManager::detach({})", name);
    }
  };

  struct DummyPresetManager final : PresetManager {
    const std::vector<std::string>& preset_names(util::string_ref engine_name) override
    {
      LOGI("DummyPresetManager::preset_names()");
      static std::vector<std::string> res;
      return res;
    };

    const std::string& name_of_idx(util::string_ref engine_name, int idx) override
    {
      LOGI("DummyPresetManager::name_of_idx()");
      static std::string res;
      return res;
    }

    int idx_of_name(util::string_ref engine_name, std::string_view name) override
    {
      LOGI("DummyPresetManager::idx_of_name()");
      return 0;
    }

    void apply_preset(core::engine::IEngine& engine, std::string_view name, bool no_enable_callback = false) override
    {
      LOGI("DummyPresetManager::apply_preset()");
    }

    void apply_preset(core::engine::IEngine& engine, int idx, bool no_enable_callback = false) override
    {
      LOGI("DummyPresetManager::apply_preset()");
    }

    void create_preset(util::string_ref engine_name,
                       std::string_view preset_name,
                       const nlohmann::json& preset_data) override
    {
      LOGI("DummyPresetManager::create_preset()");
    }
  };

  struct DummyUIManager final : UIManager {
    DummyUIManager() = default;

    void main_ui_loop() override {}

    void draw_frame(core::ui::vg::Canvas& ctx)
    {
      UIManager::draw_frame(ctx);
    }
    void display(core::ui::Screen& screen, core::input::InputHandler& input)
    {
      UIManager::display({screen, input});
    }

    static DummyUIManager& current()
    {
      return dynamic_cast<DummyUIManager&>(UIManager::current());
    }
  };

  struct DummyController final : Controller {
    void set_color(LED, LEDColor) override{};
    void flush_leds() override {}
    void clear_leds() override {}
  };

  struct DummyEngineManager final : EngineManager {
    void start() override {}
    core::audio::ProcessData<2> process(core::audio::ProcessData<2> external_in) override
    {
      if (on_process) return on_process(external_in);
      OTTO_UNREACHABLE;
    }

    static DummyEngineManager& current()
    {
      return dynamic_cast<DummyEngineManager&>(EngineManager::current());
    }

    std::function<core::audio::ProcessData<2>(core::audio::ProcessData<2> external_in)> on_process = nullptr;
  };

  struct DummyAudioManager final : AudioManager {
    DummyAudioManager()
    {
      set_bs_sr(256, 44100);
    }

    core::audio::ProcessData<2> process()
    {
      pre_process_tasks();

      int nframes = _buffer_size;
      static int r1 = 0;
      using namespace core::audio;

      auto running = this->running() && Application::current().running();
      if (!running) {
        return {{AudioBufferHandle(nullptr, 0, r1), AudioBufferHandle(nullptr, 0, r1)}};
      }

      if ((unsigned) nframes > _buffer_size) {
        LOGE("RTAudio requested more frames than expected");
        return {{AudioBufferHandle(nullptr, 0, r1), AudioBufferHandle(nullptr, 0, r1)}};
      }

      midi_bufs.swap();

      auto in_buf = Application::current().audio_manager->buffer_pool().allocate_multi_clear<2>();
      // steal the inner midi buffer
      auto out = Application::current().engine_manager->process(
        {in_buf, {std::move(midi_bufs.inner())}, core::clock::ClockRange()});

      // process_audio_output(out);

      LOGW_IF(out.nframes != nframes, "Frames went missing!");

      // return the midi buffer
      midi_bufs.inner() = out.midi.move_vector_out();

      return out;
    }

    void set_bs_sr(int buffer_size, int sample_rate)
    {
      _buffer_size = buffer_size;
      buffer_pool().set_buffer_size(buffer_size);
      gam::sampleRate(sample_rate);
    }

    static DummyAudioManager& current()
    {
      return dynamic_cast<DummyAudioManager&>(*Application::current().audio_manager);
    }

    void line_in_gain_l(float) override {}
    void line_in_gain_r(float) override {}
    void output_vol(float) override {}
  };

  inline Application make_dummy_application()
  {
    return {
      std::make_unique<LogManager>,        std::make_unique<DummyStateManager>,  std::make_unique<DummyPresetManager>,
      std::make_unique<DummyAudioManager>, ClockManager::create_default,         std::make_unique<DummyUIManager>,
      std::make_unique<DummyController>,   std::make_unique<DummyEngineManager>,
    };
  }

  inline Application make_dummy_application_default_engines()
  {
    return {
      std::make_unique<LogManager>,        std::make_unique<DummyStateManager>, std::make_unique<DummyPresetManager>,
      std::make_unique<DummyAudioManager>, ClockManager::create_default,        std::make_unique<DummyUIManager>,
      std::make_unique<DummyController>,   EngineManager::create_default,
    };
  }
} // namespace otto::services::test
