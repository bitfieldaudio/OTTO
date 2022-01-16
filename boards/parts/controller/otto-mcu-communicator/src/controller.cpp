#include "app/services/controller.hpp"

#include <cstdlib>
#include <cstring>
#include <utility>

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "lib/util/i2c.hpp"

#include "app/services/config.hpp"

namespace otto::drivers {

  struct DomainSocketClient {
    DomainSocketClient() = default;
    ~DomainSocketClient() noexcept
    {
      [[maybe_unused]] auto _ = close();
    }

    [[nodiscard]] bool is_open() const noexcept
    {
      return fd > 0;
    }
    [[nodiscard]] std::error_code open(const std::filesystem::path& path)
    {
      struct ::sockaddr_un addr {};

      fd = ::socket(AF_UNIX, SOCK_STREAM, 0);

      // Construct server address, and make the connection.
      ::memset(&addr, 0, sizeof(struct sockaddr_un));
      addr.sun_family = AF_UNIX;
      ::strncpy(addr.sun_path, path.c_str(), sizeof(addr.sun_path) - 1);

      // Connects the active socket referred to be sfd to the listening socket
      // whose address is specified by addr.
      if (::connect(fd, reinterpret_cast<struct ::sockaddr*>(&addr), sizeof(struct ::sockaddr_un)) == -1) {
        LOGC("Could not connect to otto-mcu-communicator socket at {}", path);
      }
      return {};
    }
    [[nodiscard]] std::error_code close()
    {
      if (::shutdown(fd, SHUT_RDWR) < 0) {
        return util::get_clear_errno();
      }
      if (::close(fd) < 0) {
        return util::get_clear_errno();
      }
      fd = -1;
      return {};
    }

    [[nodiscard]] std::error_code write(std::span<const std::uint8_t> message)
    {
      if (::write(fd, message.data(), message.size()) < 0) {
        return util::get_clear_errno();
      }
      return {};
    }
    [[nodiscard]] std::error_code read_into(std::span<std::uint8_t> buffer)
    {
      if (::read(fd, buffer.data(), buffer.size()) < 0) {
        return util::get_clear_errno();
      }
      return {};
    }

  private:
    int fd = -1;
  };

  struct SocketMcuPort final : MCUPort {
    struct Config : otto::Config<Config> {
      std::string socket_path = "/run/otto-mcu-communicator.sock";
      DECL_VISIT(socket_path)
    };

    SocketMcuPort(Config c) : conf(std::move(c))
    {
      auto ec = conn.open(conf.socket_path);
      if (ec) throw std::system_error(ec);
    }

    void write(const Packet& p) override
    {
      LOGT("Sending packet: {} {:02X}", util::enum_name(p.cmd), fmt::join(p.data, " "));
      std::error_code ec = conn.write(p.to_array());
      if (ec) throw std::system_error(ec);
    }

    tl::optional<Packet> read() override
    {
      std::array<std::uint8_t, 17> data = {};

      auto ec = conn.read_into(data);
      if (ec) throw std::system_error(ec);

      if (data[0] == 0) return {};
      Packet res = {static_cast<Command>(data[0])};
      std::copy(data.begin() + 1, data.end(), res.data.begin());
      LOGT("Got packet: {} {:02X}", util::enum_name(res.cmd), fmt::join(res.data, " "));
      return res;
    }

    void stop() override
    {
      // TODO: Unimplemented - is it needed?
    }

    Config conf;
    DomainSocketClient conn;
  };

  std::unique_ptr<MCUPort> MCUPort::make_default(services::ConfigManager& confman)
  {
    return std::make_unique<SocketMcuPort>(confman);
  }
} // namespace otto::drivers

// kak: other_file=../include/board/controller.hpp
