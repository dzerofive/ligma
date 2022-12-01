#pragma once

#include "material.hpp"
#include "vec3.hpp"

class sphere : public hittable {
public:
    sphere() {}
    sphere(position center, float radius, std::shared_ptr<material> mat)
        : center(center), radius(radius), mat_ptr(mat) {};

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;


    position center;
    float radius;
    std::shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    vec3 offset_center = r.origin() - center;
    float a = r.direction().lenght_squered();
    float half_b = dot(offset_center, r.direction());
    float c = offset_center.lenght_squered() - radius*radius;

    float discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return 0;
    float sqrt_discriminant = sqrt(discriminant);

    float root = (-half_b - sqrt_discriminant) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrt_discriminant) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.pos = r.at(rec.t);
    vec3 outward_normal = (rec.pos - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}
