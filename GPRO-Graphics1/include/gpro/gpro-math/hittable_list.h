/*
    hittable_list.h
    Class creation for hittable_list class; List of hittable objects

    Original code: Peter Shirley (2020) "Ray Tracing in One Weekend" (Version 3.2.0) [Source Code]. https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class/variablesandmethods
    Modified by: Michael Kashian (2020)
*/

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "gpro/gpro-math/hittable.h"
#include <memory>
#include <vector>

// Prevents having to put std:: in front of all the things
// Original Code: Peter Shirley (2020) "Ray Tracing in One Weekend"
// Modified by: Michael Kashian
using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
public:
    hittable_list() {}  // Default constructor
    hittable_list(shared_ptr<hittable> object) { add(object); } // Constructor with vector parameter

    void clear() { objects.clear(); }   // Clears the objects vector
    void add(shared_ptr<hittable> object) { objects.push_back(object); }    // Adds an object to the objects vector

    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;     // Determines if the ray hits the object

public:
    std::vector<shared_ptr<hittable>> objects;  // The objects vector
};

// hit function implementation
// Original Code: Peter Shirley (2020) "Ray Tracing in One Weekend"
// Modified by: Michael Kashian
bool hittable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = t_max;

    // Loops through each object and, given the ray, determines if it hits and object and what object it is
    for (int i = 0; i < objects.size(); i++) {
        const shared_ptr<hittable>& object = objects[i];
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}
#endif