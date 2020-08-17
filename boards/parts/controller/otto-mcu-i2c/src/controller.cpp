#include "app/services/impl/controller.hpp"
#include "app/services/config.hpp"

#include "lib/util/i2c.hpp"

namespace otto::services {

  template<int Rows, int Cols>
  using KeyMatrix = std::array<std::array<tl::optional<Key>, Cols>, Rows>;
  using LedSequence = util::enum_map<Key, std::uint8_t>;

  struct Betav01HWMap final : HardwareMap {
    static constexpr auto n_rows = 8;
    static constexpr auto n_cols = 8;

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
      {Key::seq0, Key::channel2, Key::channel5, Key::channel8, Key::twist1, Key::sampler, Key::blue_enc_click,
       Key::synth},
      {Key::channel0, Key::channel3, Key::channel6, Key::channel9, Key::fx2, Key::sends, Key::yellow_enc_click,
       Key::fx1},
      {Key::channel1, Key::channel4, Key::channel7, Key::seq15, Key::slots, Key::unassigned_b, tl::nullopt,
       Key::envelope},
      {Key::seq1, Key::seq6, Key::seq11, Key::unassigned_c, Key::plus, Key::routing, Key::red_enc_click, Key::voices},
      {Key::seq2, Key::seq7, Key::seq12, Key::unassigned_d, Key::twist2, Key::looper, tl::nullopt, tl::nullopt},
      {Key::seq3, Key::seq8, Key::seq13, Key::unassigned_f, Key::record, Key::sequencer, tl::nullopt, Key::arp},
      {Key::seq4, Key::seq9, Key::seq14, Key::unassigned_e, Key::minus, Key::unassigned_a, Key::green_enc_click,
       Key::settings},
      {Key::seq5, Key::seq10, tl::nullopt, Key::shift, Key::plus, Key::external, tl::nullopt},
    }};

    static constexpr LedSequence led_map = {{
      {Key::channel0, 16},
      {Key::channel1, 17},
      {Key::channel2, 18},
      {Key::channel3, 19},
      {Key::channel4, 20},
      {Key::channel5, 21},
      {Key::channel6, 22},
      {Key::channel7, 23},
      {Key::channel8, 24},
      {Key::channel9, 25},
      {Key::seq0, 0},
      {Key::seq1, 1},
      {Key::seq2, 2},
      {Key::seq3, 3},
      {Key::seq4, 4},
      {Key::seq5, 5},
      {Key::seq6, 6},
      {Key::seq7, 7},
      {Key::seq8, 8},
      {Key::seq9, 9},
      {Key::seq10, 10},
      {Key::seq11, 11},
      {Key::seq12, 12},
      {Key::seq13, 13},
      {Key::seq14, 14},
      {Key::seq15, 15},
      {Key::blue_enc_click, 255},
      {Key::green_enc_click, 255},
      {Key::yellow_enc_click, 255},
      {Key::red_enc_click, 255},
      {Key::shift, 26},
      {Key::sends, 43},
      {Key::plus, 39},
      {Key::routing, 40},
      {Key::minus, 38},
      {Key::fx1, 51},
      {Key::fx2, 44},
      {Key::master, 53},
      {Key::play, 46},
      {Key::record, 45},
      {Key::arp, 48},
      {Key::slots, 37},
      {Key::twist1, 31},
      {Key::twist2, 32},
      {Key::looper, 34},
      {Key::external, 33},
      {Key::sampler, 42},
      {Key::envelope, 50},
      {Key::voices, 47},
      {Key::settings, 52},
      {Key::sequencer, 41},
      {Key::synth, 49},
      {Key::unassigned_a, 35},
      {Key::unassigned_b, 36},
      {Key::unassigned_c, 27},
      {Key::unassigned_d, 28},
      {Key::unassigned_e, 29},
      {Key::unassigned_f, 30},
    }};
  };

} // namespace otto::services

namespace otto::board {
  struct I2CMCUPort final : services::MCUPort {
    struct Config : otto::Config<Config> {
      std::uint16_t address = 0x77;
      std::string device_path = "/dev/i2c-1";
      DECL_VISIT(address, device_path)
    };

    I2CMCUPort(Config::Handle c = {}) : conf(c), i2c(conf->address)
    {
      auto ec = i2c.open(conf->device_path);
      if (ec) throw std::system_error(ec);
    }

    std::size_t write(std::span<std::uint8_t> data) override
    {
      LOGI("Writing {:02X}", fmt::join(data, " "));
      auto ec = i2c.write(data);
      if (ec.value() == EREMOTEIO) {
        LOGW("MCU nack'd i2c write");
        ec = {};
      }
      if (ec) throw std::system_error(ec);
      return data.size();
    }

    std::span<std::uint8_t> read(std::size_t count) override
    {
      data.resize(count);
      auto ec = i2c.read_into(data);
      LOGI("Read: {:02X}", fmt::join(data, " "));
      if (ec.value() == EREMOTEIO) {
        LOGW("MCU nack'd i2c read");
        ec = {};
      }
      if (ec) throw std::system_error(ec);
      return data;
    }

    Config::Handle conf;
    util::I2C i2c;
    std::vector<std::uint8_t> data;
  };

  core::ServiceHandle<services::Controller> make_controller()
  {
    return core::ServiceHandle<services::Controller>([] {
      return std::make_unique<services::MCUController>(std::make_unique<I2CMCUPort>(),
                                                       std::make_unique<services::Betav01HWMap>());
    });
  }
} // namespace otto::board

// kak: other_file=../include/board/controller.hpp
