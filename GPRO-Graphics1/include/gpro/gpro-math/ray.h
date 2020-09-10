#ifndef RAY_H
#define RAY_H

#include "gpro/gpro-math/gproVector.h"

class ray {
public:
    ray() {}
    ray(const vec3& origin, const vec3& direction)
        : orig(origin), dir(direction)
    {}

    vec3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    vec3 at(float t) const {
        return orig + t * dir;
    }

public:
    vec3 orig;
    vec3 dir;
};

#endif // !RAY_H