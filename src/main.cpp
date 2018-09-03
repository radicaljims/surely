#include <iostream>
#include <vector>

#include "vec3.h"
#include "ray.h"
#include "primitives.h"
#include "camera.h"

using namespace mathy;

vec3 point_on_sphere()
{
    return normalize( { float(drand48()), float(drand48()), float(drand48()) } );
}

// TODO: still haven't done that t-windowing thing
vec3 color(std::vector<sphere> spheres, const ray& r)
{
    intersections is = intersect(spheres, r);

    if (is.size())
    {
        auto closest = is.begin();

        vec3 target = closest->p + closest->normal + point_on_sphere();
        return 0.5 * color(spheres, { closest->p, target - closest->p });
    }

    vec3 unit_direction = normalize(r.d);

    float blend = 0.5 * (unit_direction.y + 1.0);

    return lerp({ .x = 1.0, .y = 1.0, .z = 1.0 },
                { .x = 0.5, .y = 0.7, .z = 1.0 },
                blend);
}

int main()
{
    int nx = 400;
    int ny = 200;
    int ns = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    renderer::camera c = renderer::DEFAULT_CAMERA;

    std::vector<sphere> spheres = {
        { .center = { .x = 0.0, .y = 0.0, .z = -1.0 },
          .radius = 0.5 },

        { .center = { .x = 0.0, .y = -100.5, .z = -1.0 },
          .radius = 100 }

    };

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col = { 0.0, 0.0, 0.0 };

            for(int s = 0; s < ns; s++)
            {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);

                ray r = get_ray(c, u, v);

                col = col + color(spheres, r);
            }

            // TODO: maybe a running average would be cool
            col = 1.0 / float(ns) * col;

            int ir = int(255.99 * std::sqrt(col.x));
            int ig = int(255.99 * std::sqrt(col.y));
            int ib = int(255.99 * std::sqrt(col.z));

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }

}
