#include "alsamixer.hpp"
namespace otto::alsa {

  template<typename... ExtrArgs>
  using SelemFunMap = util::enum_map<ControlDirection, util::function_ptr<int(::snd_mixer_elem_t*, ExtrArgs...)>>;

  namespace cd {
    constexpr SelemFunMap<> has_switch = {{
      {ControlDirection::playback, snd_mixer_selem_has_playback_switch},
      {ControlDirection::capture, snd_mixer_selem_has_capture_switch},
    }};
    constexpr SelemFunMap<> has_volume = {{
      {ControlDirection::playback, snd_mixer_selem_has_playback_volume},
      {ControlDirection::capture, snd_mixer_selem_has_capture_volume},
    }};
    constexpr SelemFunMap<Channel> has_channel = {{
      {ControlDirection::playback, snd_mixer_selem_has_playback_channel},
      {ControlDirection::capture, snd_mixer_selem_has_capture_channel},
    }};
    constexpr SelemFunMap<long*, long*> get_dB_range = {{
      {ControlDirection::playback, snd_mixer_selem_get_playback_dB_range},
      {ControlDirection::capture, snd_mixer_selem_get_capture_dB_range},
    }};
    constexpr SelemFunMap<long*, long*> get_raw_range = {
      {ControlDirection::playback, snd_mixer_selem_get_playback_volume_range},
      {ControlDirection::capture, snd_mixer_selem_get_capture_volume_range},
    };
    constexpr SelemFunMap<Channel, long*> get_dB = {
      {ControlDirection::playback, snd_mixer_selem_get_playback_dB},
      {ControlDirection::capture, snd_mixer_selem_get_capture_dB},
    };
    constexpr SelemFunMap<Channel, long*> get_raw = {
      {ControlDirection::playback, snd_mixer_selem_get_playback_volume},
      {ControlDirection::capture, snd_mixer_selem_get_capture_volume},
    };
    constexpr SelemFunMap<Channel, long, int> set_dB = {
      {ControlDirection::playback, snd_mixer_selem_set_playback_dB},
      {ControlDirection::capture, snd_mixer_selem_set_capture_dB},
    };
    constexpr SelemFunMap<Channel, long> set_raw = {
      {ControlDirection::playback, snd_mixer_selem_set_playback_volume},
      {ControlDirection::capture, snd_mixer_selem_set_capture_volume},
    };
    constexpr SelemFunMap<Channel, int*> get_switch = {
      {ControlDirection::playback, snd_mixer_selem_get_playback_switch},
      {ControlDirection::capture, snd_mixer_selem_get_capture_switch},
    };
    constexpr SelemFunMap<Channel, int> set_switch = {
      {ControlDirection::playback, snd_mixer_selem_set_playback_switch},
      {ControlDirection::capture, snd_mixer_selem_set_capture_switch},
    };
    constexpr SelemFunMap<int> set_switch_all = {
      {ControlDirection::playback, snd_mixer_selem_set_playback_switch_all},
      {ControlDirection::capture, snd_mixer_selem_set_capture_switch_all},
    };
  } // namespace cd

  /**
   * Volume mapping adapted from alsa-utils/alsamixer/volume_mapping.c
   *
   * Copyright notice for this part:
   * ----------------------------------------------------------------------------
   * Copyright (c) 2010 Clemens Ladisch <clemens@ladisch.de>
   *
   * Permission to use, copy, modify, and/or distribute this software for any
   * purpose with or without fee is hereby granted, provided that the above
   * copyright notice and this permission notice appear in all copies.
   *
   * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
   * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
   * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
   * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
   * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
   * ----------------------------------------------------------------------------
   *
   * Documentation from alsamixer:
   * ----------------------------------------------------------------------------
   *
   * The functions in this file map the value ranges of ALSA mixer controls onto
   * the interval 0..1.
   *
   * The mapping is designed so that the position in the interval is proportional
   * to the volume as a human ear would perceive it (i.e., the position is the
   * cubic root of the linear sample multiplication factor).  For controls with
   * a small range (24 dB or less), the mapping is linear in the dB values so
   * that each step has the same size visually.  Only for controls without dB
   * information, a linear mapping of the hardware volume register values is used
   * (this is the same algorithm as used in the old alsamixer).
   *
   * When setting the volume, 'dir' is the rounding direction:
   * -1/0/1 = down/nearest/up.
   */
  namespace volume_mapping {
    constexpr long max_linear_db_scale = 24;
    static inline bool use_linear_dB_scale(long dBmin, long dBmax)
    {
      return dBmax - dBmin <= max_linear_db_scale * 100;
    }

