#include "world.h"

world::world(win &win) : main_win(&win) {
//    items.emplace_back(std::move(std::make_unique<line>(win, point(200, 200), point(100, 100))));

    std::vector<int> seg = {100, 100, 100, 100};
    items.emplace_back(std::move(std::make_unique<tentacle>(win, seg)));
}

void world::update() {
    for (auto &item : items) {
        item->update();
    }

    main_win->invalidate_rectangle(rectangle(0, 0, 640, 480));
}
