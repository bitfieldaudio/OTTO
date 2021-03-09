#pragma once

#include <string>
#include <utility>
#include <vector>

#include <alsa/asoundlib.h>
#include <alsa/mixer.h>

#include "lib/util/enum.hpp"
#include "lib/util/exception.hpp"
#include "lib/util/string_ref.hpp"

#include "fmt/core.h"
#include "fmt/format.h"
#include "fmt/ostream.h"

namespace otto::alsa {

  using Channel = ::snd_mixer_selem_channel_id_t;
  using exception = util::exception;

  constexpr std::array<Channel, SND_MIXER_SCHN_LAST> all_channels = [] {
    std::array<Channel, SND_MIXER_SCHN_LAST> res = {};
    for (int i = 0; i < res.size(); i++) {
      res[i] = Channel(i);
    }
    return res;
  }();

  namespace detail {
    /// Check error code and throw exception if error detected
    inline void check_err(int res)
    {
      if (res == 0) return;
      throw exception("Alsa error: {}", snd_strerror(res));
    }
  } // namespace detail

  struct Elem;

  struct Mixer {
    Mixer(const std::string& card)
    {
      int mode = 0;
      detail::check_err(snd_mixer_open(&handle_, mode));
      detail::check_err(snd_mixer_attach(handle_, card.c_str()));
      detail::check_err(snd_mixer_selem_register(handle_, nullptr, nullptr));
      detail::check_err(snd_mixer_load(handle_));
    }

    ~Mixer() noexcept
    {
      snd_mixer_close(handle_);
    }

    [[nodiscard]] ::snd_mixer_t* native_handle() const
    {
      return handle_;
    }

    [[nodiscard]] Elem find_elem(util::string_ref) const;

  private:
    ::snd_mixer_t* handle_ = nullptr;
  };

  struct Elem {
    Elem(::snd_mixer_elem_t* h) : handle_(h) {}

    [[nodiscard]] ::snd_mixer_elem_t* native_handle() const
    {
      return handle_;
    }

    [[nodiscard]] util::string_ref get_name() const
    {
      return snd_mixer_selem_get_name(handle_);
    }

    [[nodiscard]] bool has_common_switch() const
    {
      return snd_mixer_selem_has_common_switch(handle_) == 1;
    }

    [[nodiscard]] bool has_common_volume() const
    {
      return snd_mixer_selem_has_common_volume(handle_) == 1;
    }

    [[nodiscard]] bool has_playback_volume() const
    {
      return snd_mixer_selem_has_playback_volume(handle_) == 1;
    }

    [[nodiscard]] bool has_capture_volume() const
    {
      return snd_mixer_selem_has_capture_volume(handle_) == 1;
    }

    [[nodiscard]] bool has_playback_switch() const
    {
      return snd_mixer_selem_has_playback_switch(handle_) == 1;
    }

    [[nodiscard]] bool has_capture_switch() const
    {
      return snd_mixer_selem_has_capture_switch(handle_) == 1;
    }

    [[nodiscard]] bool has_playback_channel(Channel c) const
    {
      return snd_mixer_selem_has_playback_channel(handle_, c) == 1;
    }

    [[nodiscard]] bool has_capture_channel(Channel c) const
    {
      return snd_mixer_selem_has_capture_channel(handle_, c) == 1;
    }

    [[nodiscard]] bool is_enumerated() const
    {
      return snd_mixer_selem_is_enumerated(handle_) == 1;
    }

    [[nodiscard]] bool is_enum_playback() const
    {
      return snd_mixer_selem_is_enum_playback(handle_) == 1;
    }

    [[nodiscard]] bool is_enum_capture() const
    {
      return snd_mixer_selem_is_enum_capture(handle_) == 1;
    }

    [[nodiscard]] Channel find_playback_channel() const
    {
      for (auto c : all_channels) {
        if (has_playback_channel(c)) return c;
      }
      return SND_MIXER_SCHN_UNKNOWN;
    }

    [[nodiscard]] Channel find_capture_channel() const
    {
      for (auto c : all_channels) {
        if (has_capture_channel(c)) return c;
      }
      return SND_MIXER_SCHN_UNKNOWN;
    }

    [[nodiscard]] Channel find_channel() const
    {
      for (auto c : all_channels) {
        if (has_playback_channel(c) || has_capture_channel(c)) return c;
      }
      return SND_MIXER_SCHN_UNKNOWN;
    }

