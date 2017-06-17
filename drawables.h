#ifndef IK_DRAWABLES_H
#define IK_DRAWABLES_H

#include <dlib/gui_widgets.h>

using namespace std;
using namespace dlib;

struct updatable : public drawable {
    updatable(drawable_window &w) : drawable(w) {}

    virtual void update() = 0;
};

class line : public updatable {

    friend class tentacle;

public:
    line(drawable_window &w) : line(w, point(), point()) {
        enable_events();
    }

    line(drawable_window &w, dlib::point from_, dlib::point to_) : updatable(w), from(from_), to(to_) {
        enable_events();
    }

    ~line() {
        disable_events();
    }

    void update();

    dlib::point from;
    dlib::point to;

protected:
    void draw(const canvas &c) const {

        draw_line(c, from, to);
    }
};


class win : public drawable_window {
public:
    win() : cb(*this) {
        set_size(640, 480);
        show();
    }

    ~win() {
        close_window();
    }

    line cb;
};


class segment : public line {
    segment* previous = nullptr;
    segment* next = nullptr;

public:
    segment(drawable_window &w, int length) : line(w, point(0, 0), point(length, 0)) {};
    double angle = 0;

    void append(std::shared_ptr<segment> seg);

    void rotate(double angle);

    void move_delta(point delta);

    void move_to(point new_point);

};

class tentacle : public updatable {

    std::vector<std::shared_ptr<segment>> segments;
public:
    tentacle(drawable_window &w, const std::vector<int> &lengths);

    void update() {};

    void draw(const canvas &c) const {
        for (auto seg : segments) {
            seg->draw(c);
        }
    }

};

#endif //IK_DRAWABLES_H
