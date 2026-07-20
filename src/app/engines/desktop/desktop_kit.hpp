#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <fmt/format.h>

#include "lib/json.hpp"
#include "lib/midi.hpp"
#include "lib/skia/skia.hpp"
#include "lib/util/audio_buffer.hpp"

#include "lib/graphics.hpp"

#include "app/engines/stubs/stubs.hpp"
#include "app/engines/synths/ottofm/state.hpp"
#include "app/input.hpp"
#include "app/layers/navigator.hpp"
#include "app/services/graphics.hpp"

namespace otto::engines::desktop {

  // --- Stereo delay (fx1) ----------------------------------------------------

  struct DelayFx {
    float time = 0.35f;
    float feedback = 0.35f;
    float mix = 0.25f;
    std::vector<float> buf_l{48000, 0.f};
    std::vector<float> buf_r{48000, 0.f};
    std::size_t write = 0;
    unsigned sample_rate = 48000;

    void set_sample_rate(unsigned sr)
    {
      if (sr == sample_rate || sr == 0) return;
      sample_rate = sr;
      buf_l.assign(sample_rate, 0.f);
      buf_r.assign(sample_rate, 0.f);
      write = 0;
    }

    void process(util::stereo_audio_buffer& out)
    {
      const std::size_t delay_samples =
        std::clamp<std::size_t>(static_cast<std::size_t>(time * float(sample_rate)), 1, buf_l.size() - 1);
      for (std::size_t i = 0; i < out.left.size(); ++i) {
        const std::size_t read = (write + buf_l.size() - delay_samples) % buf_l.size();
        const float dl = buf_l[read];
        const float dr = buf_r[read];
        const float inl = out.left[i];
        const float inr = out.right[i];
        buf_l[write] = inl + dl * feedback;
        buf_r[write] = inr + dr * feedback;
        out.left[i] = inl * (1.f - mix) + dl * mix;
        out.right[i] = inr * (1.f - mix) + dr * mix;
        write = (write + 1) % buf_l.size();
      }
    }
  };

  // --- Soft clip (fx2) -------------------------------------------------------

  struct SaturatorFx {
    float drive = 1.5f;
    float mix = 0.4f;

    void process(util::stereo_audio_buffer& out) const
    {
      auto sat = [this](float x) {
        const float d = x * drive;
        const float y = std::tanh(d);
        return x * (1.f - mix) + y * mix;
      };
      for (std::size_t i = 0; i < out.left.size(); ++i) {
        out.left[i] = sat(out.left[i]);
        out.right[i] = sat(out.right[i]);
      }
    }
  };

  // --- Mixer gain ------------------------------------------------------------

  struct MixerGain {
    float level = 1.f;

    void process(util::stereo_audio_buffer& out) const
    {
      for (std::size_t i = 0; i < out.left.size(); ++i) {
        out.left[i] *= level;
        out.right[i] *= level;
      }
    }
  };

  // --- 16-step sequencer -----------------------------------------------------

  struct StepSequencer {
    std::array<bool, 16> steps = {true, false, false, false, true, false, false, false,
                                  true, false, false, false, true, false, true, false};
    int root = 48;
    int bpm = 120;
    int current = 0;
    std::size_t buffer_count = 0;
    int buffers_per_step = 10;
    tl::optional<std::uint8_t> held;
    midi::IMidiHandler* target = nullptr;
    std::shared_ptr<stubs::TransportModel> transport;

    void set_timing(unsigned sample_rate, unsigned buffer_size)
    {
      if (buffer_size == 0 || sample_rate == 0) return;
      const float bufs_per_min = (float(sample_rate) * 60.f) / float(buffer_size);
      buffers_per_step = std::max(1, int(bufs_per_min / (float(bpm) * 4.f)));
    }

    void process()
    {
      if (target == nullptr || transport == nullptr) return;
      if (!transport->playing) {
        if (held) {
          target->handle(midi::NoteOff{.note = *held});
          held = tl::nullopt;
        }
        return;
      }
      if (buffer_count % std::size_t(buffers_per_step) == 0) {
        if (held) {
          target->handle(midi::NoteOff{.note = *held});
          held = tl::nullopt;
        }
        if (steps[std::size_t(current)]) {
          const auto note = static_cast<std::uint8_t>(std::clamp(root, 0, 127));
          target->handle(midi::NoteOn{.note = note, .velocity = 100});
          held = note;
        }
        current = (current + 1) % 16;
      }
      ++buffer_count;
    }
  };

