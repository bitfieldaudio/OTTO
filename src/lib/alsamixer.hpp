#pragma once

#include <string>
#include <utility>
#include <vector>

#include <alsa/asoundlib.h>
#include <alsa/mixer.h>

#include "lib/util/enum.hpp"
#include "lib/util/exception.hpp"
#include "lib/util/string_ref.hpp"

#include "lib/logging.hpp"

#include "fmt/core.h"
#include "fmt/format.h"
#include "fmt/ostream.h"

namespace otto::alsa {

  using Channel = ::snd_mixer_selem_channel_id_t;
  std::string channel_name(Channel c) noexcept;

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
    Mixer(const std::string& card);
    ~Mixer() noexcept;

    [[nodiscard]] ::snd_mixer_t* native_handle() const;

    [[nodiscard]] Elem find_elem(util::string_ref) const;

  private:
    ::snd_mixer_t* handle_ = nullptr;
  };

  enum struct ControlDirection {
    playback,
    capture,
  };

  struct Elem {
    Elem(::snd_mixer_elem_t* h);

    [[nodiscard]] ::snd_mixer_elem_t* native_handle() const;
    [[nodiscard]] util::string_ref get_name() const;

    [[nodiscard]] bool has_common_switch() const;
    [[nodiscard]] bool has_common_volume() const;
    [[nodiscard]] bool has_volume(ControlDirection) const;
    [[nodiscard]] bool has_switch(ControlDirection) const;
    [[nodiscard]] bool has_channel(ControlDirection, Channel c) const;

    [[nodiscard]] bool is_enumerated() const;

    [[nodiscard]] Channel find_channel(ControlDirection) const;
    [[nodiscard]] Channel find_channel() const;

    [[nodiscard]] std::vector<std::string> enum_items() const;

    friend std::ostream& operator<<(std::ostream& os, const Elem& e)
    {
      os << e.get_name() << ": ";
      if (e.has_common_switch()) os << "COMSW ";
      if (e.has_common_volume()) os << "COMVOL ";
      if (e.has_volume(ControlDirection::playback)) os << "PLAYVOL ";
      if (e.has_volume(ControlDirection::capture)) os << "CAPTVOL ";
      if (e.has_switch(ControlDirection::playback)) os << "PLAYSW ";
      if (e.has_switch(ControlDirection::capture)) os << "CAPTSW ";
      if (e.is_enumerated()) {
        auto items = e.enum_items();
        fmt::print(os, "[{}] ", fmt::join(items, ", "));
      }
      return os;
    }

  private:
    ::snd_mixer_elem_t* handle_ = nullptr;
  };

  std::vector<Elem> get_elems(Mixer& m);

  struct IControl {
    virtual ~IControl() = default;
    [[nodiscard]] const std::string& get_name() const;
    [[nodiscard]] const Elem& get_elem() const;
    [[nodiscard]] Channel get_channel() const;
    [[nodiscard]] ControlDirection get_direction() const;

    [[nodiscard]] virtual std::string value_str() const = 0;

  protected:
    IControl(Elem elem, std::string name, ControlDirection dir, Channel c)
      : elem_(elem), name_{std::move(name)}, dir_(dir), channel_(c)
    {}
    Elem elem_;
    std::string name_;
    ControlDirection dir_;
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

  struct Switch : Control<bool> {
    Switch(Elem& e, ControlDirection dir, Channel c) : Control(e, "switch", dir, c) {}
    using Control::operator=;
    void set_value(bool b) override;
    [[nodiscard]] bool get_value() const override;
  };

  struct Volume : Control<float> {
    Volume(Elem& e, ControlDirection dir, Channel c) : Control(e, "volume", dir, c) {}
    using Control::operator=;
    void set_value(float f) override;
    [[nodiscard]] float get_value() const override;
  };

  struct EnumControl : Control<int> {
    EnumControl(Elem& e, Channel c);
    EnumControl(Elem& e);
    using Control::operator=;

    void set_value(int i) override;
    [[nodiscard]] int get_value() const override;
    [[nodiscard]] const std::vector<std::string>& enum_items() const;
    [[nodiscard]] std::string value_str() const override;
    int index_of(std::string_view str);

  private:
    std::vector<std::string> enum_items_;
  };

  struct SwitchAll : Switch {
    SwitchAll(Elem& e, ControlDirection dir) : Switch(e, dir, e.find_channel(dir)) {}
    using Switch::operator=;
    void set_value(bool b) override;
  };

  struct VolumeAll : Volume {
    VolumeAll(Elem& e, ControlDirection dir) : Volume(e, dir, e.find_channel(dir)) {}
    using Volume::operator=;
    void set_value(float f) override;
  };

  std::vector<std::unique_ptr<IControl>> get_controls(Elem& elem, std::vector<std::unique_ptr<IControl>>&& vec = {});

  std::vector<std::unique_ptr<IControl>> get_controls_all_channels(Elem& elem,
                                                                   std::vector<std::unique_ptr<IControl>>&& vec = {});

  template<typename Control, ControlDirection Dir>
  struct ControlWithDir : Control {
    ControlWithDir(Elem& e) : Control(e, Dir) {}
    using Control::operator=;
  };

  using PlaybackSwitchAll = ControlWithDir<SwitchAll, ControlDirection::playback>;
  using CaptureSwitchAll = ControlWithDir<SwitchAll, ControlDirection::capture>;
  using PlaybackVolumeAll = ControlWithDir<VolumeAll, ControlDirection::playback>;
  using CaptureVolumeAll = ControlWithDir<VolumeAll, ControlDirection::capture>;

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
    struct BasicElemProp<EnumControl> {
      EnumControl enum_control;
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
