#include "sample.hpp"

#include "util/assert.hpp"

namespace otto::dsp {

  Sample::Sample(gsl::span<float> audio_data) : _audio_data(audio_data), _end_point(_audio_data.size()) {}

  int Sample::size() const noexcept
  {
    return _end_point - _start_point;
  }

  Sample::iterator Sample::begin() const
  {
    float stride = _playback_speed * speed_modifier;
    if (stride < 0) {
      return {*this, end_point() - 1, stride * speed_modifier};
    }
    return {*this, start_point(), stride * speed_modifier};
  }

  Sample::iterator Sample::end() const
  {
    float stride = _playback_speed * speed_modifier;
    if (stride < 0) {
      return {*this, start_point() - 1, stride * speed_modifier};
    }
    return {*this, end_point(), stride * speed_modifier};
  }

  int Sample::start_point() const
  {
    return _start_point;
  }

  int Sample::end_point() const
  {
    return _end_point;
  }

  int Sample::loop_start() const
  {
    OTTO_ASSERT(false, "untested, implementation probably not correct");
    if (_loop_start < 0) return start_point();
    return _loop_start;
  }

  int Sample::loop_end() const
  {
    OTTO_ASSERT(false, "untested, implementation probably not correct");
    if (_loop_end < 0) return end_point();
    return _loop_end;
  }

  int Sample::fade_in_time() const
  {
    return _fade_in_time;
  }

  int Sample::fade_out_time() const
  {
    return _fade_out_time;
  }

  float Sample::playback_speed() const
  {
    return _playback_speed;
  }

  int Sample::start_point(int val)
  {
    _start_point = val;
    if (_end_point < val) end_point(val);
    return _start_point;
  }

  int Sample::end_point(int val)
  {
    val = std::clamp(val, 0, (int) _audio_data.size());
    _end_point = val;
    if (start_point() > val) start_point(val);
    return _end_point;
  }

  int Sample::loop_start(int val)
  {
    val = std::clamp(val, start_point(), loop_end() - 1);
    _loop_start = val;
    return _loop_start;
  }

  int Sample::loop_end(int val)
  {
    val = std::clamp(val, loop_start() + 1, end_point());
    _loop_end = val;
    return _loop_end;
  }

  int Sample::fade_in_time(int val)
  {
    _fade_in_time = val;
    return _fade_in_time;
  }

  int Sample::fade_out_time(int val)
  {
    _fade_out_time = val;
    return _fade_out_time;
  }

  float Sample::playback_speed(float val)
  {
    _playback_speed = val;
    return _playback_speed;
  }

  Sample::iterator::iterator(const Sample& sample, int index, float stride)
    : sample(sample), _index(index), _playback_speed(stride)
  {}

  Sample::iterator::iterator(const iterator& rhs) = default;

  Sample::iterator& Sample::iterator::operator=(const iterator& rhs)
  {
    OTTO_ASSERT(&this->sample == &rhs.sample);
    do_loop = rhs.do_loop;
    _index = rhs._index;
    _playback_speed = rhs._playback_speed;
    _error = rhs._error;
    return *this;
  }

  void Sample::iterator::advance(std::ptrdiff_t d)
  {
    float int_part;
    _error = std::modf(_error + _playback_speed * d, &int_part);
    if (_error < 0) {
      int_part -= 1;
      _error += 1;
    }
    for (int i = 0; i != std::abs(int_part); i++) {
      _index += int_part / std::abs(int_part);
      if (signed_index() == loop_end() && do_loop) {
        _index = std::abs(loop_start());
      }
    }
  }

  float Sample::iterator::dereference() const
  {
    if (start_point() == end_point() || signed_index() < start_point() || signed_index() >= end_point()) return 0.f;
    OTTO_ASSERT(_index >= 0 && _index < sample._audio_data.size());
    float res = sample._audio_data[_index];
    if (fade_in_time() > 0) {
      float fade_amnt = (signed_index() - start_point()) / float(fade_in_time());
      if (fade_amnt < 1) res *= fade_amnt;
    }
    if (fade_out_time() > 0) {
      float fade_amnt = (end_point() - signed_index()) / float(fade_out_time());
      if (fade_amnt < 1) res *= fade_amnt;
    }
    return res;
  }

  bool Sample::iterator::equal(const Sample::iterator& rhs) const
  {
    return _index == rhs._index && (signed_index() == end_point() || _error == rhs._error);
  }

  int Sample::iterator::index() const
  {
    return _index;
  }

  int Sample::iterator::start_point() const
  {
    if (_playback_speed < 0) return -(sample.end_point() - 1);
    return sample.start_point();
  }

  int Sample::iterator::end_point() const
  {
    if (_playback_speed < 0) return -(sample.start_point() - 1);
    return sample.end_point();
  }

  int Sample::iterator::loop_start() const
  {
    if (_playback_speed < 0) return -sample.loop_end();
    return sample.loop_start();
  }

  int Sample::iterator::loop_end() const
  {
    if (_playback_speed < 0) return -sample.loop_start();
    return sample.loop_end();
  }

  int Sample::iterator::signed_index() const
  {
    if (_playback_speed < 0) return -_index;
    return _index;
  }

  int Sample::iterator::fade_in_time() const
  {
    if (_playback_speed < 0) return sample.fade_out_time();
    return sample.fade_in_time();
  }

  int Sample::iterator::fade_out_time() const
  {
    if (_playback_speed < 0) return sample.fade_in_time();
    return sample.fade_out_time();
  }


}