  // --- Preset adapt (legacy OTTO.FM → ottofm::State) --------------------------

  inline ottofm::State adapt_ottofm_preset(const json::value& root)
  {
    ottofm::State out;
    const auto& props = root.at("props").at("props");
    if (props.contains("algorithm_idx")) out.algorithm_idx = props.at("algorithm_idx").get<int>();
    if (props.contains("fm_amount")) out.fm_amount = props.at("fm_amount").get<float>();
    if (props.contains("cur_op")) out.cur_op_idx = props.at("cur_op").get<int>();
    if (props.contains("operators") && props.at("operators").is_array()) {
      const auto& ops = props.at("operators");
      for (std::size_t i = 0; i < std::min(ops.size(), out.operators.size()); ++i) {
        const auto& op = ops[i];
        auto& dst = out.operators[i];
        if (op.contains("attack")) dst.envelope.attack = op.at("attack").get<float>();
        if (op.contains("decay_release")) {
          dst.envelope.decay = op.at("decay_release").get<float>();
          dst.envelope.release = op.at("decay_release").get<float>();
        }
        if (op.contains("suspos")) dst.envelope.sustain = op.at("suspos").get<float>();
        if (op.contains("out_level")) dst.level = op.at("out_level").get<float>();
        if (op.contains("feedback")) dst.shape = op.at("feedback").get<float>();
        if (op.contains("detune")) dst.detune = op.at("detune").get<float>();
        if (op.contains("ratio_idx")) dst.ratio_idx = op.at("ratio_idx").get<int>();
      }
    }
    return out;
  }

  inline std::vector<std::filesystem::path> list_fm_presets(const std::filesystem::path& data_dir)
  {
    std::vector<std::filesystem::path> out;
    const auto dir = data_dir / "presets" / "OTTO.FM";
    if (!std::filesystem::exists(dir)) return out;
    for (const auto& e : std::filesystem::directory_iterator(dir)) {
      if (e.path().extension() == ".json") out.push_back(e.path());
    }
    std::sort(out.begin(), out.end());
    return out;
  }

  inline ottofm::State load_ottofm_preset_file(const std::filesystem::path& path)
  {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Could not open preset");
    json::value root;
    in >> root;
    return adapt_ottofm_preset(root);
  }

  // --- Screens ---------------------------------------------------------------

  inline ScreenWithHandler make_delay_screen(std::shared_ptr<DelayFx> fx)
  {
    struct Screen final : ScreenBase {
      explicit Screen(std::shared_ptr<DelayFx> f) : fx_(std::move(f)) {}
      void draw(skia::Canvas& ctx) noexcept override
      {
        skia::place_text(ctx, "DELAY", fonts::black(26), paints::fill(colors::white), {160, 36}, anchors::center);
        skia::place_text(ctx, fmt::format("TIME  {:.2f}s", fx_->time), fonts::regular(18), paints::fill(colors::blue),
                         {40, 100}, anchors::top_left);
        skia::place_text(ctx, fmt::format("FB    {:.0f}%", fx_->feedback * 100), fonts::regular(18),
                         paints::fill(colors::green), {40, 140}, anchors::top_left);
        skia::place_text(ctx, fmt::format("MIX   {:.0f}%", fx_->mix * 100), fonts::regular(18),
                         paints::fill(colors::yellow), {40, 180}, anchors::top_left);
      }
      std::shared_ptr<DelayFx> fx_;
    };
    struct Handler final : IInputLayer {
      explicit Handler(std::shared_ptr<DelayFx> f) : fx_(std::move(f)) {}
      [[nodiscard]] KeySet key_mask() const noexcept override
      {
        return key_groups::enc_clicks;
      }
      void handle(KeyPress) noexcept override {}
      void handle(KeyRelease) noexcept override {}
      void handle(EncoderEvent e) noexcept override
      {
        if (e.encoder == Encoder::blue) fx_->time = std::clamp(fx_->time + e.steps * 0.01f, 0.05f, 0.9f);
        if (e.encoder == Encoder::green) fx_->feedback = std::clamp(fx_->feedback + e.steps * 0.01f, 0.f, 0.95f);
        if (e.encoder == Encoder::yellow) fx_->mix = std::clamp(fx_->mix + e.steps * 0.01f, 0.f, 1.f);
      }
      std::shared_ptr<DelayFx> fx_;
    };
    return {std::make_unique<Screen>(fx), std::make_unique<Handler>(fx)};
  }

