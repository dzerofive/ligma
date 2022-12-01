#pragma once

#include "vec3.hpp"
#include "ray.hpp"
#include "random.hpp"

class camera {
public:
    camera() {
        float aspect_ratio = 16.0f / 9.0f;
        float viewport_height = 2.f;
        float viewport_width = aspect_ratio * viewport_height;
        float focal_length = 1.f;

        // Ray would be projected from this point
        origin = position(0, 0, 0);
        // To a plane set here
        horizontal = vec3(viewport_width, 0.f, 0.f);
        vertical = vec3(0.f, viewport_height, 0.f);
        // Half of width and height + offset forward to a focal lenght
        lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
    }

    ray get_ray(float u, float v) const {
        return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }
private:
    position origin;
    position lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};