    [[nodiscard]] std::vector<std::string> enum_items() const
    {
      std::vector<std::string> res;
      auto count = snd_mixer_selem_get_enum_items(handle_);
      for (int i = 0; i < count; i++) {
        std::array<char, 20> buf = {'\0'};
        detail::check_err(snd_mixer_selem_get_enum_item_name(handle_, i, buf.size(), buf.data()));
        res.emplace_back(buf.data());
      }
      return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const Elem& e)
    {
      os << e.get_name() << ": ";
      if (e.has_common_switch()) os << "COMSW ";
      if (e.has_common_volume()) os << "COMVOL ";
      if (e.has_playback_volume()) os << "PLAYVOL ";
      if (e.has_capture_volume()) os << "CAPTVOL ";
      if (e.has_playback_switch()) os << "PLAYSW ";
      if (e.has_capture_switch()) os << "CAPTSW ";
      if (e.is_enumerated()) {
        auto items = e.enum_items();
        fmt::print(os, "[{}] ", fmt::join(items, ", "));
      }
      return os;
    }

  private:
    ::snd_mixer_elem_t* handle_ = nullptr;
  };

  inline Elem Mixer::find_elem(util::string_ref name) const
  {
    ::snd_mixer_selem_id_t* id = nullptr;
    snd_mixer_selem_id_alloca(&id); // NOLINT
    snd_mixer_selem_id_set_index(id, 0);
    snd_mixer_selem_id_set_name(id, name.c_str());
    ::snd_mixer_elem_t* res = snd_mixer_find_selem(native_handle(), id);
    if (res == nullptr) throw exception("No mixer element found with name '{}'", name);
    return Elem(res);
  }

  inline std::string channel_name(Channel c) noexcept
  {
    return ::snd_mixer_selem_channel_name(c);
  }

  inline std::vector<Elem> get_elems(Mixer& m)
  {
    std::vector<Elem> res;
    ::snd_mixer_elem_t* elem = snd_mixer_first_elem(m.native_handle());
    while (elem != nullptr) {
      res.emplace_back(elem);
      elem = snd_mixer_elem_next(elem);
    }
    return res;
  }

  struct IControl {
    virtual ~IControl() = default;
    [[nodiscard]] const std::string& get_name() const
    {
      return name_;
    }

    [[nodiscard]] const Elem& get_elem() const
    {
      return elem_;
    }

    [[nodiscard]] Channel get_channel() const
    {
      return channel_;
    }

    [[nodiscard]] virtual std::string value_str() const = 0;

  protected:
    IControl(Elem elem, std::string name, Channel c) : elem_(elem), name_{std::move(name)}, channel_(c) {}
    Elem elem_;
    std::string name_;
    Channel channel_;
  };

  template<typename T>
  struct Control : IControl {
    virtual void set_value(T) = 0;
    [[nodiscard]] virtual T get_value() const = 0;
    [[nodiscard]] std::string value_str() const override
    {
      return fmt::to_string(get_value());
    }

    Control& operator=(T t)
    {
      set_value(t);
      return *this;
    }

  protected:
    using IControl::IControl;
  };

  struct PlaybackSwitch : Control<bool> {
    PlaybackSwitch(Elem& e, Channel c) : Control(e, "Playback switch", c) {}
    using Control::operator=;
    void set_value(bool b) override
    {
      detail::check_err(::snd_mixer_selem_set_playback_switch(elem_.native_handle(), channel_, static_cast<int>(b)));
    }
    [[nodiscard]] bool get_value() const override
    {
      int res = -1;
      detail::check_err(::snd_mixer_selem_get_playback_switch(elem_.native_handle(), channel_, &res));
      return res == 1;
    }
  };

  struct CaptureSwitch : Control<bool> {
    CaptureSwitch(Elem& e, Channel c) : Control(e, "Capture switch", c) {}
    using Control::operator=;
    void set_value(bool b) override
    {
      detail::check_err(::snd_mixer_selem_set_capture_switch(elem_.native_handle(), channel_, static_cast<int>(b)));
    }
    [[nodiscard]] bool get_value() const override
    {
      int res = -1;
      detail::check_err(::snd_mixer_selem_get_capture_switch(elem_.native_handle(), channel_, &res));
      return res == 1;
    }
  };

  struct PlaybackVolume : Control<float> {
    PlaybackVolume(Elem& e, Channel c) : Control(e, "Playback volume", c) {}
    using Control::operator=;
    void set_value(float f) override
    {
      long min = 0;
      long max = 0;
      detail::check_err(::snd_mixer_selem_get_playback_volume_range(elem_.native_handle(), &min, &max));
      long i = min + static_cast<long>(static_cast<float>(min - max) * f);
      detail::check_err(::snd_mixer_selem_set_playback_volume(elem_.native_handle(), channel_, i));
    }
    [[nodiscard]] float get_value() const override
    {
      long res = -1;
      detail::check_err(::snd_mixer_selem_get_playback_volume(elem_.native_handle(), channel_, &res));
      long min = 0;
      long max = 0;
      detail::check_err(::snd_mixer_selem_get_playback_volume_range(elem_.native_handle(), &min, &max));
      return static_cast<float>(res - min) / static_cast<float>(max - min);
    }
  };

