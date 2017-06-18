#include "world.h"
#include "tentacle.h"

world::world(dlib::drawable_window &win) {
    std::vector<int> seg(50, 10);
    auto t = std::make_unique<tentacle>(win, seg);
    t->move(dlib::point(320, 240));

    items.emplace_back(std::move(t));
}

void world::update() {
    for (auto &item : items) {
        item->update();
    }
}

void world::on_mouse_down(unsigned long btn, unsigned long state, long x, long y, bool is_double_click) {
    for (auto &item : items) {
        item->on_mouse_down(btn, state, x, y, is_double_click);
    }
}
