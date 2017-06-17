#ifndef IK_WORLD_H
#define IK_WORLD_H


#include "drawables.h"

class world {

    win* main_win;
public:
    world(win &win);

    void update();

    std::vector<std::unique_ptr<updatable>> items;
};


#endif //IK_WORLD_H
