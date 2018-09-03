#pragma once

#include "ray.h"

namespace renderer
{
    struct camera
    {
        mathy::vec3 llc;
        mathy::vec3 horizontal;
        mathy::vec3 vertical;
        mathy::vec3 origin;
    };

    const struct camera DEFAULT_CAMERA =
    {
        { .x = -2.0, .y = -1.0, .z = -1.0 },
        { .x =  4.0, .y =  0.0, .z =  0.0 },
        { .x =  0.0, .y =  2.0, .z =  0.0 },
        { .x =  0.0, .y =  0.0, .z =  0.0 }
    };

    inline mathy::ray get_ray(struct camera &c, float u, float v)
    {
        return { c.origin, c.llc + (u * c.horizontal) + (v * c.vertical) - c.origin };
    }

}
