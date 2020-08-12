#include "app/services/impl/controller.hpp"
#include "app/services/config.hpp"

#include "lib/util/i2c.hpp"

namespace otto::services {

  template<int Rows, int Cols>
  using KeyMatrix = std::array<std::array<tl::optional<Key>, Cols>, Rows>;
  using LedSequence = util::enum_map<Key, std::uint8_t>;

  struct Betav01HWMap final : HardwareMap {
    static constexpr auto n_rows = 8;
    static constexpr auto n_cols = 7;

    int row_count() const noexcept override
    {
      return n_rows;
    }
    int col_count() const noexcept override
    {
      return n_cols;
    }

    tl::optional<Key> key_at(std::uint8_t row, std::uint8_t col) const noexcept override
    {
      if (row >= n_rows || col >= n_cols) return tl::nullopt;
      return key_codes[row][col];
    }
    std::uint8_t led_for(Key k) const noexcept override
    {
      return led_map[k];
    }

    static constexpr KeyMatrix<n_rows, n_cols> key_codes = {{
      {Key::channel0, Key::channel3, Key::channel7, Key::shift, Key::sends, tl::nullopt, Key::blue_enc_click},
      {Key::seq1, Key::seq6, Key::seq11, Key::plus, Key::routing, Key::rec, Key::yellow_enc_click},
      {Key::seq2, Key::seq7, Key::seq12, Key::minus, Key::fx2, Key::master, tl::nullopt},
      {Key::channel1, Key::channel4, Key::channel8, Key::seq0, Key::fx1, Key::play, Key::red_enc_click},
      {Key::seq3, Key::seq8, Key::seq13, Key::seq15, Key::arp, Key::slots, tl::nullopt},
      {Key::seq4, Key::seq9, Key::seq14, Key::twist2, Key::looper, Key::twist1, tl::nullopt},
      {Key::channel2, Key::channel5, Key::channel9, Key::external, Key::sampler, Key::envelope, Key::green_enc_click},
      {Key::seq5, Key::channel6, Key::seq10, Key::settings, Key::sequencer, Key::synth, tl::nullopt},
    }};

    static constexpr LedSequence led_map = {{
      {Key::channel0, 0},
      {Key::channel3, 3},
      {Key::channel7, 7},
      {Key::shift, 2},
      {Key::sends, 3},
      {Key::blue_enc_click, 25},
      {Key::seq1, 1},
      {Key::seq6, 6},
      {Key::seq11, 11},
      {Key::plus, 1},
      {Key::routing, 10},
      {Key::rec, 11},
      {Key::yellow_enc_click, 25},
      {Key::seq2, 2},
      {Key::seq7, 7},
      {Key::seq12, 12},
      {Key::minus, 0},
      {Key::fx2, 9},
      {Key::master, 13},
      {Key::channel1, 1},
      {Key::channel4, 4},
      {Key::channel8, 8},
      {Key::seq0, 0},
      {Key::fx1, 4},
      {Key::play, 12},
      {Key::red_enc_click, 25},
      {Key::seq3, 3},
      {Key::seq8, 8},
      {Key::seq13, 13},
      {Key::seq15, 15},
      {Key::arp, 8},
      {Key::slots, 14},
      {Key::seq4, 4},
      {Key::seq9, 9},
      {Key::seq14, 14},
      {Key::twist2, 16},
      {Key::looper, 5},
      {Key::twist1, 15},
      {Key::channel2, 2},
      {Key::channel5, 5},
      {Key::channel9, 9},
      {Key::external, 17},
      {Key::sampler, 7},
      {Key::envelope, 18},
      {Key::green_enc_click, 25},
      {Key::seq5, 5},
      {Key::channel6, 6},
      {Key::seq10, 10},
      {Key::settings, 20},
      {Key::sequencer, 6},
      {Key::synth, 19},
    }};
  };

} // namespace otto::services

namespace otto::board {
  struct I2CMCUPort final : services::MCUPort {
    struct Config : otto::Config<Config> {
      std::uint16_t address = 0x77;
      std::filesystem::path device_path = "/dev/i2c-1";
    };

    I2CMCUPort() : I2CMCUPort(core::ServiceAccessor<services::ConfigManager>()->register_config<Config>()) {}

    I2CMCUPort(const Config& conf) : i2c(conf.address)
    {
      auto ec = i2c.open(conf.device_path);
      if (ec) throw std::system_error(ec);
    }

    std::size_t write(std::span<std::uint8_t> data) override
    {
      auto ec = i2c.write(data);
      if (ec) throw std::system_error(ec);
      return data.size();
    }

    std::span<std::uint8_t> read(std::size_t count) override
    {
      data.resize(count);
      auto ec = i2c.read_into(data);
      if (ec) throw std::system_error(ec);
      return data;
    }

    util::I2C i2c;
    std::vector<std::uint8_t> data;
  };

  core::ServiceHandle<services::Controller> make_controller()
  {
    return core::make_handle<services::MCUController>(std::make_unique<I2CMCUPort>(),
                                                      std::make_unique<services::Betav01HWMap>());
  }
} // namespace otto::board

// kak: other_file=../include/board/controller.hpp
