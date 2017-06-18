#include "drawables.h"

tentacle::tentacle(drawable_window &w, const std::vector<int> &len) : updatable(w), origin(0, 0), lengths(len) {
    angles.resize(len.size(), 0.0);
}

dlib::point tentacle::forward_kinematics(std::vector<double> &angles) {
    double sum_angle = 0;
    point center = origin, end_point;

    for (unsigned i = 0; i < angles.size(); i++) {
        sum_angle += angles[i];
        end_point = center;
        end_point.x() += lengths[i];

        center = dlib::rotate_point(center, end_point, sum_angle);
    }

    return center;
}

double tentacle::distance_to_target(dlib::point target, std::vector<double> &angles) {
    auto endpoint = forward_kinematics(angles);
    return dlib::length(endpoint - target);
}

double tentacle::partial_gradient(dlib::point target, std::vector<double> &angles, int i) {
    double angle = angles[i];

    // Gradient : [F(x+SamplingDistance) - F(x)] / h
    double f_x = distance_to_target(target, angles);

    angles[i] += sampling_distance;
    double f_x_plus_d = distance_to_target(target, angles);

    double gradient = (f_x_plus_d - f_x) / sampling_distance;

    // Restores
    angles[i] = angle;

    return gradient;
}

void tentacle::inverse_kinematics(dlib::point target, std::vector<double> &angles) {
    if (distance_to_target(target, angles) < distance_threshold)
        return;

    for (int i = angles.size() - 1; i >= 0; i--) {
        // Gradient descent
        // Update : Solution -= LearningRate * Gradient
        double gradient = partial_gradient(target, angles, i);
        angles[i] -= learning_rate * gradient;

        // Early termination
        if (distance_to_target(target, angles) < distance_threshold)
            return;
    }
}

void tentacle::draw(const canvas &c) const {
    double sum_angle = 0;
    point center = origin, end_point;

    for (unsigned i = 0; i < angles.size(); i++) {
        sum_angle += angles[i];
        end_point = center;
        end_point.x() += lengths[i];

        center = dlib::rotate_point(center, end_point, sum_angle);

        draw_line(c, center, end_point);
    }
}

void tentacle::update() {
    point target;
    inverse_kinematics(target, angles);
}