  struct CaptureVolume : Control<float> {
    CaptureVolume(Elem& e, Channel c) : Control(e, "Capture volume", c) {}
    using Control::operator=;
    void set_value(float f) override
    {
      long min = 0;
      long max = 0;
      detail::check_err(::snd_mixer_selem_get_capture_volume_range(elem_.native_handle(), &min, &max));
      long i = min + static_cast<long>(static_cast<float>(min - max) * f);
      detail::check_err(::snd_mixer_selem_set_capture_volume(elem_.native_handle(), channel_, i));
    }
    [[nodiscard]] float get_value() const override
    {
      long res = -1;
      detail::check_err(::snd_mixer_selem_get_capture_volume(elem_.native_handle(), channel_, &res));
      long min = 0;
      long max = 0;
      detail::check_err(::snd_mixer_selem_get_capture_volume_range(elem_.native_handle(), &min, &max));
      return static_cast<float>(res - min) / static_cast<float>(max - min);
    }
  };

  struct EnumControl : Control<int> {
    EnumControl(Elem& e, Channel c) : Control(e, "Enum", c), enum_items_(e.enum_items()) {}
    using Control::operator=;

    void set_value(int i) override
    {
      detail::check_err(::snd_mixer_selem_set_enum_item(elem_.native_handle(), channel_, i));
    }
    [[nodiscard]] int get_value() const override
    {
      unsigned int res = -1;
      detail::check_err(::snd_mixer_selem_get_enum_item(elem_.native_handle(), channel_, &res));
      return static_cast<int>(res);
    }

    [[nodiscard]] const std::vector<std::string>& enum_items() const
    {
      return enum_items_;
    }

    [[nodiscard]] std::string value_str() const override
    {
      return enum_items_.at(get_value());
    }

    int index_of(std::string_view str)
    {
      auto found = std::ranges::find(enum_items_, str);
      if (found == enum_items_.end()) throw std::out_of_range("alsamixer: No enum value given name");
      return static_cast<int>(found - enum_items_.begin());
    }

  private:
    std::vector<std::string> enum_items_;
  };

  struct PlaybackSwitchAll : Control<bool> {
    PlaybackSwitchAll(Elem& e) : Control(e, "Playback switch", e.find_playback_channel()) {}
    using Control::operator=;
    void set_value(bool b) override
    {
      detail::check_err(::snd_mixer_selem_set_playback_switch_all(elem_.native_handle(), static_cast<int>(b)));
    }
    [[nodiscard]] bool get_value() const override
    {
      int res = -1;
      detail::check_err(::snd_mixer_selem_get_playback_switch(elem_.native_handle(), channel_, &res));
      return res == 1;
    }
  };

  struct CaptureSwitchAll : Control<bool> {
    CaptureSwitchAll(Elem& e) : Control(e, "Capture switch", e.find_capture_channel()) {}
    using Control::operator=;
    void set_value(bool b) override
    {
      detail::check_err(::snd_mixer_selem_set_capture_switch(elem_.native_handle(), channel_, static_cast<int>(b)));
    }
    [[nodiscard]] bool get_value() const override
    {
      int res = -1;
      detail::check_err(::snd_mixer_selem_get_capture_switch(elem_.native_handle(), channel_, &res));
      return res == 1;
    }
  };

  struct PlaybackVolumeAll : Control<float> {
    PlaybackVolumeAll(Elem& e) : Control(e, "Playback volume", e.find_playback_channel()) {}
    using Control::operator=;
    void set_value(float f) override
    {
      long min = 0;
      long max = 0;
      detail::check_err(::snd_mixer_selem_get_playback_volume_range(elem_.native_handle(), &min, &max));
      long i = min + static_cast<long>(static_cast<float>(min - max) * f);
      detail::check_err(::snd_mixer_selem_set_playback_volume(elem_.native_handle(), channel_, i));
    }
    [[nodiscard]] float get_value() const override
    {
      long res = -1;
      detail::check_err(::snd_mixer_selem_get_playback_volume(elem_.native_handle(), channel_, &res));
      long min = 0;
      long max = 0;
      detail::check_err(::snd_mixer_selem_get_playback_volume_range(elem_.native_handle(), &min, &max));
      return static_cast<float>(res - min) / static_cast<float>(max - min);
    }
  };

