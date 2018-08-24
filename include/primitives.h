#pragma once

#include <vector>
#include <set>

#include "ray.h"


namespace mathy
{
    struct sphere
    {
        vec3 center;
        float radius;
    };

    using spheres = std::vector<sphere>;

    struct intersection
    {
        float t;
        vec3  p;
        vec3  normal;
    };

    bool operator< (const struct intersection& lhs, const struct intersection& rhs)
    {
        return lhs.t < rhs.t;
    }

    using intersections = std::set<intersection>;

    intersection intersect(const sphere& s, const ray& r)
    {
        vec3 oc = r.o - s.center;

        float a = length_squared(r.d);
        float b = 2.0f * dot(oc, r.d);
        float c = length_squared(oc) - (s.radius * s.radius);

        float disc = (b * b) - (4.0f * a * c);

        intersection record;

        record.t      = disc < 0.0f ? -1.0f : (-b - sqrt(disc)) / (2.0f * a);
        record.p      = at(r, record.t);
        record.normal = normalize(record.p - s.center);

        return record;
    }

    intersections intersect(const spheres& ss, const ray& r)
    {
        intersections is;

        for(auto&& s : ss)
        {
            auto i = intersect(s, r);

            if (i.t > 0.0f)
            {
                is.insert(i);
            }
        }

        return is;
    }

    inline bool hit_sphere(const sphere& s, const ray& r)
    {
        return intersect(s, r).t > 0;
    }

}