    static long lrint_dir(float x, int dir)
    {
      if (dir > 0) {
        return std::lrint(std::ceil(x));
      }
      if (dir < 0) {
        return std::lrint(std::floor(x));
      }
      return std::lrint(x);
    }

    float get_normalized_volume(snd_mixer_elem_t* elem, snd_mixer_selem_channel_id_t channel, ControlDirection ctl_dir)
    {
      long value = 0;
      float normalized = 0;
      float min_norm = 0;

      long min = 0;
      long max = 0;
      int err = cd::get_dB_range[ctl_dir](elem, &min, &max);
      if (err < 0 || min >= max) {
        err = cd::get_raw_range[ctl_dir](elem, &min, &max);
        if (err < 0 || min == max) return 0;

        err = cd::get_raw[ctl_dir](elem, channel, &value);
        if (err < 0) return 0;

        return float(value - min) / float(max - min);
      }

      err = cd::get_dB[ctl_dir](elem, channel, &value);
      if (err < 0) return 0;

      if (use_linear_dB_scale(min, max)) return float(value - min) / float(max - min);

      normalized = std::pow(10.f, float(value - max) / 6000.f);
      if (min != SND_CTL_TLV_DB_GAIN_MUTE) {
        min_norm = std::pow(10.f, float(min - max) / 6000.f);
        normalized = (normalized - min_norm) / (1 - min_norm);
      }

      return normalized;
    }

    int set_normalized_volume(snd_mixer_elem_t* elem,
                              snd_mixer_selem_channel_id_t channel,
                              float volume,
                              int dir,
                              ControlDirection ctl_dir)
    {
      long min = 0;
      long max = 0;
      long value = 0;
      float min_norm = 0;
      int err = 0;

      err = cd::get_dB_range[ctl_dir](elem, &min, &max);
      if (err < 0 || min >= max) {
        err = cd::get_raw_range[ctl_dir](elem, &min, &max);
        if (err < 0) return err;

        value = lrint_dir(volume * float(max - min), dir) + min;
        return cd::set_raw[ctl_dir](elem, channel, value);
      }

      if (use_linear_dB_scale(min, max)) {
        value = lrint_dir(volume * float(max - min), dir) + min;
        return cd::set_dB[ctl_dir](elem, channel, value, dir);
      }

      if (min != SND_CTL_TLV_DB_GAIN_MUTE) {
        min_norm = std::pow(10.f, float(min - max) / 6000.f);
        volume = volume * (1 - min_norm) + min_norm;
      }
      value = lrint_dir(6000.f * std::log10(volume), dir) + max;
      return cd::set_dB[ctl_dir](elem, channel, value, dir);
    }
  } // namespace volume_mapping

  std::string channel_name(Channel c) noexcept
  {
    return ::snd_mixer_selem_channel_name(c);
  }

  // Mixer //////////////////////

  Mixer::Mixer(const std::string& card)
  {
    int mode = 0;
    detail::check_err(snd_mixer_open(&handle_, mode));
    detail::check_err(snd_mixer_attach(handle_, card.c_str()));
    detail::check_err(snd_mixer_selem_register(handle_, nullptr, nullptr));
    detail::check_err(snd_mixer_load(handle_));
  }
  Mixer::~Mixer() noexcept
  {
    snd_mixer_close(handle_);
  }
  ::snd_mixer_t* Mixer::native_handle() const
  {
    return handle_;
  }

