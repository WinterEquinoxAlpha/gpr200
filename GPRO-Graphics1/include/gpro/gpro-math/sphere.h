/*
    sphere.h
    Class creation for shpere class; Shere object which interacts with rays to display on the screen

    Original code: Peter Shirley (2020) "Ray Tracing in One Weekend" (Version 3.2.0) [Source Code]. https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class/variablesandmethods
    Modified by: Michael Kashian (2020)
*/

#ifndef SPHERE_H
#define SPHERE_H

#include "gpro/gpro-math/hittable.h"
#include "gpro/gpro-math/gproVector.h"

// Original Code: Peter Shirley (2020) "Ray Tracing in One Weekend"
// Modified by: Michael Kashian
class sphere : public hittable {
public:
    sphere() {} // Default constructor
    sphere(vec3 cen, float r) : center(cen), radius(r) {};  // Constructor with vec3 and float parameters

    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;     // Determines if the ray hits the object

public:
    vec3 center;
    float radius;
};

// hit function implementation
// Original Code: Peter Shirley (2020) "Ray Tracing in One Weekend"
// Modified by: Michael Kashian
bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    float a = r.direction().length_squared(r.direction());
    float half_b = dot(oc, r.direction());
    float c = oc.length_squared(oc) - radius * radius;
    float discriminant = half_b * half_b - a * c;

    // Determines how the ray intersects with the object using an outwards normal
    if (discriminant > 0) {
        float root = sqrt(discriminant);

        // If the ray is in the sphere, return true and update rec
        float temp = (-half_b - root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            return true;
        }

        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            return true;
        }
    }
    return false;
}
#endif