  struct CaptureVolumeAll : Control<float> {
    CaptureVolumeAll(Elem& e) : Control(e, "Capture volume", e.find_capture_channel()) {}
    using Control::operator=;
    void set_value(float f) override
    {
      long min = 0;
      long max = 0;
      detail::check_err(::snd_mixer_selem_get_capture_volume_range(elem_.native_handle(), &min, &max));
      long i = min + static_cast<long>(static_cast<float>(min - max) * f);
      detail::check_err(::snd_mixer_selem_set_capture_volume(elem_.native_handle(), channel_, i));
    }
    [[nodiscard]] float get_value() const override
    {
      long res = -1;
      detail::check_err(::snd_mixer_selem_get_capture_volume(elem_.native_handle(), channel_, &res));
      long min = 0;
      long max = 0;
      detail::check_err(::snd_mixer_selem_get_capture_volume_range(elem_.native_handle(), &min, &max));
      return static_cast<float>(res - min) / static_cast<float>(max - min);
    }
  };


  struct EnumControlAll : EnumControl {
    EnumControlAll(Elem& e) : EnumControl(e, e.find_channel()) {}
    using EnumControl::operator=;

    void set_value(int i) override
    {
      for (auto c : all_channels) {
        if (elem_.has_playback_channel(c) || elem_.has_capture_channel(c)) {
          detail::check_err(::snd_mixer_selem_set_enum_item(elem_.native_handle(), channel_, i));
        }
      }
    }
  };


  inline std::vector<std::unique_ptr<IControl>> get_controls(Elem& elem,
                                                             std::vector<std::unique_ptr<IControl>>&& vec = {})
  {
    if (elem.has_common_switch() || elem.has_playback_switch()) {
      for (auto c : all_channels) {
        if (elem.has_playback_channel(c)) vec.emplace_back(std::make_unique<PlaybackSwitch>(elem, c));
      }
    }
    if (!elem.has_common_switch() && elem.has_capture_switch()) {
      for (auto c : all_channels) {
        if (elem.has_capture_channel(c)) vec.emplace_back(std::make_unique<CaptureSwitch>(elem, c));
      }
    }
    if (elem.has_common_volume() || elem.has_playback_volume()) {
      for (auto c : all_channels) {
        if (elem.has_playback_channel(c)) vec.emplace_back(std::make_unique<PlaybackVolume>(elem, c));
      }
    }
    if (!elem.has_common_volume() && elem.has_capture_volume()) {
      for (auto c : all_channels) {
        if (elem.has_capture_channel(c)) vec.emplace_back(std::make_unique<CaptureVolume>(elem, c));
      }
    }
    if (elem.is_enumerated()) {
      for (auto c : all_channels) {
        if (elem.has_playback_channel(c) || elem.has_capture_channel(c)) {
          vec.emplace_back(std::make_unique<EnumControl>(elem, c));
        }
      }
    }
    return std::move(vec);
  }

  inline std::vector<std::unique_ptr<IControl>> get_controls_all_channels(
    Elem& elem,
    std::vector<std::unique_ptr<IControl>>&& vec = {})
  {
    if (elem.has_common_switch() || elem.has_playback_switch()) {
      vec.emplace_back(std::make_unique<PlaybackSwitchAll>(elem));
    }
    if (!elem.has_common_switch() && elem.has_capture_switch()) {
      vec.emplace_back(std::make_unique<CaptureSwitchAll>(elem));
    }
    if (elem.has_common_volume() || elem.has_playback_volume()) {
      vec.emplace_back(std::make_unique<PlaybackVolumeAll>(elem));
    }
    if (!elem.has_common_volume() && elem.has_capture_volume()) {
      vec.emplace_back(std::make_unique<CaptureVolumeAll>(elem));
    }
    if (elem.is_enumerated()) {
      for (auto c : all_channels) {
        if (elem.has_playback_channel(c) || elem.has_capture_channel(c)) {
          vec.emplace_back(std::make_unique<EnumControl>(elem, c));
        }
      }
    }
    return std::move(vec);
  }

  namespace detail {
    template<typename Control>
    struct BasicElemProp;

    template<>
    struct BasicElemProp<PlaybackSwitchAll> {
      PlaybackSwitchAll playback_switch;
    };

    template<>
    struct BasicElemProp<CaptureSwitchAll> {
      CaptureSwitchAll capture_switch;
    };

    template<>
    struct BasicElemProp<PlaybackVolumeAll> {
      PlaybackVolumeAll playback_volume;
    };

    template<>
    struct BasicElemProp<CaptureVolumeAll> {
      CaptureVolumeAll capture_volume;
    };

    template<>
    struct BasicElemProp<EnumControlAll> {
      EnumControlAll enum_control;
    };
  } // namespace detail

  template<typename... Controls>
  struct ElemProp : detail::BasicElemProp<Controls>... {
    ElemProp(Elem elem) : detail::BasicElemProp<Controls>{elem}... {}
  };

  template<typename Control>
  struct ElemProp<Control> : Control {
    ElemProp(Elem elem) : Control{elem} {}
    using Control::operator=;
  };

} // namespace otto::alsa
