#include "tapebuffer.hpp"

#include <thread>
#include <mutex>
#include <condition_variable>

#include "util/tapefile.hpp"
#include "util/timer.hpp"
#include "core/globals.hpp"
#include "services/logger.hpp"

namespace otto {

  using value_type = tape_buffer::value_type;
  constexpr int buffer_size = tape_buffer::buffer_size;

  constexpr int wrap(std::size_t position)
  {
    return position % buffer_size;
  }

  /// Handles all interactions with the tapefile. Works on its own thread
  struct Producer {

    /// The desired distance from the playpoint to the head, and vice versa for
    /// the tail
    const int goal_length = tape_buffer::buffer_size / 2 - 2;

    /// The minimum number of samples to read from file
    const int min_read_size = tape_buffer::buffer_size >> 8;
    const int min_write_size = tape_buffer::buffer_size >> 8;

    const fs::path path = global::data_dir / "tape.wav";
    util::TapeFile file;
    std::thread thread;
    tape_buffer& owner;
    std::mutex global_lock;
    std::condition_variable waiting;
    std::atomic_bool keepRunning {true};

    Producer(tape_buffer& owner)
      : thread {&Producer::main_routine, this},
	owner {owner}
    {}

    ~Producer()
    {
      keepRunning = false;
      {
        std::unique_lock lock {global_lock};
        waiting.notify_all();
      }
      thread.join();
    }

    void main_routine()
    {
      services::logger::set_thread_name("Tape Buffer");
      file.open(path);
      read_slices();

      while (keepRunning) {
        std::unique_lock lock {global_lock};
        {
          TIME_SCOPE("TapeBuffer read cycle");
          std::size_t index = owner.current_position;

          write_from_buffer();
          fill_buffer(index);
        }
        waiting.wait(lock);
      }

      // Make sure everything is written
      write_from_buffer<true>();
      write_slices();

      file.close();
    }

    /// Write everything in `owner.write_sect`
    template<bool unconditionally = false>
    void write_from_buffer()
    {
      auto write_sect = owner.write_sect.load();
      if (unconditionally
        || write_sect.size() > min_write_size
        || (write_sect.in - owner.tail)  <= min_read_size * 2
        || (owner.head - write_sect.out) <= min_read_size * 2)
      {
        write_wrapped(write_sect.in, write_sect.size());

        // Atomically update `write_sect`
        util::audio::Section<int> new_sect;
        auto expected_sect = owner.write_sect.load();
        do {
          new_sect = expected_sect - write_sect;
        } while (!owner.write_sect.compare_exchange_weak(
            expected_sect, new_sect));
      }
    }

    /// Fill the buffer as needed, assuming `index` is the current position.
    /// This is the only function that can modify `owner.head` & `owner.tail`!
    void fill_buffer(int index)
    {
      if (auto diff = goal_length - (owner.head - index);
        diff > min_read_size)
      {
        read_wrapped(owner.head, diff);
        owner.head = std::clamp(owner.head + diff, 0, (int) tape_buffer::max_length);
        if (auto dst = owner.head - owner.tail; dst > buffer_size) {
          // Get rid of overlap
          owner.tail += std::max(0, dst - buffer_size + 2);
        }
      }
      if (auto diff = goal_length - (index - owner.tail);
        diff > min_read_size)
      {
        int read_pos = std::clamp(owner.tail - diff, 0, (int) tape_buffer::max_length);
        read_wrapped(read_pos, diff);
        owner.tail = read_pos;
        if (auto dst = owner.head - owner.tail; dst > buffer_size) {
          // Get rid of overlap
          owner.head -= std::max(0, dst - buffer_size + 2);
        }
      }
    }

    /// Read `n` samples to `position`, splitting the operation into two reads if
    /// wrapping is necessary
    ///
    /// This could have been done just using the wrapping array iterators, but
    /// performance tests (see `test/util/bytefile.t.cpp`) say the pointer
    /// optimization is around 50 times faster
    void read_wrapped(int position, int n)
    {
      // We dont have to worry about thread safety in here, everything is thread local
      int wrap_pos = wrap(position);
      int overflow = std::max(0, wrap_pos + n - buffer_size);
      file.seek(4 * position);
      file.read_samples((owner.buffer.data() + wrap_pos)->data(), 4 * (n - overflow));
      if (overflow > 0) {
        file.read_samples(owner.buffer.data()->data(), 4 * overflow);
      }
    }

