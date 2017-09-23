#include "tapebuffer.hpp"

#include <thread>
#include <mutex>
#include <condition_variable>
#include "util/tapefile.hpp"
#include "core/globals.hpp"
#include <plog/Log.h>

namespace top1 {

  using value_type = tape_buffer::value_type;
  constexpr std::size_t buffer_size = tape_buffer::buffer_size;

  constexpr std::size_t wrap(std::size_t position)
  {
    return position % buffer_size;
  }

  struct Producer {

    /// The desired distance from the playpoint to the head, and vice versa for
    /// the tail
    const std::size_t goal_length = tape_buffer::buffer_size / 2 - 2;

    /// The minimum number of samples to read from file
    const std::size_t min_read_size = 2048;
    const std::size_t min_write_size = 2048;

    const fs::path path = Globals::data_dir / "tape.wav";
    TapeFile file;
    std::thread thread;
    tape_buffer& owner;
    std::mutex mutex;
    std::condition_variable waiting;

    Producer(tape_buffer& owner)
      : owner {owner},
        thread {&Producer::main_routine, this}
    {}

    ~Producer()
    {
      waiting.notify_all();
      thread.join();
    }

    void main_routine()
    {
      file.open(path);

      while (Globals::running()) {
        std::unique_lock lock {mutex};

        std::size_t index = owner.current_position;

        fill_buffer(index);

        waiting.wait(lock);
      }
    }

    /// Write everything between `owner.write_head` and `owner.write_tail`
    void write_from_buffer()
    {
      // auto [head, tail] = owner.write_sect.load();
      // if (auto size = head - tail; size > min_write_size)
      // {
      //   write_wrapped(tail, size);
      //   // TODO: Mark section as written
      // }
    }

    /// Fill the buffer as needed, assuming `index` is the current position.
    /// This is the only function that can modify `owner.head` & `owner.tail`!
    void fill_buffer(std::size_t index)
    {
      if (auto diff = goal_length - (owner.head - index);
          diff > min_read_size)
      {
        read_wrapped(owner.head, diff);
        owner.head += diff;
        if (auto dst = owner.head - owner.tail; dst > buffer_size) {
          // Get rid of overlap
          owner.tail += dst - buffer_size + 2;
        }
      }
      if (auto diff = goal_length - (index - owner.tail);
          diff > min_read_size)
      {
        read_wrapped(owner.tail - diff, diff);
        owner.tail -= diff;
        if (auto dst = owner.head - owner.tail; dst > buffer_size) {
          // Get rid of overlap
          owner.head -= dst - buffer_size + 2;
        }
      }
    }

    /// Read `n` samples to `position`, splitting the operation into two reads if
    /// wrapping is necessary
    void read_wrapped(std::size_t position, std::size_t n)
    {
      // We dont have to worry about thread safety in here, everything is thread local
      std::size_t wrap_pos = wrap(position);
      std::size_t overflow = std::max(std::size_t(0), wrap_pos + n - buffer_size);
      file.seek(4 * position);
      file.read_samples((float*) (owner.buffer.data() + wrap_pos), 4 * (n - overflow));
      if (overflow > 0) {
        file.read_samples((float*) owner.buffer.data(), 4 * overflow);
      }
    }

    /// Write `n` samples to `position`, splitting the operation into two writes if
    /// wrapping is necessary
    void write_wrapped(std::size_t position, std::size_t n)
    {
      // We dont have to worry about thread safety in here, everything is thread local
      std::size_t wrap_pos = wrap(position);
      std::size_t overflow = std::max(std::size_t(0), wrap_pos + n - buffer_size);
      file.seek(4 * position);
      file.write_samples((float*) (owner.buffer.data() + wrap_pos), 4 * (n - overflow));
      if (overflow > 0) {
        file.write_samples((float*) owner.buffer.data(), 4 * overflow);
      }
    }
  };

  void tape_buffer::advance(int n)
  {
    current_position = std::clamp((int) current_position + n, 0, (int) max_length);
    producer->waiting.notify_all();
  }

  void tape_buffer::advance_const(int n)
  {
    current_position = std::clamp((int) current_position + n, 0, (int) max_length);
    producer->waiting.notify_all();
  }

  value_type& tape_buffer::cur_value()
  {
    return buffer[wrap(current_position)];
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

}
