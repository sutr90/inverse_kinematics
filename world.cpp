#include "world.h"

world::world(win &win) : main_win(&win) {
    std::vector<int> seg = {100, 100, 100, 100};
    std::vector<double> rot = {0.2, -0.4, 0.8, -0.6};

    auto t = std::make_unique<tentacle>(win, seg);
    t->move(point(100,100));
    t->forward_kinematics(rot);

    items.emplace_back(std::move(t));
}

void world::update() {
    for (auto &item : items) {
        item->update();
    }

    main_win->invalidate_rectangle(rectangle(0, 0, 640, 480));
}
