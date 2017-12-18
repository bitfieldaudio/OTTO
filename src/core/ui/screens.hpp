#pragma once

#include <vector>
#include <functional>
#include "core/ui/widget.hpp"
#include "core/ui/drawing.hpp"

namespace otto::ui {

  template<typename ItemType>
  class SelectorScreen : public Screen {
    const float itemHeight = 20;
    int topItem;
  public:
    int selectedItem;
    struct Item {
      std::string name;
      ItemType value;
    };
    using ItemMap = std::vector<Item>;
    ItemMap items;
    vg::Colour itemColour;
    std::function<void()> onSelect = []() {};

    SelectorScreen(const ItemMap&, vg::Colour);

    void draw(vg::Canvas&) override;
    bool keypress(ui::Key) override;
    void rotary(ui::RotaryEvent) override;

    void prev(int = 1);
    void next(int = 1);
    void select(int);
  };

  /****************************************/
  /* SelectorScreen Implementation        */
  /****************************************/

  template<typename T>
  SelectorScreen<T>::SelectorScreen(const ItemMap& items, vg::Colour c) :
    items (items), itemColour (c) {}

  template<typename T>
  void SelectorScreen<T>::draw(vg::Canvas& ctx) {
    using namespace vg;

    int nitems = std::min<int>(items.size(), HEIGHT / itemHeight);

    for (int i = 0; i < nitems; i++) {
      int idx = topItem + i;

      if (idx == selectedItem) {
        ctx.beginPath();
        ctx.rect({40.f, i * itemHeight}, {160.f, itemHeight});
        ctx.fill(itemColour);
        ctx.stroke(itemColour);
        ctx.fillStyle(Colours::Black);
      } else {
        ctx.fillStyle(itemColour);
      }
      ctx.beginPath();
      ctx.textAlign(TextAlign::Left, TextAlign::Middle);
      ctx.font(Fonts::Light);
      ctx.font(15.f);
      ctx.fillText(items[idx].name, {45.f, (i + 0.5f) * itemHeight});
    }
  }

  template<typename T>
  bool SelectorScreen<T>::keypress(ui::Key key) {
    return false;
  }

  template<typename T>
  void SelectorScreen<T>::rotary(ui::RotaryEvent e) {
    select(selectedItem - e.clicks);
  }

  template<typename T>
  void SelectorScreen<T>::prev(int n) {
    select(selectedItem - n);
  }

  template<typename T>
  void SelectorScreen<T>::next(int n) {
    select(selectedItem + n);
  }

  template<typename T>
  void SelectorScreen<T>::select(int i) {
    selectedItem = std::clamp<int>(i, 0, items.size() - 1);
    onSelect();
  }
}
