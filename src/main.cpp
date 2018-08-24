#include <iostream>
#include <vector>

#include "vec3.h"
#include "ray.h"
#include "primitives.h"

using namespace mathy;

vec3 color(std::vector<sphere> spheres, const ray& r)
{
    // for(auto&& s : spheres)
    // {
    //     intersection i = intersect(s, r);

    //     // We can only hit one sphere for now I guess
    //     if (i.t > 0.0)
    //     {
    //         return 0.5 * (i.normal + vec3({.x = 1.0, .y = 1.0, .z = 1.0}));
    //     }
    // }

    intersections is = intersect(spheres, r);

    if (is.size())
    {
        auto closest = is.begin();

        // std::cerr << closest->t << std::endl;

        return 0.5 * (closest->normal + vec3({ .x = 1.0, .y = 1.0, .z = 1.0 }));
    }

    vec3 unit_direction = normalize(r.d);

    float blend = 0.5 * (unit_direction.y + 1.0);

    return lerp({ .x = 1.0, .y = 1.0, .z = 1.0 },
                { .x = 0.5, .y = 0.7, .z = 1.0 },
                blend);
}

int main()
{
    int nx = 200;
    int ny = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 llc        = { .x = -2.0, .y = -1.0, .z = -1.0 };
    vec3 horizontal = { .x =  4.0, .y =  0.0, .z =  0.0 };
    vec3 vertical   = { .x =  0.0, .y =  2.0, .z =  0.0 };
    vec3 origin     = { .x =  0.0, .y =  0.0, .z =  0.0 };

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
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            ray r = { .o = origin,
                      .d = (llc + (u * horizontal) +  (v * vertical)) };

            vec3 col = color(spheres, r);

            int ir = int(255.99 * col.x);
            int ig = int(255.99 * col.y);
            int ib = int(255.99 * col.z);

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }

}
