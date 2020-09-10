/*
   Copyright 2020 Daniel S. Buckstein

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

/*
	GPRO-Graphics1-TestConsole-main.c/.cpp
	Main entry point source file for a Windows console application.

	Modified by: Michael Kashian
	Modified because: Lab 1

	Credit for code basis: Daniel Buckstein
	Credit for code basis: Peter Shirley (2020) "Ray Tracing in One Weekend" (Version 3.2.0) [Source Code]. https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class/variablesandmethods
*/


#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "gpro/gpro-math/gproVector.h"
#include "gpro/gpro-math/ray.h"
#include "gpro/gpro-math/rtweekend.h"
#include "gpro/gpro-math/hittable_list.h"
#include "gpro/gpro-math/sphere.h"

void testVector()
{
	// test array vector initializers and functions
	float3 av, bv, cv, dv;
	vec3default(av);								// -> a = (0, 0, 0)
	vec3init(bv, 1.0f, 2.0f, 3.0f);					// -> b = (1, 2, 3)
	vec3copy(dv, vec3init(cv, 4.0f, 5.0f, 6.0f));	// -> d = c = (4, 5, 6)
	vec3copy(av, dv);								// a = d			-> a = (4, 5, 6)
	vec3add(dv, bv);								// d += b			-> d = (4 + 1, 5 + 2, 6 + 3) = (5, 7, 9)
	vec3sum(dv, bv, bv);							// d = b + b		-> d = (1 + 1, 2 + 2, 3 + 3) = (2, 4, 6)
	vec3add(vec3sum(dv, cv, bv), av);				// d = c + b + a	-> d = (4 + 1 + 4, 5 + 2 + 5, 6 + 3 + 6) = (9, 12, 15)

#ifdef __cplusplus
	// test all constructors and operators
	vec3 a, b(1.0f, 2.0f, 3.0f), c(cv), d(c);		// default; init; copy array; copy
	a = d;											// assign						-> a = (4, 5, 6)
	d += b;											// add assign					-> d = (5, 7, 9)
	d = b + b;										// sum, init, assign			-> d = (2, 4, 6)
	d = c + b + a;									// sum, init, sum, init, assign	-> d = (9, 12, 15)
#endif	// __cplusplus

	vec3 test;
	vec3init(test.v, 1.0f, 2.0f, 3.0f);
	//printf("%f \n", test.x);
}

#ifdef __cplusplus
// For opening and writing to a file in C++
#include <string>
#include <fstream>
#else //!__cplusplus
// For opening and writing to a file in C
#include <stdio.h>
#endif //__cplusplus

// Writes out each pixel color to the given outstream
void write_color(std::ostream& out, vec3 pixel_color) {
	out << static_cast<int>(255.999 * pixel_color.x) << ' '
		<< static_cast<int>(255.999 * pixel_color.y) << ' '
		<< static_cast<int>(255.999 * pixel_color.z) << '\n';
}

// Determines if and how many times a ray intersects with a sphere
float hit_sphere(const vec3& center, float radius, const ray& r) {
	vec3 oc = r.origin() - center;
	float a = r.direction().length_squared(r.direction());
	float half_b = dot(oc, r.direction());
	float c = oc.length_squared(oc) - radius * radius;
	float discriminant = half_b * half_b - a * c;

	if (discriminant < 0) {
		return -1.0f;	// If it does not hit, return 0
	}
	else {
		return (-half_b - sqrt(discriminant)) / a;	// If it does hit, return the number of hits
	}
}

// Determines the color of the pixel given the ray's intersectors
vec3 ray_color(const ray& r, const hittable& world) {
	hit_record rec;
	if (world.hit(r, 0, infinity, rec)) {
		return 0.5f * (rec.normal + vec3(1.0f, 1.0f, 1.0f));
	}
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y + 1.0f);
	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

// main function
int main(int const argc, char const* const argv[])
{
	//testVector();

	#ifdef __cplusplus

	// Image
	const float aspect_ratio = 16.0f / 9.0f;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	//World
	hittable_list world;
	// Adding the objects to the scene
	world.add(make_shared<sphere>(vec3(0.0f, 0.0f, -1.0f), 0.5f));
	world.add(make_shared<sphere>(vec3(0.0f, -100.5f, -1.0f), 100.0f));

	// Camera
	float viewport_height = 2.0f;
	float viewport_width = aspect_ratio * viewport_height;
	float focal_length = 1.0f;

	vec3 origin = vec3(0.0f, 0.0f, 0.0f);
	vec3 horizontal = vec3(viewport_width, 0.0f, 0.0f);
	vec3 vertical = vec3(0.0f, viewport_height, 0.0f);
	vec3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0.0f, 0.0f, focal_length);

	// Render
	// Opens the output file and writes the header
	std::ofstream outfile("image.ppm");
	outfile << "P3\n" << image_width << " " << image_height << "\n255\n";

	// Loops through evey pixel in the image, determiens their color, and writes them to the file
	for (int j = image_height - 1; j >= 0; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; i++)
		{
			float u = float(i) / (image_width - 1);
			float v = float(j) / (image_height - 1);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 pixel_color = ray_color(r, world);
			write_color(outfile, pixel_color);
		}
	}
	// Closes file
	outfile.close();
	
	#else //!__cplusplus
	FILE* file = fopen("op.txt", "w");
	if (file) {
		char* test = "hello";
		fprintf(file, "%s\n", test);
		close(file);
	}

	#endif //__cplusplus
}