  inline ScreenWithHandler make_saturator_screen(std::shared_ptr<SaturatorFx> fx)
  {
    struct Screen final : ScreenBase {
      explicit Screen(std::shared_ptr<SaturatorFx> f) : fx_(std::move(f)) {}
      void draw(skia::Canvas& ctx) noexcept override
      {
        skia::place_text(ctx, "SATURATE", fonts::black(26), paints::fill(colors::white), {160, 36}, anchors::center);
        skia::place_text(ctx, fmt::format("DRIVE {:.1f}", fx_->drive), fonts::regular(18), paints::fill(colors::blue),
                         {40, 110}, anchors::top_left);
        skia::place_text(ctx, fmt::format("MIX   {:.0f}%", fx_->mix * 100), fonts::regular(18),
                         paints::fill(colors::yellow), {40, 150}, anchors::top_left);
      }
      std::shared_ptr<SaturatorFx> fx_;
    };
    struct Handler final : IInputLayer {
      explicit Handler(std::shared_ptr<SaturatorFx> f) : fx_(std::move(f)) {}
      [[nodiscard]] KeySet key_mask() const noexcept override
      {
        return key_groups::enc_clicks;
      }
      void handle(KeyPress) noexcept override {}
      void handle(KeyRelease) noexcept override {}
      void handle(EncoderEvent e) noexcept override
      {
        if (e.encoder == Encoder::blue) fx_->drive = std::clamp(fx_->drive + e.steps * 0.05f, 0.5f, 8.f);
        if (e.encoder == Encoder::yellow) fx_->mix = std::clamp(fx_->mix + e.steps * 0.01f, 0.f, 1.f);
      }
      std::shared_ptr<SaturatorFx> fx_;
    };
    return {std::make_unique<Screen>(fx), std::make_unique<Handler>(fx)};
  }

  inline ScreenWithHandler make_mixer_screen(std::shared_ptr<MixerGain> mix)
  {
    struct Screen final : ScreenBase {
      explicit Screen(std::shared_ptr<MixerGain> m) : mix_(std::move(m)) {}
      void draw(skia::Canvas& ctx) noexcept override
      {
        skia::place_text(ctx, "MIXER", fonts::black(26), paints::fill(colors::white), {160, 36}, anchors::center);
        skia::place_text(ctx, fmt::format("LEVEL {:.0f}%", mix_->level * 100), fonts::regular(22),
                         paints::fill(colors::blue), {160, 120}, anchors::center);
        skia::place_text(ctx, "Blue encoder · Master has global volume", fonts::regular(12),
                         paints::fill(colors::grey50), {160, 180}, anchors::center);
      }
      std::shared_ptr<MixerGain> mix_;
    };
    struct Handler final : IInputLayer {
      explicit Handler(std::shared_ptr<MixerGain> m) : mix_(std::move(m)) {}
      [[nodiscard]] KeySet key_mask() const noexcept override
      {
        return key_groups::enc_clicks;
      }
      void handle(KeyPress) noexcept override {}
      void handle(KeyRelease) noexcept override {}
      void handle(EncoderEvent e) noexcept override
      {
        if (e.encoder == Encoder::blue) mix_->level = std::clamp(mix_->level + e.steps * 0.01f, 0.f, 1.5f);
      }
      std::shared_ptr<MixerGain> mix_;
    };
    return {std::make_unique<Screen>(mix), std::make_unique<Handler>(mix)};
  }

