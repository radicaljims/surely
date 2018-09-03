#pragma once

#include "intersection.h"
#include "material.h"

namespace shading
{
    struct shade
    {
        geometry::intersection i;
        materials::material m;
    };

    bool operator< (const struct shade& lhs, const struct shade& rhs)
    {
        return lhs.i < rhs.i;
    }
}
