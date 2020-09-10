/*
    hittable.h
    Class creation for hittable class and struct hit_record; Object that interacts with rays to display on the screen

    Original code: Peter Shirley (2020) "Ray Tracing in One Weekend" (Version 3.2.0) [Source Code]. https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class/variablesandmethods
    Modified by: Michael Kashian (2020)
*/

#ifndef HITTABLE_H
#define HITTABLE_H

#include "gpro/gpro-math/ray.h"

struct hit_record {
    vec3 p;
    vec3 normal;
    float t;
    bool front_face;

    // Forces the normal to point a specific direction (outwards)
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -1*outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;    // Determines if the ray hits the object
};

#endif