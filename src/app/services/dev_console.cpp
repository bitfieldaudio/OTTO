#include "dev_console.hpp"

#include <cstddef>
#include <cstdlib>

#include <linenoise.h>

#include "lib/util/algorithm.hpp"
#include "lib/util/tweaks.hpp"

namespace otto::services {

  static void dev_console_completions(const char* input_c, linenoiseCompletions* completions)
  {
    using namespace std::literals;
    util::string_ref input = input_c;
    if ("stop"sv.starts_with(input)) {
      linenoiseAddCompletion(completions, "stop");
    }

    if ("quit"sv.starts_with(input)) {
      linenoiseAddCompletion(completions, "quit");
    }

    if ("tweak"sv.starts_with(input)) {
      linenoiseAddCompletion(completions, "tweak");
    }

    if (input.starts_with("tweak ")) {
      auto tweaks = util::tweak_details::tweaks.lock_shared();
      for (const auto& [k, val] : *tweaks) {
        auto completion = fmt::format("tweak {}", k);
        linenoiseAddCompletion(completions, completion.c_str());
      }
    }
  }

  DevConsole::DevConsole(RuntimeController& runtime) : rt(runtime)
  {
    thread = std::jthread([this](const std::stop_token& st) {
      linenoiseHistorySetMaxLen(64);
      linenoiseSetCompletionCallback(dev_console_completions);
      while (!st.stop_requested() && !rt.stop_requested()) {
        util::string_ref line = linenoise("> ");
        std::cout << '\n';
        linenoiseHistoryAdd(line.c_str());
        run_command(line);

        ::free((void*) line.data()); // NOLINT
      }
    });
  }

  std::ostream& write_tweak(std::ostream& stream, const std::any& val)
  {
    if (val.type() == typeid(int)) {
      return stream << std::any_cast<int>(val);
    }
    if (val.type() == typeid(uint)) {
      return stream << std::any_cast<uint>(val);
    }
    if (val.type() == typeid(int8_t)) {
      return stream << std::any_cast<int8_t>(val);
    }
    if (val.type() == typeid(uint8_t)) {
      return stream << std::any_cast<uint8_t>(val);
    }
    if (val.type() == typeid(float)) {
      return stream << std::any_cast<float>(val);
    }
    if (val.type() == typeid(double)) {
      return stream << std::any_cast<double>(val);
    }
    return stream << "[unknown tweak type]";
  }

  void print_tweak(util::string_ref key, const std::any& val)
  {
    std::cout << key << " = ";
    write_tweak(std::cout, val) << '\n';
  }

  void set_tweak(util::string_ref key, util::string_ref val_str)
  {
    auto any = util::get_tweak_any(key);
    if (!any) {
      std::cout << "Error: Tweak " << key << " does not exist" << '\n';
      return;
    }
    if (any->type() == typeid(int)) {
      return util::set_tweak<int>(key, std::strtol(val_str.c_str(), nullptr, 0));
    }
    if (any->type() == typeid(uint)) {
      return util::set_tweak<uint>(key, std::strtol(val_str.c_str(), nullptr, 0));
    }
    if (any->type() == typeid(int8_t)) {
      return util::set_tweak<int8_t>(key, std::strtol(val_str.c_str(), nullptr, 0));
    }
    if (any->type() == typeid(uint8_t)) {
      return util::set_tweak<uint8_t>(key, std::strtol(val_str.c_str(), nullptr, 0));
    }
    if (any->type() == typeid(float)) {
      return util::set_tweak<float>(key, std::strtof(val_str.c_str(), nullptr));
    }
    if (any->type() == typeid(double)) {
      return util::set_tweak<double>(key, std::strtod(val_str.c_str(), nullptr));
    }
    std::cout << "Error: Tweak " << key << " has unknown type " << '\n';
  }

  void DevConsole::run_command(util::string_ref line)
  {
    std::string_view rest = line;
    auto arg = [&]() -> std::string_view {
      auto [arg, new_rest] = util::split_string(rest, ' ');
      rest = new_rest;
      return arg;
    };

    auto cmd = arg();

    if (cmd == "stop" || cmd == "quit" || cmd == "q") {
      rt.request_stop();
      return;
    }

    if (cmd == "tweak") {
      auto name = std::string(arg());
      auto val = std::string(arg());

      if (name.empty()) {
        fmt::print("Tweaks:\n");
        auto tweaks = util::tweak_details::tweaks.lock_shared();
        for (const auto& [k, val] : *tweaks) {
          print_tweak(k, val);
        }
        return;
      }

      if (val.empty()) {
        print_tweak(name, val);
      } else {
        set_tweak(name, val);
        print_tweak(name, util::get_tweak_any(name));
      }
    }
  }
} // namespace otto::services
