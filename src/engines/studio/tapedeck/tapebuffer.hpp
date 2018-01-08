#pragma once

#include <array>
#include <cmath>
#include <atomic>
#include <memory>
#include <set>

#include "util/iterator.hpp"
#include "util/algorithm.hpp"
#include "util/math.hpp"
#include "util/audio.hpp"
#include "util/ringbuffer.hpp"

#include "services/debug_ui.hpp"

namespace otto::engines {

  // FDCL - Defined in tapebuffer.cpp
  struct Producer;


  /// The buffer used for the tapedeck
  ///
  /// Provides reading from file, variable speed reading/writing in both
  /// directions and access to tape metadata, such as slices.
  class tape_buffer {
    using Value = std::array<float, 4>;
  public:

    using TapeSlice = util::audio::Section<int>;

    struct TapeSliceSet {
      std::vector<TapeSlice> slices;

      TapeSliceSet() {}

      std::vector<TapeSlice> overlapping_slices(util::audio::Section<int> area) const;

      bool in_slice(int time) const;
      TapeSlice current(int time) const;

      void add(TapeSlice slice);
      void erase(TapeSlice slice);

      void cut(int time);
      void glue(TapeSlice s1, TapeSlice s2);

      // Iteration
      decltype(auto) begin() { return slices.begin(); }
      decltype(auto) end() { return slices.end(); }
      decltype(auto) begin() const { return slices.begin(); }
      decltype(auto) end() const { return slices.end(); }
      decltype(auto) size() const { return slices.size(); }
      decltype(auto) clear() { return slices.clear(); }
    };


    /* Constants */

    static constexpr std::size_t buffer_size = 1 << 18;
    static constexpr std::size_t max_length = 8 * 60 * 44100;

    using value_type = Value;
    /// Tape slices for each of the 4 tracks
    std::array<TapeSliceSet, 4> slices;

    /* Initialization */

    tape_buffer();
    ~tape_buffer();

    tape_buffer(tape_buffer&) = delete;
    tape_buffer(tape_buffer&&) = delete;

    /* Member functions */

    std::size_t position() const
    {
      return current_position;
    }

    /// Move the point `n` forward. `n` can be negative
    void advance(int n = 1);
    void notify_update();
    void invalidate();

    /// Get a refference to the value at point
    value_type& cur_value();

    /// Write `n` frames from `iter` at speed `speed`, throug `func`
    ///
    /// for each frame in the tape, `func` will be called with arguments
    /// `*iter, *tape`. It is expected that `func` modifies the `tape` argument.
    ///
    /// `iter` will be slowed down/sped up according to `speed`. If `speed` is
    /// positive, the frames will be written "behind" the cursor, as in, the
    /// last frame will be positioned at `cursor - 1`. If `speed` is negative,
    /// the first frame in the range will be positioned at `cursor + 1`.
    /// If `speed` is `0`, nothing will be written
    ///
    /// \returns the section of tape that was just written
    template<typename Iter, typename BinaryFunc>
    util::audio::Section<int> write_n(Iter iter, int n, float speed,
      BinaryFunc&& func = [] (auto&& in, auto& tape) { tape = in; })
    {
      util::audio::Section<int> written {0,0};
      int write_n = 0;
      float inpt_speed;
      if (speed > 0) {
        write_n = n * speed;
        written = {current_position - write_n, current_position};
        inpt_speed = 1.f / speed;
      } else if (speed < 0) {
        write_n = n * -speed;
        written = {current_position + 1, current_position + write_n + 1};
        inpt_speed = 1.f / -speed;
      } else {
        return written;
      }

      auto tape = buffer.iter(written.in);
      auto inpt = util::float_step(std::move(iter), inpt_speed);
      for (int i = 0; i < write_n; i++, tape++, inpt++) {
        func(*inpt, *tape);
      }

      // Atomically update `write_sect`
      util::audio::Section<int> new_sect;
      auto expected_sect = write_sect.load();
      do {
        new_sect = written;
        if (expected_sect.size() != 0) {
          new_sect += expected_sect;
        }
      } while (!write_sect.compare_exchange_weak(expected_sect, new_sect));
      notify_update();

      return written;
    }

    template<typename Iter>
    void read_n(int n, float speed, Iter dst)
    {
      auto src = util::float_step(buffer.citer(current_position), speed);
      std::copy_n(src, n, dst);
      advance(n * speed);

      dbg.record_read(n * speed);
    }

    template<typename Iter>
    std::size_t read_until(std::size_t pos, float speed, Iter dst,
      std::size_t max_n = std::numeric_limits<std::size_t>::max())
    {
      auto first = util::float_step(buffer.citer(current_position), speed);
      auto last = util::float_step(buffer.citer(pos), speed);
      auto iter = first;
      std::size_t i = 0;
      for (;iter < last && i < max_n; ++iter, ++i)
      {
        *dst = *iter;
      }
      advance(iter.difference(first));
      return i;
    }

    /// Jumps the tape to absolute position `p`
    ///
    /// Use sparingly - a jump clears the entire buffer
    void jump_to(std::size_t p);

    /* Member variables */

    using buffer_type = util::wrapping_array<value_type, buffer_size>;

    /// The current file position
    /// This variable should only be modified by the consumer - to everyone else
    /// it is read only!
    std::atomic_int current_position {0};

    // Beginning/end of loaded section. File position, *not* buffer index
    // These variables should only be modified by the producer
    std::atomic_int head {0};
    std::atomic_int tail {0};

    std::atomic<util::audio::Section<int>> write_sect;

    buffer_type buffer;

    // Defined in implementation file
    friend struct Producer;
    std::unique_ptr<Producer> producer;

    struct DbgInfo : service::debug_ui::Info {
      void record_read(float entry) {
#if OTTO_DEBUG_UI
        read_size_graph.push(entry);
#endif
      }

      void draw() override;

    private:
      service::debug_ui::graph<1 << 10> read_size_graph;
    } dbg;
  };
}
