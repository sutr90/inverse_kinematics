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
    auto new_end = dlib::rotate_point(from, to, angle);
    auto diff = new_end - to;
    to = new_end;
    if (next != nullptr) {
        next->move_delta(diff);
        next->rotate(angle);
    }

    this->angle += angle;
}

void segment::move_delta(point delta) {
    auto cursor = this;
    while(cursor != nullptr) {
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

    segments[0]->move_to(point(100, 100));

    segments[0]->rotate(0.2);
    segments[1]->rotate(-0.4);
    segments[2]->rotate(0.8);
}