  Elem Mixer::find_elem(util::string_ref name) const
  {
    ::snd_mixer_selem_id_t* id = nullptr;
    snd_mixer_selem_id_alloca(&id); // NOLINT
    snd_mixer_selem_id_set_index(id, 0);
    snd_mixer_selem_id_set_name(id, name.c_str());
    ::snd_mixer_elem_t* res = snd_mixer_find_selem(native_handle(), id);
    if (res == nullptr) throw exception("No mixer element found with name '{}'", name);
    return Elem(res);
  }

  std::vector<Elem> get_elems(Mixer& m)
  {
    std::vector<Elem> res;
    ::snd_mixer_elem_t* elem = snd_mixer_first_elem(m.native_handle());
    while (elem != nullptr) {
      res.emplace_back(elem);
      elem = snd_mixer_elem_next(elem);
    }
    return res;
  }

  // Elem //////////////////////

  Elem::Elem(::snd_mixer_elem_t* h) : handle_(h) {}
  ::snd_mixer_elem_t* Elem::native_handle() const
  {
    return handle_;
  }
  util::string_ref Elem::get_name() const
  {
    return snd_mixer_selem_get_name(handle_);
  }
  bool Elem::has_common_switch() const
  {
    return snd_mixer_selem_has_common_switch(handle_) == 1;
  }
  bool Elem::has_common_volume() const
  {
    return snd_mixer_selem_has_common_volume(handle_) == 1;
  }
  bool Elem::has_volume(ControlDirection dir) const
  {
    return cd::has_volume[dir](handle_) == 1;
  }
  bool Elem::has_switch(ControlDirection dir) const
  {
    return cd::has_switch[dir](handle_) == 1;
  }
  bool Elem::has_channel(ControlDirection dir, Channel c) const
  {
    return cd::has_channel[dir](handle_, c) == 1;
  }
  bool Elem::is_enumerated() const
  {
    return snd_mixer_selem_is_enumerated(handle_) == 1;
  }
  Channel Elem::find_channel(ControlDirection dir) const
  {
    for (auto c : all_channels) {
      if (has_channel(dir, c)) return c;
    }
    return SND_MIXER_SCHN_UNKNOWN;
  }
  Channel Elem::find_channel() const
  {
    for (auto c : all_channels) {
      for (auto dir : util::enum_values<ControlDirection>()) {
        if (has_channel(dir, c)) return c;
      }
    }
    return SND_MIXER_SCHN_UNKNOWN;
  }
  std::vector<std::string> Elem::enum_items() const
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

  // IControl //////////////////////

  const std::string& IControl::get_name() const
  {
    return name_;
  }
  const Elem& IControl::get_elem() const
  {
    return elem_;
  }
  Channel IControl::get_channel() const
  {
    return channel_;
  }
  ControlDirection IControl::get_direction() const
  {
    return dir_;
  }

  // Switch //////////////////////

  void Switch::set_value(bool b)
  {
    detail::check_err(cd::set_switch[dir_](elem_.native_handle(), channel_, static_cast<int>(b)));
  }
  bool Switch::get_value() const
  {
    int res = -1;
    detail::check_err(cd::get_switch[dir_](elem_.native_handle(), channel_, &res));
    return res == 1;
  }

  // Volume //////////////////////

  void Volume::set_value(float f)
  {
    detail::check_err(volume_mapping::set_normalized_volume(elem_.native_handle(), channel_, f, 0, dir_));
  }
  float Volume::get_value() const
  {
    return volume_mapping::get_normalized_volume(elem_.native_handle(), channel_, dir_);
  }

  // Enum Control //////////////////////

  EnumControl::EnumControl(Elem& e, Channel c)
    : Control(e, "Enum", ControlDirection::playback, c), enum_items_(e.enum_items())
  {}
  EnumControl::EnumControl(Elem& e) : EnumControl(e, e.find_channel()) {}
  void EnumControl::set_value(int i)
  {
    detail::check_err(::snd_mixer_selem_set_enum_item(elem_.native_handle(), channel_, i));
  }
  int EnumControl::get_value() const
  {
    unsigned int res = -1;
    detail::check_err(::snd_mixer_selem_get_enum_item(elem_.native_handle(), channel_, &res));
    return static_cast<int>(res);
  }
  const std::vector<std::string>& EnumControl::enum_items() const
  {
    return enum_items_;
  }
  std::string EnumControl::value_str() const
  {
    return enum_items_.at(get_value());
  }
  int EnumControl::index_of(std::string_view str)
  {
    auto found = std::ranges::find(enum_items_, str);
    if (found == enum_items_.end()) throw std::out_of_range("alsamixer: No enum value given name");
    return static_cast<int>(found - enum_items_.begin());
  }

