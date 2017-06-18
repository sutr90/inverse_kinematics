#ifndef IK_DRAWABLES_H
#define IK_DRAWABLES_H

#include <dlib/gui_widgets.h>
#include "updatable.h"
#include "world.h"

class win : public dlib::drawable_window {
    world *wrld;
public:
    win() {
        set_size(640, 480);
        show();
    }

    void set_world(world *wrld) {
        this->wrld = wrld;
    }

    void on_mouse_down(unsigned long btn, unsigned long state, long x, long y, bool is_double_click) {
        wrld->on_mouse_down(btn, state, x, y, is_double_click);
    }

    ~win() {
        close_window();
    }
};




#endif //IK_DRAWABLES_H
