#ifndef IK_TENTACLE_H
#define IK_TENTACLE_H

#include <dlib/gui_widgets/drawable.h>
#include "updatable.h"

class tentacle : public updatable, public dlib::drawable {
    double sampling_distance = 0.1;
    double learning_rate = 0.0001;
    double distance_threshold = 10;
    std::vector<double> angles;
    dlib::point origin;
    dlib::point target;
    std::vector<int> lengths;

    void draw(const dlib::canvas &c) const;

    dlib::point forward_kinematics(std::vector<double> &angles);

    double error_function(std::vector<double> &angles);

    double distance_to_target(std::vector<double> &angles);

    double partial_gradient(std::vector<double> &angles, int i);

    void inverse_kinematics(std::vector<double> &angles);

public:
    tentacle(dlib::drawable_window &w, const std::vector<int> &len);

    void update();

    void move(dlib::point pt) {
        origin = pt;
    }

    ~tentacle() {
        disable_events();
    }

    void on_mouse_down(unsigned long btn, unsigned long state, long x, long y, bool is_double_click) override;
};


#endif //IK_TENTACLE_H