  inline ScreenWithHandler make_seq_screen(std::shared_ptr<StepSequencer> seq)
  {
    struct Screen final : ScreenBase {
      explicit Screen(std::shared_ptr<StepSequencer> s) : seq_(std::move(s)) {}
      void draw(skia::Canvas& ctx) noexcept override
      {
        skia::place_text(ctx, "SEQUENCER", fonts::black(22), paints::fill(colors::white), {160, 28}, anchors::center);
        skia::place_text(ctx, fmt::format("BPM {}  ROOT {}", seq_->bpm, seq_->root), fonts::regular(14),
                         paints::fill(colors::grey50), {160, 52}, anchors::center);
        for (int i = 0; i < 16; ++i) {
          const float x = 20.f + (i % 8) * 36.f;
          const float y = 90.f + (i / 8) * 50.f;
          const bool on = seq_->steps[std::size_t(i)];
          const bool cur = i == seq_->current;
          ctx.drawRect(skia::Box{{x, y}, {28, 28}},
                       paints::fill(cur ? colors::green : (on ? colors::blue : colors::grey70)));
        }
        skia::place_text(ctx, "Blue:cursor  Green click:toggle  Yellow:BPM  Red:root", fonts::regular(11),
                         paints::fill(colors::grey50), {160, 220}, anchors::center);
      }
      std::shared_ptr<StepSequencer> seq_;
    };
    struct Handler final : IInputLayer {
      explicit Handler(std::shared_ptr<StepSequencer> s) : seq_(std::move(s)) {}
      int cursor = 0;
      [[nodiscard]] KeySet key_mask() const noexcept override
      {
        return key_groups::enc_clicks;
      }
      void handle(KeyPress e) noexcept override
      {
        if (e.key == Key::green_enc_click) seq_->steps[std::size_t(cursor)] = !seq_->steps[std::size_t(cursor)];
      }
      void handle(KeyRelease) noexcept override {}
      void handle(EncoderEvent e) noexcept override
      {
        if (e.encoder == Encoder::blue) cursor = (cursor + e.steps + 16 * 8) % 16;
        if (e.encoder == Encoder::yellow) seq_->bpm = std::clamp(seq_->bpm + e.steps, 40, 240);
        if (e.encoder == Encoder::red) seq_->root = std::clamp(seq_->root + e.steps, 24, 84);
      }
      std::shared_ptr<StepSequencer> seq_;
    };
    return {std::make_unique<Screen>(seq), std::make_unique<Handler>(seq)};
  }

  inline ScreenWithHandler make_preset_screen(std::vector<std::filesystem::path> presets,
                                              std::function<void(const std::filesystem::path&)> on_load)
  {
    struct Model {
      std::vector<std::filesystem::path> presets;
      int idx = 0;
      std::string status = "Yellow click to load";
      std::function<void(const std::filesystem::path&)> on_load;
    };
    auto model = std::make_shared<Model>(Model{std::move(presets), 0, "Yellow click to load", std::move(on_load)});
    struct Screen final : ScreenBase {
      explicit Screen(std::shared_ptr<Model> m) : m_(std::move(m)) {}
      void draw(skia::Canvas& ctx) noexcept override
      {
        skia::place_text(ctx, "PRESETS", fonts::black(26), paints::fill(colors::white), {160, 36}, anchors::center);
        if (m_->presets.empty()) {
          skia::place_text(ctx, "No OTTO.FM presets in data/", fonts::regular(16), paints::fill(colors::grey50),
                           {160, 120}, anchors::center);
          return;
        }
        const auto& p = m_->presets[std::size_t(m_->idx)];
        skia::place_text(ctx, p.stem().string(), fonts::black(22), paints::fill(colors::blue), {160, 110},
                         anchors::center);
        skia::place_text(ctx, fmt::format("{}/{}", m_->idx + 1, m_->presets.size()), fonts::regular(14),
                         paints::fill(colors::grey50), {160, 150}, anchors::center);
        skia::place_text(ctx, m_->status, fonts::regular(14), paints::fill(colors::green), {160, 190}, anchors::center);
      }
      std::shared_ptr<Model> m_;
    };
    struct Handler final : IInputLayer {
      explicit Handler(std::shared_ptr<Model> m) : m_(std::move(m)) {}
      [[nodiscard]] KeySet key_mask() const noexcept override
      {
        return key_groups::enc_clicks;
      }
      void handle(KeyPress e) noexcept override
      {
        if (e.key == Key::yellow_enc_click && !m_->presets.empty()) {
          try {
            m_->on_load(m_->presets[std::size_t(m_->idx)]);
            m_->status = "Loaded!";
          } catch (const std::exception& ex) {
            m_->status = ex.what();
          }
        }
      }
      void handle(KeyRelease) noexcept override {}
      void handle(EncoderEvent e) noexcept override
      {
        if (m_->presets.empty()) return;
        if (e.encoder == Encoder::blue || e.encoder == Encoder::green) {
          const int n = int(m_->presets.size());
          m_->idx = (m_->idx + e.steps % n + n) % n;
          m_->status = "Yellow click to load";
        }
      }
      std::shared_ptr<Model> m_;
    };
    return {std::make_unique<Screen>(model), std::make_unique<Handler>(model)};
  }

} // namespace otto::engines::desktop
