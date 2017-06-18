#include "tentacle.h"

tentacle::tentacle(dlib::drawable_window &w, const std::vector<int> &len) : drawable(w), origin(0, 0), lengths(len) {
    angles.resize(len.size(), 0.0);
    enable_events();
}

dlib::point tentacle::forward_kinematics(std::vector<double> &angles) {
    double sum_angle = 0;
    dlib::point center = origin, end_point;

    for (unsigned i = 0; i < angles.size(); i++) {
        sum_angle += angles[i];
        end_point = center;
        end_point.x() += lengths[i];

        center = dlib::rotate_point(center, end_point, sum_angle);
    }

    return center;
}

double tentacle::distance_to_target(std::vector<double> &angles) {
    auto endpoint = forward_kinematics(angles);
    return dlib::length(endpoint - target);
}

double tentacle::partial_gradient(std::vector<double> &angles, int i) {
    double angle = angles[i];

    // Gradient : [F(x+SamplingDistance) - F(x)] / h
    double f_x = error_function(angles);

    angles[i] += sampling_distance;
    double f_x_plus_d = error_function(angles);

    double gradient = (f_x_plus_d - f_x) / sampling_distance;

    // Restores
    angles[i] = angle;

    return gradient;
}

void tentacle::inverse_kinematics(std::vector<double> &angles) {
    if (error_function(angles) < distance_threshold)
        return;

    for (int i = angles.size() - 1; i >= 0; i--) {
        // Gradient descent
        // Update : Solution -= LearningRate * Gradient
        double gradient = partial_gradient(angles, i);
        angles[i] -= learning_rate * gradient;

        angles[i] = std::min(dlib::pi, std::max(angles[i], -dlib::pi));

        // Early termination
        if (error_function(angles) < distance_threshold)
            return;
    }
}

void tentacle::draw(const dlib::canvas &c) const {
    double sum_angle = 0;
    dlib::point start_point = origin, end_point;

    for (unsigned i = 0; i < angles.size(); i++) {
        sum_angle += angles[i];
        end_point = start_point;
        end_point.x() += lengths[i];

        end_point = dlib::rotate_point(start_point, end_point, sum_angle);

        dlib::draw_line(c, start_point, end_point);
        start_point = end_point;
    }
}

void tentacle::update() {
    inverse_kinematics(angles);
}

void tentacle::on_mouse_down(unsigned long btn, unsigned long, long x, long y, bool is_double_click) {
    if (btn == 1 && is_double_click) {
        target.x() = x;
        target.y() = y;
    }
}

double tentacle::error_function(std::vector<double> &angles) {
    return distance_to_target(angles);
}

