#pragma once

#include <iostream>
#include <cassert>
#include <cmath>
#include <algorithm>

namespace mathy
{
    struct xyz
    {
        float x, y, z;
    };

    struct rgb
    {
        float r, g, b;
    };

    using vec3 = xyz;

    inline vec3 operator+ (const vec3& a, const vec3& b)
    {
        return { a.x + b.x, a.y + b.y, a.z + b.z };
    }

    inline vec3 operator- (const vec3& a, const vec3& b)
    {
        return { a.x - b.x, a.y - b.y, a.z - b.z };
    }

    inline vec3 operator* (float s, const vec3& a)
    {
        return { s * a.x, s * a.y, s * a.z };
    }

    inline vec3 cross(const vec3& a, const vec3& b)
    {
        return {(a.y * b.z) - (a.z * b.y),
                (a.z * b.x) - (a.x * b.z),
                (a.x * b.y) - (a.y * b.x)};
    }

    inline float dot(const vec3& a, const vec3& b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    inline float length_squared(const vec3& a)
    {
        return dot(a, a);
    }

    inline float length(const vec3& a)
    {
        return std::sqrt(length_squared(a));
    }

    inline vec3 normalize(const vec3& a)
    {
        assert(length(a) != 0.0);

        float s = 1.0 / length(a);
        return s * a;
    }

    inline std::istream& operator>> (std::istream &is, vec3 &a)
    {
        is >> a.x;
        is >> a.y;
        is >> a.z;

        return is;
    }

    inline std::ostream& operator<< (std::ostream &os, const vec3& a)
    {
        os << a.x << " ";
        os << a.y << " ";
        os << a.z << "\n";

        return os;
    }
}
