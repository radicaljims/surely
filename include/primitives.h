#pragma once

#include "ray.h"

namespace mathy
{
    struct sphere
    {
        vec3 center;
        float radius;
    };

    bool hit_sphere(const sphere& s, const ray& r)
    {
        vec3 oc = r.o - s.center;

        float a = length_squared(r.d);
        float b = 2.0 * dot(oc, r.d);
        float c = length_squared(oc) - (s.radius * s.radius);

        float disc = (b * b) - (4 * a * c);

        return disc > 0;
    }
}
