#pragma once

#include <cmath>
#include <numbers>

#include <Gamma/Oscillator.h>

#include "lib/graphics/ads.hpp"
#include "lib/graphics/adsr.hpp"
#include "lib/skia/anim.hpp"
#include "lib/skia/skia.hpp"
#include "lib/widget.hpp"

#include "app/engines/synths/nuke/state.hpp"

#include "nuke.hpp"

namespace otto::engines::nuke {

  struct FourParams : graphics::Widget<FourParams> {
    const std::string title;
    const std::array<std::string, 4> params;

    float a = 0;
    float b = 0;
    float c = 0;
    float d = 0;

    FourParams(std::string t, std::array<std::string, 4> p = {"param 0", "param 1", "param 2", "param 3"})
      : title(t), params(p){};

    void set(const std::array<float, 4>& t);

    void do_draw(skia::Canvas& ctx);
  };


  inline float lfo_take_graphics(gam::LFO<gam::phsInc::Loop, gam::Domain1>& lfo, LfoShapes& shape)
  {
    switch (shape) {
      case LfoShapes::constant: return 1.f; break;
      case LfoShapes::up: return lfo.up(); break;
      case LfoShapes::down: return lfo.down(); break;
      case LfoShapes::tri: return lfo.tri(); break;
      case LfoShapes::sqr: return lfo.sqr(); break;
      case LfoShapes::sine: return lfo.sineP9(); break;
      case LfoShapes::C2: return lfo.C2(); break;
      case LfoShapes::S5: return lfo.S5(); break;
      default: return 0.f;
    }
  }

  template<typename Rng>
  void fill_wave(Rng& rng, LfoShapes shape, const int num_samples, const int num_periods)
  {
    // Create LFO object
    gam::LFO<gam::phsInc::Loop, gam::Domain1> lfo;
    float frequency = static_cast<float>(num_periods) / num_samples;
    lfo.freq(frequency);

    auto get_next = [&]() { return lfo_take_graphics(lfo, shape); };
    std::generate(rng.begin(), rng.end(), get_next);
  }

  struct NukeLFO : graphics::Widget<NukeLFO> {
    float attack = 0.2;
    float decay = 0.2;
    float speed = 1;
    int lfo_type = 0;
    bool active = false;
    float expanded = 0;
    float active_segment = 0;

    static const int wave_resolution = 50;
    static const int wave_periods = 5;
    std::array<float, wave_resolution * wave_periods> wave_samples;
    float wave_step = 1; // Should be between 1 and 5

    NukeLFO()
    {
      fill_wave(wave_samples, LfoShapes::sine, wave_samples.size(), wave_periods);
    }

    void update_wave()
    {
      fill_wave(wave_samples, static_cast<LfoShapes>(static_cast<int>(lfo_type)), wave_samples.size(), wave_periods);
    }

    void do_draw(skia::Canvas& ctx)
    {
      const float width = bounding_box.width();
      const float height = bounding_box.height();
      const float spacing = width / 16.f;
      const float max_width = width / 2.5f;
      const float aw = max_width * attack;
      const float dw = max_width * decay;

      const float arc_size = 0.2f * expanded + 0.5f;
      const float attack_arc_size = 0.5f - 0.5f * expanded;

      const float a_active = std::clamp(1 - active_segment, 0.f, 1.f);
      const float d_active = active_segment < 1 ? 0 : std::clamp(1 - (active_segment - 1), 0.f, 1.f);

      constexpr int min_width = 4;
      constexpr int min_width2 = 2;
      // Draw rects
      skia::Rect rect = skia::Rect::MakeXYWH(0, 0, aw + min_width, bounding_box.height());
      skia::RRect rrect = skia::RRect::MakeRectXY(rect, 4, 4);
      skia::Paint paint = paints::stroke(colors::yellow.mix(colors::black, static_cast<float>(!active) * 0.8f), 4.f);
      ctx.drawRRect(rrect, paint);

      rect = skia::Rect::MakeXYWH(aw + spacing - min_width2, 0, width - 2 * spacing - aw - dw + min_width,
                                  bounding_box.height());
      rrect = skia::RRect::MakeRectXY(rect, 4, 4);
      paint = paints::stroke(colors::blue.mix(colors::black, static_cast<float>(!active) * 0.8f), 4.f);
      ctx.drawRRect(rrect, paint);

      rect = skia::Rect::MakeXYWH(width - dw - min_width, 0, dw + min_width, bounding_box.height());
      rrect = skia::RRect::MakeRectXY(rect, 4, 4);
      paint = paints::stroke(colors::red.mix(colors::black, static_cast<float>(!active) * 0.8f), 4.f);
      ctx.drawRRect(rrect, paint);

      // Wave
      const float offset = 10;
      const float x_distance = (width - 2 * offset) / wave_resolution;
      const float y_mid = height / 2;
      const float wave_y_scale = height / 3.5f;
      skia::Path path;
      path.moveTo(offset, y_mid - wave_samples[0] * wave_y_scale);
      for (auto i = 0; i < wave_resolution; i++) {
        path.lineTo(i * x_distance + offset, y_mid - wave_samples[static_cast<int>(i * wave_step)] * wave_y_scale);
      }
      ctx.drawPath(path, paints::stroke(colors::black, 10.f));
      ctx.drawPath(path, paints::stroke(colors::green.mix(colors::black, static_cast<float>(!active) * 0.8f), 4.f));
    }
  };

