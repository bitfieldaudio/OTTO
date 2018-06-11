#include "board/ui/rpi_input.hpp"

namespace otto::board::ui {

  Key translate_key(int key_code, bool ctrl)
  {
    switch (key_code) {
    // Rotaries
    case KEY_Q: return ctrl ? Key::blue_click : Key::blue_up;
    case KEY_A: return ctrl ? Key::blue_click : Key::blue_down;
    case KEY_W: return ctrl ? Key::green_click : Key::green_up;
    case KEY_S: return ctrl ? Key::green_click : Key::green_down;
    case KEY_E: return ctrl ? Key::white_click : Key::white_up;
    case KEY_D: return ctrl ? Key::white_click : Key::white_down;
    case KEY_R: return ctrl ? Key::red_click : Key::red_up;
    case KEY_F: return ctrl ? Key::red_click : Key::red_down;

    case KEY_LEFT: return Key::left;
    case KEY_RIGHT:
      return Key::right;

    // Tapedeck
    case KEY_SPACE: return Key::play;
    case KEY_Z: return Key::rec;
    case KEY_F1: return Key::track_1;
    case KEY_F2: return Key::track_2;
    case KEY_F3: return Key::track_3;
    case KEY_F4:
      return Key::track_4;

    // Numbers
    case KEY_T:
      if (ctrl) {
        return Key::tape;
      }
      break;
    case KEY_Y:
      if (ctrl) {
        return Key::mixer;
      }
      break;
    case KEY_U:
      if (ctrl) {
        return Key::synth;
      }
      break;
    case KEY_G:
      if (ctrl) {
        return Key::metronome;
      }
      break;
    case KEY_H:
      if (ctrl) {
        return Key::sampler;
      }
      break;
    case KEY_J:
      if (ctrl) {
        return Key::drums;
      }
      break;
    case KEY_K:
      if (ctrl) {
        return Key::envelope;
      }
      break;

    case KEY_L: return Key::loop;
    case KEY_I: return Key::loop_in;
    case KEY_O: return Key::loop_out;

    case KEY_X: return Key::cut;
    case KEY_C:
      if (ctrl) {
        return Key::lift;
      }
      break;

    case KEY_V:
      if (ctrl) {
        return Key::drop;
      }
      break;

    case KEY_LEFTSHIFT:
    case KEY_RIGHTSHIFT: return Key::shift;

    case KEY_ESC: return Key::quit;
    }

    return Key::none;
  }

}