  // SwitchAll ////////////////////////

  void SwitchAll::set_value(bool b)
  {
    detail::check_err(cd::set_switch_all[dir_](elem_.native_handle(), static_cast<int>(b)));
  }

  // VolumeAll ////////////////////////

  void VolumeAll::set_value(float f)
  {
    for (Channel c : all_channels) {
      if (elem_.has_channel(dir_, c)) {
        volume_mapping::set_normalized_volume(elem_.native_handle(), c, f, 0, dir_);
      }
    }
  }

  // find_controls /////////////////////

  std::vector<std::unique_ptr<IControl>> get_controls(Elem& elem, std::vector<std::unique_ptr<IControl>>&& vec)
  {
    if (elem.has_common_switch() || elem.has_switch(ControlDirection::playback)) {
      for (auto c : all_channels) {
        if (elem.has_channel(ControlDirection::playback, c)) {
          vec.emplace_back(std::make_unique<Switch>(elem, ControlDirection::playback, c));
        }
      }
    }
    if (!elem.has_common_switch() && elem.has_switch(ControlDirection::capture)) {
      for (auto c : all_channels) {
        if (elem.has_channel(ControlDirection::capture, c)) {
          vec.emplace_back(std::make_unique<Switch>(elem, ControlDirection::capture, c));
        }
      }
    }
    if (elem.has_common_volume() || elem.has_volume(ControlDirection::playback)) {
      for (auto c : all_channels) {
        if (elem.has_channel(ControlDirection::playback, c)) {
          vec.emplace_back(std::make_unique<Volume>(elem, ControlDirection::playback, c));
        }
      }
    }
    if (!elem.has_common_volume() && elem.has_volume(ControlDirection::capture)) {
      for (auto c : all_channels) {
        if (elem.has_channel(ControlDirection::capture, c)) {
          vec.emplace_back(std::make_unique<Volume>(elem, ControlDirection::capture, c));
        }
      }
    }
    if (elem.is_enumerated()) {
      for (auto c : all_channels) {
        if (elem.has_channel(ControlDirection::playback, c) || elem.has_channel(ControlDirection::capture, c)) {
          vec.emplace_back(std::make_unique<EnumControl>(elem, c));
        }
      }
    }
    return std::move(vec);
  }
  std::vector<std::unique_ptr<IControl>> get_controls_all_channels(Elem& elem,
                                                                   std::vector<std::unique_ptr<IControl>>&& vec)
  {
    if (elem.has_common_switch() || elem.has_switch(ControlDirection::playback)) {
      vec.emplace_back(std::make_unique<SwitchAll>(elem, ControlDirection::playback));
    }
    if (!elem.has_common_switch() && elem.has_switch(ControlDirection::capture)) {
      vec.emplace_back(std::make_unique<SwitchAll>(elem, ControlDirection::capture));
    }
    if (elem.has_common_volume() || elem.has_volume(ControlDirection::playback)) {
      vec.emplace_back(std::make_unique<VolumeAll>(elem, ControlDirection::playback));
    }
    if (!elem.has_common_volume() && elem.has_volume(ControlDirection::capture)) {
      vec.emplace_back(std::make_unique<VolumeAll>(elem, ControlDirection::capture));
    }
    if (elem.is_enumerated()) {
      for (auto c : all_channels) {
        if (elem.has_channel(ControlDirection::playback, c) || elem.has_channel(ControlDirection::capture, c)) {
          vec.emplace_back(std::make_unique<EnumControl>(elem, c));
        }
      }
    }
    return std::move(vec);
  }
} // namespace otto::alsa