  struct LFOGraphic {
    LFOGraphic(int idx) : index(idx) {}
    int index;
    bool active = false;
    NukeLFO graphic;
    skia::Anim<float> size = {0, 0.25};

    void on_state_change(const State& s)
    {
      graphic.wave_step = s.lfo_speed * 5;
      graphic.attack = s.lfo_attack;
      graphic.decay = s.lfo_decay;
      // Only change type if necessary
      if (graphic.lfo_type != s.lfo_type) {
        graphic.lfo_type = s.lfo_type;
        graphic.update_wave();
      }
      active = s.active_idx == index;
      graphic.active = active;
      size = active ? 1.f : 0.f;
    }
  };

  struct ADSRGraphic {
    ADSRGraphic(int idx) : index(idx) {}
    int index;
    bool active = false;
    graphics::ADSR graphic;
    skia::Anim<float> size = {0, 0.25};

    void on_state_change(const State& s)
    {
      graphic.a = s.attack;
      graphic.d = s.decay;
      graphic.s = s.sustain;
      graphic.r = s.release;
      active = s.active_idx == index;
      graphic.active = active;
      size = active ? 1.f : 0.f;
    }

    int will_change(const State& s)
    {
      if (graphic.a != s.attack) return 1;
      if (graphic.d != s.decay) return 2;
      if (graphic.s != s.sustain) return 3;
      if (graphic.r != s.release) return 4;
      return 0;
    }
  };

  struct ADSGraphic {
    ADSGraphic(int idx) : index(idx) {}
    int index;
    bool active = false;
    graphics::ADS graphic;
    skia::Anim<float> size = {0, 0.25};

    void on_state_change(const State& s)
    {
      graphic.a = s.filter_attack;
      graphic.d = s.filter_decay;
      graphic.s = s.filter_sustain;
      graphic.x = s.filter_amount;
      active = s.active_idx == index;
      graphic.active = active;
      size = active ? 1.f : 0.f;
    }

    int will_change(const State& s)
    {
      if (graphic.a != s.filter_attack) return 1;
      if (graphic.d != s.filter_decay) return 2;
      if (graphic.s != s.filter_sustain) return 3;
      if (graphic.x != s.filter_amount) return 4;
      return 0;
    }
  };

  struct Level : graphics::Widget<Level> {
    Level(std::string t, skia::Color c) : title_(t), color_(c) {}

    float value = 0;
    float expansion = 0;
    bool active = false;

    void do_draw(skia::Canvas& ctx);

  private:
    std::string title_;
    skia::Color color_;
  };

  struct Targets : graphics::Widget<Targets> {
    int index;
    std::array<Level, 4> levels = {
      {{"PITCH", colors::blue}, {"VOLUME", colors::green}, {"FILTER", colors::yellow}, {"OSC 2", colors::red}}};
    skia::Anim<float> expansion = {0, 0.25};

    float expanded = 0;

    Targets(int i) : index(i)
    {
      for (int i = 0; i < levels.size(); i++) {
        auto& l = levels[i];
        l.bounding_box.move_to({i * 77, 0});
        l.bounding_box.resize({40, 40});
      }
      bounding_box.resize({240, 40});
    }

    void on_state_change(const State& s)
    {
      levels[0].value = s.lfo_pitch_amount;
      levels[1].value = s.lfo_volume_amount;
      levels[2].value = s.lfo_filter_amount;
      levels[3].value = s.lfo_osc2_pitch_amount;
      bool active = s.active_idx == index;
      expansion = active ? 1.f : 0.f;
      for (auto& l : levels) l.active = active;
    }

    void do_draw(skia::Canvas& ctx)
    {
      bounding_box.resize({240, 20 + 20 * expansion});
      for (auto& l : levels) {
        l.expansion = expansion;
        l.draw(ctx);
      }
    }
  };



} // namespace otto::engines::nuke
