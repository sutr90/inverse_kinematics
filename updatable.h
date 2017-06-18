#ifndef IK_UPDATABLE_H
#define IK_UPDATABLE_H

#include <dlib/gui_widgets.h>

struct updatable {
    virtual void update() = 0;

    virtual void on_mouse_down(unsigned long, unsigned long, long, long, bool) {};
};

#endif //IK_UPDATABLE_H
