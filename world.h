#ifndef IK_WORLD_H
#define IK_WORLD_H

#include "updatable.h"

class world : public updatable {
public:
    world(dlib::drawable_window &win);

    void update();

    std::vector<std::unique_ptr<updatable>> items;

    void on_mouse_down(unsigned long btn, unsigned long state, long x, long y, bool is_double_click) override;
};


#endif //IK_WORLD_H
