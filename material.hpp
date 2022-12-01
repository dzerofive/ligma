#pragma once

#include "ray.hpp"
#include "hittable.hpp"

class material {
public:
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
public:
    lambertian(const color& color) : albedo(color) {}

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {

        vec3 scatter_direction = rec.normal + random_unit_vector();

        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = ray(rec.pos, scatter_direction);
        attenuation = albedo;
        return true;
    }

    color albedo;
};

class metal : public material {
public:
    metal(const color& color, float fuzz) : albedo(color), fuzz(fuzz < 1 ? fuzz : 1) {}

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {

        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.pos, reflected + fuzz*random_in_unit_sphere());
        attenuation = albedo;
        return true;
    }

    color albedo;
    float fuzz;
};