    /// Write `n` samples to `position`, splitting the operation into two writes if
    /// wrapping is necessary
    ///
    /// This could have been done just using the wrapping array iterators, but
    /// performance tests (see `test/util/bytefile.t.cpp`) say the pointer
    /// optimization is around 50 times faster
    void write_wrapped(int position, int n)
    {
      // We dont have to worry about thread safety in here, everything is thread local
      int wrap_pos = wrap(position);
      int overflow = std::max(0, wrap_pos + n - buffer_size);
      file.seek(4 * position);
      file.write_samples((owner.buffer.data() + wrap_pos)->data(), 4 * (n - overflow));
      if (overflow > 0) {
        file.write_samples(owner.buffer.data()->data(), 4 * overflow);
      }
    }

    void read_slices()
    {
      for (int track = 0; track < 4; track++) {
        auto& file_slices = file.slices[track];
        auto& owner_slices = owner.slices[track];
        auto n = file_slices.count;

        owner_slices.clear();
        std::transform(std::begin(file_slices.array), std::begin(file_slices.array) + n,
          std::back_inserter(owner_slices.slices), [] (auto&& slice) {
            return util::audio::Section<int>{
              gsl::narrow_cast<int>(slice.in),
              gsl::narrow_cast<int>(slice.out)};
          });
      }
    }

    void write_slices()
    {
      for (int track = 0; track < 4; track++) {
        auto& file_slices = file.slices[track];
        auto& owner_slices = owner.slices[track];
        auto n = std::min(file_slices.array.size(), owner_slices.size());
        file_slices.count = n;

        std::transform(
          std::begin(owner_slices),
          std::begin(owner_slices) + n,
          std::begin(file_slices.array),
          [] (auto&& slice) {
            return util::TapeFile::SliceData{
              gsl::narrow_cast<std::uint32_t>(slice.in),
              gsl::narrow_cast<std::uint32_t>(slice.out)};
          });
      }
    }
  };

  void tape_buffer::advance(int n)
  {
    current_position = std::clamp(current_position + n, 0, (int) max_length);
    notify_update();
  }

  void tape_buffer::notify_update()
  {
    producer->waiting.notify_all();
  }

  void tape_buffer::invalidate()
  {
    tail.exchange(current_position);
    head.exchange(current_position);
    notify_update();
  }

  value_type& tape_buffer::cur_value()
  {
    return buffer[current_position];
  }

  void tape_buffer::jump_to(std::size_t position)
  {
    current_position = position;
    producer->waiting.notify_all();
  }

  tape_buffer::tape_buffer()
    : producer {std::make_unique<Producer>(*this)}
  {}

  tape_buffer::~tape_buffer() {}

  /* Debug Info */

  void tape_buffer::DbgInfo::draw()
  {
    ImGui::Begin("Tape buffer");
    read_size_graph.plot("Read size");
    ImGui::End();
  }

  /*
   * TapeSliceSet
   */

  std::vector<tape_buffer::TapeSlice>
  tape_buffer::TapeSliceSet::overlapping_slices(TapeSlice area) const {
    std::vector<TapeSlice> xs;
    std::copy_if(std::begin(slices), std::end(slices), std::back_inserter(xs),
      [&] (auto&& slice) {
        return slice.overlaps(area);
      });
    return xs;
  }

  bool tape_buffer::TapeSliceSet::in_slice(int time) const {
    return std::any_of(std::begin(slices), std::end(slices),
      [time] (auto&& slice) { return slice.contains(time); });
  }

  tape_buffer::TapeSlice tape_buffer::TapeSliceSet::current(int time) const {
    for (auto&& slice : slices) {
      if (slice.contains(time)) return slice;
    }
    return {-1, -1};
  }

  void tape_buffer::TapeSliceSet::erase(TapeSlice slice) {
    for (auto&& sl : slices) {
      // TODO: Split if sl contains slice
      sl -= slice;
    }
    std::remove_if(std::begin(slices), std::end(slices),
      [] (auto&& in) { return in.size() == 0; });
  }

  void tape_buffer::TapeSliceSet::add(TapeSlice slice) {
    erase(slice);
    slices.push_back(slice);
  }

  void tape_buffer::TapeSliceSet::cut(int time) {
    if (!in_slice(time)) return;
    TapeSlice slice = current(time);
    add({slice.in, time});
    add({time + 1, slice.out});
  }

  void tape_buffer::TapeSliceSet::glue(TapeSlice s1, TapeSlice s2) {
    add({std::min(s1.in, s2.in), std::max(s1.out, s2.out)});
  }

}
