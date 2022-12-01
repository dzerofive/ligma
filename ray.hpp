#pragma once

#include "vec3.hpp"

class ray {
public:
    ray() {}
    ray(const position& origin, const vec3& direction)
        : orig(origin), dir(direction) {}

    position origin() const { return orig; }
    vec3 direction() const { return dir; }

    position at(float lenght) const {
        return orig + lenght * dir;
    }

    position orig;
    vec3 dir;
};
