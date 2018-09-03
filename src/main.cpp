#include <iostream>
#include <vector>

#include "vec3.h"
#include "ray.h"
#include "primitives.h"
#include "material.h"
#include "camera.h"

using namespace mathy;

// TODO: still haven't done that t-windowing thing
vec3 color(const primitives& ps, const ray& r, int depth)
{
    intersections is = intersect(ps, r);

    if (is.size())
    {
        auto closest = is.begin();

        // vec3 target = closest->i.p + closest->i.normal + point_on_sphere();
        // return 0.5 * color(ps, { closest->i.p, target - closest->i.p });

        materials::material_interaction mat = closest->m(r, closest->i);

        if (depth < 50 && mat.valid)
        {
            return mat.attenuation * color(ps, mat.scattered, depth + 1);
        }
        else
        {
            return  { 0.0, 0.0, 0.0 };
        }
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

    auto empty_material      = materials::make_empty_material({ 0.0, 0.0, 0.0 });

    auto lambertian_purpley = materials::make_lambertian_material({ 0.3, 0.5, 0.5 });
    auto lambertian_reddish = materials::make_lambertian_material({ 0.8, 0.3, 0.1 });

    // auto metal_material      = materials::make_metal_material({ 0.8, 0.6, 0.2 });
    auto metal_material      = materials::make_metal_material({ 0.8, 0.8, 0.8 });

    std::vector<sphere> spheres = {
        { .center = { .x = 0.0, .y = 0.0, .z = -1.0 },
          .radius = 0.5, .m = metal_material },

        { .center = { .x = 2.0, .y = 0.0, .z = -1.0 },
          .radius = 0.5, .m = lambertian_reddish },

        { .center = { .x = 0.0, .y = -100.5, .z = -1.0 },
          .radius = 100, .m = lambertian_purpley }
    };

    primitives ps;

    std::for_each(spheres.begin(), spheres.end(), [&] (const sphere& s) { ps.push_back(make_sphere_primitive(s)); });

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

                col = col + color(ps, r, 0);
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
