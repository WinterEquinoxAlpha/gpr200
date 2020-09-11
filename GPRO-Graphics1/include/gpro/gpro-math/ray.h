/*
    ray.h
    Class creation for ray class; Container for vec3s and at() function

    Original code: Peter Shirley (2020) "Ray Tracing in One Weekend" (Version 3.2.0) [Source Code]. https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class/variablesandmethods
    Modified by: Michael Kashian (2020)
*/

#ifndef RAY_H
#define RAY_H

#include "gpro/gpro-math/gproVector.h"

// Original Code: Peter Shirley (2020) "Ray Tracing in One Weekend"
// Modified by: Michael Kashian
class ray {
public:
    ray() {}    // Default constructor
    ray(const vec3& origin, const vec3& direction) : orig(origin), dir(direction){} // Constructor with two vec3 parameters

    vec3 origin() const { return orig; }    // Returns orig
    vec3 direction() const { return dir; }  // Returns dir

    // Calculates point on the vector at a given t
    // Original Code: Peter Shirley (2020) "Ray Tracing in One Weekend"
    // Modified by: Michael Kashian
    vec3 at(float t) const {
        return orig + t * dir;
    }

public:
    vec3 orig;
    vec3 dir;
};

#endif // !RAY_H