#include "drawables.h"

void line::update() {
    to = dlib::rotate_point(from, to, 0.1);
}

void segment::append(std::shared_ptr<segment> seg) {
    this->next = seg.get();
    seg->previous = this;

    seg->move_to(to);
}


void segment::rotate(double angle) {
    auto cursor = this;
    while (cursor != nullptr) {
        auto new_end = dlib::rotate_point(cursor->from, cursor->to, angle);
        auto diff = new_end - cursor->to;
        cursor->to = new_end;
        cursor->next->move_delta(diff);
        cursor->angle += angle;
        cursor = cursor->next;
    }
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

tentacle::tentacle(drawable_window &w, const std::vector<int> &lengths) : updatable(w) {
    for (auto l : lengths) {
        segments.push_back(std::make_shared<segment>(w, l));
    }

    for (unsigned i = 0; i < segments.size() - 1; i++) {
        segments[i]->append(segments[i + 1]);
    }
}

void tentacle::forward_kinematics(std::vector<double> &angles) {
    for (auto i = 0; i < segments.size(); i++) {
        segments[i]->rotate(angles[i]);
    }
}
