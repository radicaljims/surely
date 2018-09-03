#pragma once

#include "vec3.h"
#include "ray.h"
#include "intersection.h"

namespace materials
{
    struct material_interaction
    {
        bool valid = false;
        mathy::vec3 attenuation;
        mathy::ray  scattered;
    };

    using material = std::function<material_interaction(const mathy::ray& r,
                                                        const geometry::intersection& i)>;

    material make_empty_material(const mathy::vec3& albedo)
    {
        return [=](const mathy::ray& r, const geometry::intersection& i)
        {
            mathy::vec3 attenuation;
            mathy::ray scattered;
            material_interaction empty = { false, attenuation, scattered };

            return empty;
        };
    }

    material make_lambertian_material(const mathy::vec3& albedo)
    {
        return [=](const mathy::ray& r, const geometry::intersection& i)
        {
            mathy::vec3 target = i.p + i.normal + mathy::point_on_sphere();

            mathy::ray scattered = { i.p, target - i.p };

            material_interaction mat = { true, albedo, scattered };

            return mat;
        };
    }

    material make_metal_material(const mathy::vec3& albedo)
    {
        return [=] (const mathy::ray& r, const geometry::intersection& i)
        {
            mathy::vec3 reflected = mathy::reflect(normalize(r.d), i.normal);

            mathy::ray scattered = { i.p, reflected };

            material_interaction mat = { dot(scattered.d, i.normal) > 0, albedo, scattered };

            return mat;
        };
    }
}
