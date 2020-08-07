#pragma once

#include <linux/input-event-codes.h>

#include "lib/util/algorithm.hpp"

namespace otto::board::ui {

  /// Linux keys
  enum struct Key {
    unknown = KEY_UNKNOWN,

    /* Printable keys */
    space = KEY_SPACE,
    apostrophe = KEY_APOSTROPHE,
    comma = KEY_COMMA,
    minus = KEY_MINUS,
    period = KEY_DOT,
    slash = KEY_SLASH,
    n0 = KEY_0,
    n1 = KEY_1,
    n2 = KEY_2,
    n3 = KEY_3,
    n4 = KEY_4,
    n5 = KEY_5,
    n6 = KEY_6,
    n7 = KEY_7,
    n8 = KEY_8,
    n9 = KEY_9,
    semicolon = KEY_SEMICOLON,
    equal = KEY_EQUAL,
    a = KEY_A,
    b = KEY_B,
    c = KEY_C,
    d = KEY_D,
    e = KEY_E,
    f = KEY_F,
    g = KEY_G,
    h = KEY_H,
    i = KEY_I,
    j = KEY_J,
    k = KEY_K,
    l = KEY_L,
    m = KEY_M,
    n = KEY_N,
    o = KEY_O,
    p = KEY_P,
    q = KEY_Q,
    r = KEY_R,
    s = KEY_S,
    t = KEY_T,
    u = KEY_U,
    v = KEY_V,
    w = KEY_W,
    x = KEY_X,
    y = KEY_Y,
    z = KEY_Z,
    left_bracket = KEY_LEFTBRACE,
    backslash = KEY_BACKSLASH,
    right_bracket = KEY_RIGHTBRACE,
    grave_accent = KEY_GRAVE,

    /* Function keys */
    escape = KEY_ESC,
    enter = KEY_ENTER,
    tab = KEY_TAB,
    backspace = KEY_BACKSPACE,
    insert = KEY_INSERT,
    del = KEY_DELETE,
    right = KEY_RIGHT,
    left = KEY_LEFT,
    down = KEY_DOWN,
    up = KEY_UP,
    page_up = KEY_PAGEUP,
    page_down = KEY_PAGEDOWN,
    home = KEY_HOME,
    end = KEY_END,
    caps_lock = KEY_CAPSLOCK,
    scroll_lock = KEY_SCROLLLOCK,
    num_lock = KEY_NUMLOCK,
    print_screen = KEY_PRINT,
    pause = KEY_PAUSE,
    f1 = KEY_F1,
    f2 = KEY_F2,
    f3 = KEY_F3,
    f4 = KEY_F4,
    f5 = KEY_F5,
    f6 = KEY_F6,
    f7 = KEY_F7,
    f8 = KEY_F8,
    f9 = KEY_F9,
    f10 = KEY_F10,
    f11 = KEY_F11,
    f12 = KEY_F12,
    f13 = KEY_F13,
    f14 = KEY_F14,
    f15 = KEY_F15,
    f16 = KEY_F16,
    f17 = KEY_F17,
    f18 = KEY_F18,
    f19 = KEY_F19,
    f20 = KEY_F20,
    f21 = KEY_F21,
    f22 = KEY_F22,
    f23 = KEY_F23,
    f24 = KEY_F24,
    kp_0 = KEY_KP0,
    kp_1 = KEY_KP1,
    kp_2 = KEY_KP2,
    kp_3 = KEY_KP3,
    kp_4 = KEY_KP4,
    kp_5 = KEY_KP5,
    kp_6 = KEY_KP6,
    kp_7 = KEY_KP7,
    kp_8 = KEY_KP8,
    kp_9 = KEY_KP9,
    kp_decimal = KEY_KPDOT,
    kp_divide = KEY_KPSLASH,
    kp_multiply = KEY_KPASTERISK,
    kp_subtract = KEY_KPMINUS,
    kp_add = KEY_KPPLUS,
    kp_enter = KEY_KPENTER,
    kp_equal = KEY_KPEQUAL,
    left_shift = KEY_LEFTSHIFT,
    left_control = KEY_LEFTCTRL,
    left_alt = KEY_LEFTALT,
    left_super = KEY_LEFTMETA,
    right_shift = KEY_RIGHTSHIFT,
    right_control = KEY_RIGHTCTRL,
    right_alt = KEY_RIGHTALT,
    right_super = KEY_RIGHTMETA,
    menu = KEY_MENU,

    last = KEY_LAST,
  };

  /// Modifiers
  enum struct Modifier {
    none = 0,
    shift = 0b0001,
    ctrl = 0b0010,
    alt = 0b0100,
    super = 0b1000,
  };

  /// A set of modifiers
  struct Modifiers {
    std::underlying_type_t<Modifier> data = 0;

    constexpr Modifiers(std::initializer_list<Modifier> mods = {}) noexcept
      : data{util::accumulate(mods, 0, [](auto m1, Modifier m2) {
          return util::underlying(m1) | util::underlying(m2);
        })}
    {}

    constexpr Modifiers(Modifier data) noexcept : data(util::underlying(data)) {}

    constexpr Modifiers(std::underlying_type_t<Modifier> data) noexcept : data(data) {}

    constexpr bool is(Modifier m) const noexcept
    {
      return util::underlying(m) & data;
    }

    constexpr void set(Modifier m, bool flag = true) noexcept
    {
      if (flag)
        data |= util::underlying(m);
      else
        data &= ~util::underlying(m);
    }

    constexpr Modifiers operator&(Modifier m) const noexcept
    {
      return {data & util::underlying(m)};
    }

    constexpr Modifiers operator|(Modifier m) const noexcept
    {
      return {data | util::underlying(m)};
    }

    constexpr Modifiers operator|(Modifiers m) const noexcept
    {
      return {data | m.data};
    }

    constexpr operator bool() const noexcept
    {
      return data != 0;
    }
  };

  enum struct Action { press, release, repeat };

  /// Bind keys by implementing this function
  void handle_keyevent(Action, Modifiers, Key);

} // namespace otto::board::ui
