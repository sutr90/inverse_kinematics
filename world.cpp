#include "world.h"

world::world(win &win) : main_win(&win) {
    std::vector<int> seg = {50,50,50,50};
    std::vector<double> rot = {0.785,0,0,0};

    auto t = std::make_unique<tentacle>(win, seg);
    t->move(point(100, 100));
    t->forward_kinematics(rot);
//    auto end = t->calculate_endpoint(rot);
//
//    auto dist = t->distance_to_target(rot, point(100,250));


    items.emplace_back(std::move(t));
}

void world::update() {
    for (auto &item : items) {
        item->update();
    }

    main_win->invalidate_rectangle(rectangle(0, 0, 640, 480));
}
