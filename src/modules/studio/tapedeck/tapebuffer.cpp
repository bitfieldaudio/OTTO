#include "tapebuffer.hpp"

#include <thread>
#include <mutex>
#include <condition_variable>
#include "util/tapefile.hpp"
#include "core/globals.hpp"
#include <plog/Log.h>

namespace top1 {

  using value_type = tape_buffer::value_type;
  constexpr int buffer_size = tape_buffer::buffer_size;

  constexpr int wrap(std::size_t position)
  {
    return position % buffer_size;
  }

  struct Producer {

    /// The desired distance from the playpoint to the head, and vice versa for
    /// the tail
    const int goal_length = tape_buffer::buffer_size / 2 - 2;

    /// The minimum number of samples to read from file
    const int min_read_size = tape_buffer::buffer_size >> 8;
    const int min_write_size = tape_buffer::buffer_size >> 8;

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

        write_from_buffer();
        fill_buffer(index);

        waiting.wait(lock);
      }

      file.close();
    }

    /// Write everything between `owner.write_head` and `owner.write_tail`
    void write_from_buffer()
    {
      auto write_sect = owner.write_sect.load();
      if (write_sect.size() > min_write_size
        || (write_sect.in - owner.tail)  <= min_read_size * 2
        || (owner.head - write_sect.out) <= min_read_size * 2)
      {
        // file.write_samples(std::begin(owner.buffer) + write_sect.in,
        //   4 * write_sect.size());

        // Atomically update `write_sect`
        audio::Section<int> new_sect;
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
        file.seek(owner.head * 4);
        // file.read_samples(std::begin(owner.buffer) + owner.head, 4 * diff);
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
        // file.read_samples(std::begin(owner.buffer) + read_pos, 4 * diff);
        owner.tail = read_pos;
        if (auto dst = owner.head - owner.tail; dst > buffer_size) {
          // Get rid of overlap
          owner.tail -= std::max(0, dst - buffer_size + 2);
        }
      }
    }
  };

  void tape_buffer::advance(int n)
  {
    current_position = std::clamp((int) current_position + n, 0, (int) max_length);
    producer->waiting.notify_all();
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

}
