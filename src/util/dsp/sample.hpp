#pragma once

#include <gsl/span>

#include "util/iterator.hpp"

namespace otto::dsp {

  /// Storage and playback of a sample
  struct Sample {
    struct iterator;

    explicit Sample(gsl::span<float> audio_data);
    Sample() = default;

    int size() const noexcept;

    iterator begin() const;

    iterator end() const;

    int start_point() const;
    int end_point() const;
    int loop_start() const;
    int loop_end() const;
    int fade_in_time() const;
    int fade_out_time() const;
    float playback_speed() const;

    int start_point(int val);
    int end_point(int val);
    int loop_start(int val);
    int loop_end(int val);
    int fade_in_time(int val);
    int fade_out_time(int val);
    float playback_speed(float val);

    struct iterator : util::iterator_facade<iterator, float, std::forward_iterator_tag, float> {
      using vector_iterator = std::vector<float>::const_iterator;

      iterator(const Sample& sample, int index, float stride = 1.f);
      iterator(const iterator&);
      iterator& operator=(const iterator&);

      void advance(std::ptrdiff_t d);
      float dereference() const;
      bool equal(const iterator& rhs) const;

      int index() const;

      const Sample& sample;
      bool do_loop = false;

    private:
      int start_point() const;
      int end_point() const;
      int loop_start() const;
      int loop_end() const;
      int signed_index() const;
      int fade_in_time() const;
      int fade_out_time() const;

      int _index = 0;
      float _playback_speed = 1.f;
      float _error = 0.f;
    };

    bool cut = false;
    bool loop = false;

  private:
    gsl::span<float> _audio_data;

    friend struct iterator;

    int _start_point = 0;
    int _end_point = 0;
    int _loop_start = -1;
    int _loop_end = -1;
    int _fade_in_time = 0;
    int _fade_out_time = 0;
    float _playback_speed = 1.f;

    /// The normal speed. When reading a sample from a file, this is the AudioManager's
    /// samplerate divided by the sample's
    float speed_modifier = 1.f;
  };


} // namespace otto::dsp
