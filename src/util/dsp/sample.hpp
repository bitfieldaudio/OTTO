#pragma once

#include <vector>
#include <gsl/span>

#include "util/iterator.hpp"
#include "util/reflection.hpp"

namespace otto::dsp {

  /// Storage and playback of a sample
  struct Sample {
    struct iterator;

    explicit Sample(gsl::span<float> audio_data) noexcept;
    Sample() = default;

    int size() const noexcept;

    iterator begin() const noexcept;
    iterator end() const noexcept;

    int start_point() const noexcept;
    int end_point() const noexcept;
    int loop_start() const noexcept;
    int loop_end() const noexcept;
    int fade_in_time() const noexcept;
    int fade_out_time() const noexcept;
    float playback_speed() const noexcept;

    int start_point(int val) noexcept;
    int end_point(int val) noexcept;
    int loop_start(int val) noexcept;
    int loop_end(int val) noexcept;
    int fade_in_time(int val) noexcept;
    int fade_out_time(int val) noexcept;
    float playback_speed(float val) noexcept;

    struct iterator : util::iterator_facade<iterator, float, std::forward_iterator_tag, float> {
      using vector_iterator = std::vector<float>::const_iterator;

      iterator() noexcept = default;
      iterator(const Sample& sample, int index, float stride = 1.f) noexcept;
      iterator(const iterator&) noexcept;
      iterator& operator=(const iterator&) noexcept;

      void advance(std::ptrdiff_t d) noexcept;
      float dereference() const noexcept;
      bool equal(const iterator& rhs) const noexcept;

      int index() const noexcept;

      bool do_loop = false;

    private:
      int start_point() const noexcept;
      int end_point() const noexcept;
      int loop_start() const noexcept;
      int loop_end() const noexcept;
      int signed_index() const noexcept;
      int fade_in_time() const noexcept;
      int fade_out_time() const noexcept;

      const Sample* sample_ = nullptr;

      int index_ = 0;
      float playback_speed_ = 1.f;
      float error_ = 0.f;
    };

    bool cut = false;
    bool loop = false;

    DECL_REFLECTION(Sample,
                    ("start_point", &Sample::start_point, &Sample::start_point),
                    ("end_point", &Sample::end_point, &Sample::end_point),
                    // ("loop_start", &Sample::loop_start, &Sample::loop_start),
                    // ("loop_end", &Sample::loop_end, &Sample::loop_end),
                    ("fade_in_time", &Sample::fade_in_time, &Sample::fade_in_time),
                    ("fade_out_time", &Sample::fade_out_time, &Sample::fade_out_time),
                    ("playback_speed", &Sample::playback_speed, &Sample::playback_speed))
  private:
    gsl::span<float> audio_data_;

    friend struct iterator;

    int start_point_ = 0;
    int end_point_ = 0;
    int loop_start_ = -1;
    int loop_end_ = -1;
    int fade_in_time_ = 0;
    int fade_out_time_ = 0;
    float playback_speed_ = 1.f;

    /// The normal speed. When reading a sample from a file, this is the AudioManager's
    /// samplerate divided by the sample's
    float speed_modifier = 1.f;
  };


} // namespace otto::dsp
