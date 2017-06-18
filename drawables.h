#ifndef IK_DRAWABLES_H
#define IK_DRAWABLES_H

#include <dlib/gui_widgets.h>

using namespace std;
using namespace dlib;

struct updatable : public drawable {
    updatable(drawable_window &w) : drawable(w) {}

    virtual void update() = 0;
};


class win : public drawable_window {
public:
    win() {
        set_size(640, 480);
        show();
    }

    ~win() {
        close_window();
    }
};


class tentacle : public updatable {

    double distance_to_target(dlib::point target, std::vector<double> &angles);

    double partial_gradient(dlib::point target, std::vector<double> &angles, int i);

    void inverse_kinematics(dlib::point target, std::vector<double> &angles);

    double sampling_distance = 0.1;

    double learning_rate = 0.1;

    double distance_threshold = 10;

    std::vector<double> angles;

    point origin;

    std::vector<int> lengths;
    void draw(const canvas &c) const;
public:

    dlib::point forward_kinematics(std::vector<double> &angles);

    tentacle(drawable_window &w, const std::vector<int> &len);

    void update();
    void move(point pt) {
        origin = pt;
    }
};

#endif //IK_DRAWABLES_H
