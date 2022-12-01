#include <iostream>
#include <limits>

#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "rtutil.hpp"
#include "random.hpp"

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.14159265358979;

inline float deg_to_rad(float degrees) {
    return degrees * pi / 180.0;
}

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    if (depth <= 0)
        return color(0, 0, 0);

    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    float res = 0.5f*(unit_direction.y() + 1.0);
    return (1.0f-res)*color(1.0f, 1.0f, 1.0f) + res*color(0.5f, 0.7f, 1.f);
}

int main(int argc, char *argv[]) {
    // Image
    const float aspect_ratio = 16.f/9.f;
    const int image_width = 1920;
    const int image_height = static_cast<int>(image_width/aspect_ratio);
    const int samples_per_pixel = 48;
    const int max_depth = 5;

    // World
    hittable_list world;

    auto material_solid = std::make_shared<lambertian>(color(0.8, 0.8, 0.8));
    auto material_blue = std::make_shared<lambertian>(color(0.2, 0.2, 0.9));
    auto material_red   = std::make_shared<lambertian>(color(0.9, 0.35, 0.35));
    auto material_metal = std::make_shared<metal>(color(0.8, 0.6, 0.4), 0.3);

    world.add(std::make_shared<sphere>(position(0, 0, -1), 0.5f, material_red));
    world.add(std::make_shared<sphere>(position(0, -100.5, -1), 100, material_solid));
    world.add(std::make_shared<sphere>(position(1, -0.3, -1.2), 0.2f, material_solid));
    world.add(std::make_shared<sphere>(position(-0.7, -0.2, -0.8), 0.3f, material_metal));
    world.add(std::make_shared<sphere>(position(1.5, 1, -4), 2.5f, material_blue));
    world.add(std::make_shared<sphere>(position(1.6, -0.4, -1.1), 0.1f, material_red));
    world.add(std::make_shared<sphere>(position(-1.3, -0.4, -0.8), 0.1f, material_solid));
    world.add(std::make_shared<sphere>(position(-0.3, -0.4, -0.5), 0.1f, material_blue));
    world.add(std::make_shared<sphere>(position(-0.2, -0.4, -0.6), 0.1f, material_metal));

    // Camera
    camera cam;

    // Render
    // Image info
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    // Render line-by-line, left to right, from top to bottom
    for (int j = image_height-1; j>= 0; --j) {
        std::cerr << "\rScanlinex remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                float u = float(i + random_float()) / (image_width-1);
                float v = float(j + random_float()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    return 0;
}
