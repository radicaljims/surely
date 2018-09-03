#pragma once

#include "vec3.h"

namespace geometry
{
    struct intersection
    {
        float t;
        mathy::vec3  p;
        mathy::vec3  normal;
    };

    bool operator< (const struct intersection& lhs, const struct intersection& rhs)
    {
        return lhs.t < rhs.t;
    }
}
