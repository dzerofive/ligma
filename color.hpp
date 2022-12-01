#pragma once

#include <iostream>

#include "vec3.hpp"
#include "rtutil.hpp"

void write_color(std::ostream& os, color pixel_color, int samples_per_pixel) {
    float r = pixel_color.x();
    float g = pixel_color.y();
    float b = pixel_color.z();

    float scale = 1.f / samples_per_pixel;
    r = sqrt(r*scale);
    g = sqrt(g*scale);
    b = sqrt(b*scale);

    os << static_cast<int>(256 * clamp(r, 0.f, 0.999f)) << ' '
       << static_cast<int>(256 * clamp(g, 0.f, 0.999f)) << ' '
       << static_cast<int>(256 * clamp(b, 0.f, 0.999f)) << '\n';
}
