#include <iostream>

#include "vec3.h"
#include "ray.h"
#include "primitives.h"

using namespace mathy;

vec3 color(const ray& r)
{
    sphere s = { .center = { .x = 0.0, .y = 0.0, .z = -1.0 },
                 .radius = 0.5 };

    if (hit_sphere(s, r))
    {
        return { .x = 1.0, .y = 0.0, .z = 0.0 };
    }

    vec3 unit_direction = normalize(r.d);

    float t = 0.5 * (unit_direction.y + 1.0);

    return lerp({ .x = 1.0, .y = 1.0, .z = 1.0 },
                { .x = 0.5, .y = 0.7, .z = 1.0 },
                t);
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

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            ray r = { .o = origin,
                      .d = (llc + (u * horizontal) +  (v * vertical)) };

            vec3 col = color(r);

            int ir = int(255.99 * col.x);
            int ig = int(255.99 * col.y);
            int ib = int(255.99 * col.z);

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }

}
