#pragma once

#include <vector>
#include <set>

#include "ray.h"
#include "intersection.h"
#include "material.h"
#include "shading.h"

namespace mathy
{
    struct sphere
    {
        vec3 center;
        float radius;

        materials::material m;
    };

    using spheres = std::vector<sphere>;

    shading::shade intersect(const sphere& s, const ray& r)
    {
        vec3 oc = r.o - s.center;

        float a = length_squared(r.d);
        float b = 2.0f * dot(oc, r.d);
        float c = length_squared(oc) - (s.radius * s.radius);

        float disc = (b * b) - (4.0f * a * c);

        geometry::intersection record;

        record.t      = disc < 0.0f ? -1.0f : (-b - sqrt(disc)) / (2.0f * a);
        record.p      = at(r, record.t);
        record.normal = normalize(record.p - s.center);

        return { record, s.m };
    }

    inline bool hit_sphere(const sphere& s, const ray& r)
    {
        return intersect(s, r).i.t > 0;
    }

    using intersections = std::set<shading::shade>;

    using primitive  = std::function<shading::shade(const ray&)>;
    using primitives = std::vector<primitive>;

    primitive make_sphere_primitive(const sphere& s)
    {
        return [=](const ray& r) { return intersect(s, r); };
    }

    intersections intersect(const primitives& ps, const ray& r)
    {
        intersections is;

        for(auto&& p : ps)
        {
            auto s = p(r);

            if (s.i.t > 0.0f)
            {
                is.insert(s);
            }
        }

        return is;
    }

}
