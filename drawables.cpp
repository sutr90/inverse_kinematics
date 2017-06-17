#include "drawables.h"

#define RAD_TO_DEG(angleRadians) ((int)(angleRadians * 180.0 / 3.14159265)%360)
#define MYMOD(a, n) ((a % n + n) % n)

void line::update() {}

void segment::append(std::shared_ptr<segment> seg) {
    this->next = seg.get();
    seg->move_to(to);
}


void segment::rotate(double angle) {
    target_angle = angle;
    step = (target_angle - actual_angle) / 50;//TODO speed
}

void segment::move_delta(point delta) {
    auto cursor = this;
    while (cursor != nullptr) {
        cursor->from += delta;
        cursor->to += delta;
        cursor = cursor->next;
    }
}

void segment::move_to(point new_point) {
    auto delta = new_point - from;
    move_delta(delta);
}

void segment::do_rotate() {
    auto cursor = this;
    cursor->actual_angle += step;
    while (cursor != nullptr) {
        auto new_end = dlib::rotate_point(cursor->from, cursor->to, step);
        auto diff = new_end - cursor->to;
        cursor->to = new_end;
        cursor->next->move_delta(diff);
        cursor = cursor->next;
    }
}

void segment::update() {
    auto diff = RAD_TO_DEG(actual_angle) - RAD_TO_DEG(target_angle);
    diff = MYMOD((diff + 180), 360) - 180;
    if (std::abs(diff) > 1) {
        do_rotate();
    }
}

tentacle::tentacle(drawable_window &w, const std::vector<int> &lengths) : updatable(w) {
    for (auto l : lengths) {
        segments.push_back(std::make_shared<segment>(w, l));
    }

    for (unsigned i = 0; i < segments.size() - 1; i++) {
        segments[i]->append(segments[i + 1]);
    }
}

void tentacle::forward_kinematics(std::vector<double> &angles) {
    for (unsigned i = 0; i < segments.size(); i++) {
        segments[i]->rotate(angles[i]);
    }
}

dlib::point tentacle::calculate_endpoint(std::vector<double> &angles) {
    double sum_angle = 0;
    point end_point, offset(0, 0);

    for (unsigned i = 0; i < segments.size(); i++) {
        sum_angle += angles[i];
        end_point = dlib::rotate_point(segments[i]->from + offset, segments[i]->to + offset, sum_angle);
        offset = end_point - segments[i]->to;
    }
    return end_point;
}
