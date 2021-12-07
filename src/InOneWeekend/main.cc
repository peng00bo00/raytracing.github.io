//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;

    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    // background
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1024;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera
    // auto viewport_height = 2.0;
    // auto viewport_width = aspect_ratio * viewport_height;
    // auto focal_length = 1.0;

    // auto origin = point3();
    // auto horizontal = vec3(viewport_width, 0, 0);
    // auto vertical = vec3(0, viewport_height, 0);
    // auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
    camera cam;


    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < image_width; ++i)
        {   
            // "Hello World!" in CG
            // auto r = double(i) / (image_width -1);
            // auto g = double(j) / (image_height-1);
            // auto b = 0.25;

            // int ir = static_cast<int>(255.999 * r);
            // int ig = static_cast<int>(255.999 * g);
            // int ib = static_cast<int>(255.999 * b);

            // std::cout << ir << ' ' << ig << ' ' << ib << '\n';

            // color color_pixel_color(double(i)/(image_width-1), double(j)/(image_height-1), 0.25);
            // write_color(std::cout, color_pixel_color);

            // Sending Rays
            color pixel_color(0, 0, 0);

            for (size_t s = 0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (image_width -1);
                auto v = (j + random_double()) / (image_height-1);

                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world);
            }
            
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
        
    }

    std::cerr << "\nDone.\n";

}