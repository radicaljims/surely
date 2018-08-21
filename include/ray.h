#pragma once

#include "vec3.h"

namespace mathy
{
    struct ray
    {
        vec3 o;
        vec3 d;
    };

    vec3 at(const ray& r, float t)
    {
        return r.o + (t * r.d);
    }
}
