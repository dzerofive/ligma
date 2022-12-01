#pragma once

#include <cmath>
#include <iostream>

#include "random.hpp"

class vec3 {
public:
    vec3() : value{0, 0, 0} {};
    vec3(float x, float y, float z) : value{x, y, z} {};

    float x() const {return value[0];}
    float y() const {return value[1];}
    float z() const {return value[2];}

    vec3 operator-() const { return vec3(-value[0], -value[1], -value[2]); }
    float operator[](int index) const { return value[index]; }
    float& operator[](int index) { return value[index]; }

    float lenght() const {
        return std::sqrt(lenght_squered());
    }
    float lenght_squered() const {
        return value[0]*value[0] + value[1]*value[1] + value[2]*value[2];
    }

    vec3& operator*=(const float operand) {
        value[0] *= operand;
        value[1] *= operand;
        value[2] *= operand;
        return *this;
    }
    vec3& operator+=(const vec3& operand) {
        value[0] += operand.value[0];
        value[1] += operand.value[1];
        value[2] += operand.value[2];
        return *this;
    }
    vec3& operator/=(const float t) {
        return *this *= 1/t;
    }

    inline static vec3 random() {
        return vec3(random_float(), random_float(), random_float());
    }
    inline static vec3 random(float min, float max) {
        return vec3(random_float(min, max),
                    random_float(min, max),
                    random_float(min, max));
    }

    bool near_zero() const {
        const float s = 1e-8;
        return (std::fabs(value[0]) < s) && (std::fabs(value[1]) < s) && (std::fabs(value[2]) < s);
    };

    // -------

    float value[3];

};

using position = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream &os, const vec3 &vec) {
    return os << vec.value[0] << ' ' << vec.value[1] << ' ' << vec.value[2];
}
inline vec3 operator+(const vec3& first, const vec3 second) {
    return vec3(first.value[0] + second.value[0], first.value[1] + second.value[1], first.value[2] + second.value[2]);
}
inline vec3 operator-(const vec3& first, const vec3 second) {
    return vec3(first.value[0] - second.value[0], first.value[1] - second.value[1], first.value[2] - second.value[2]);
}

inline vec3 operator*(const vec3& first, const vec3 second) {
    return vec3(first.value[0] * second.value[0], first.value[1] * second.value[1], first.value[2] * second.value[2]);
}
inline vec3 operator*(const vec3& first, const float second) {
    return vec3(first.value[0] * second, first.value[1] * second, first.value[2] * second);
}
inline vec3 operator*(const float second, const vec3& first) {
    return vec3(first * second);
}

inline vec3 operator/(const vec3& first, float second) {
    return (1/second) * first;
}

inline float dot(const vec3& first, const vec3& second) {
    return first.value[0] * second.value[0]
         + first.value[1] * second.value[1]
         + first.value[2] * second.value[2];
}

inline vec3 cross(const vec3& first, const vec3& second) {
    return vec3(first.value[1] * second.value[2] - first.value[2] * second.value[1],
                first.value[2] * second.value[0] - first.value[0] * second.value[2],
                first.value[0] * second.value[1] - first.value[1] * second.value[0]);
}

inline vec3 unit_vector(vec3 vector) {
    return vector / vector.lenght();
}

inline vec3 random_in_unit_sphere() {
    while (true) {
        vec3 p = vec3::random(-1, 1);
        if (p.lenght_squered() >= 1) continue;
        return p;
    }
}

vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_shpere = random_in_unit_sphere();
    if (dot(in_unit_shpere, normal) > 0.f)
        return in_unit_shpere;
    else
        return -in_unit_shpere;
}

vec3 reflect(const vec3& vector, const vec3& normal) {
    return vector - 2*dot(vector, normal) * normal;
}
