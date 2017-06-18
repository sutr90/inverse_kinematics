#include "world.h"

world::world(win &win) : main_win(&win) {
    std::vector<int> seg = {100,100,100,100};
    std::vector<double> rot = {1.57,1.57,1.57,1.57};

    auto t = std::make_unique<tentacle>(win, seg);
    t->move(point(320,240));
    auto end = t->forward_kinematics(rot);
    cout << end;
//    auto end = t- >forward_kinematics(rot);
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
