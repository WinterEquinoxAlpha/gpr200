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
	gproVector.h
	Interface for vectors. Sets an example for C and C++ compatible headers.

	Modified by: Michael Kashian
	Modified because: Lab 1

	Credit for code basis: Daniel Buckstein
	Credit for code basis: Peter Shirley (2020) "Ray Tracing in One Weekend" (Version 3.2.0) [Source Code]. https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class/variablesandmethods
*/

#ifdef _GPRO_VECTOR_H_
#ifndef _GPRO_VECTOR_INL_
#define _GPRO_VECTOR_INL_


#ifdef __cplusplus

inline vec3::vec3()
	: x(0.0f), y(0.0f), z(0.0f)
{
}
inline vec3::vec3(float const xc, float const yc, float const zc)
	: x(xc), y(yc), z(zc)
{
}
inline vec3::vec3(float3 const vc)
	: x(vc[0]), y(vc[1]), z(vc[2])
{
}
inline vec3::vec3(vec3 const& rh)
	: x(rh.x), y(rh.y), z(rh.z)
{
}

inline vec3& vec3::operator =(vec3 const& rh)
{
	x = rh.x;
	y = rh.y;
	z = rh.z;
	return *this;
}

inline vec3& vec3::operator +=(vec3 const& rh)
{
	x += rh.x;
	y += rh.y;
	z += rh.z;
	return *this;
}

inline vec3 const vec3::operator +(vec3 const& rh) const
{
	return vec3((x + rh.x), (y + rh.y), (z + rh.z));
}

inline vec3& vec3::operator -=(vec3 const& rh)
{
	x -= rh.x;
	y -= rh.y;
	z -= rh.z;
	return *this;
}

inline vec3 const vec3::operator -(vec3 const& rh) const
{
	return vec3((x - rh.x), (y - rh.y), (z - rh.z));
}

// Multiplication of two vec3s
// Original Code: Peter Shirley (2020) "Ray Tracing in One Weekend"
// Modified by: Michael Kashian
inline vec3 operator *(const vec3& lh, const vec3& rh)
{
	return vec3(lh.x * rh.x, lh.y * rh.y, lh.z * rh.z);
}

// Multiplication of a constant and a vec3
// Original Code: Peter Shirley (2020) "Ray Tracing in One Weekend"
// Modified by: Michael Kashian
inline vec3 operator *(float lh, const vec3& rh)
{
	return vec3(lh * rh.x, lh * rh.y, lh * rh.z);
}

// Multiplication of a constant and a vec3 but in reverse order
// Original Code: Peter Shirley (2020) "Ray Tracing in One Weekend"
// Modified by: Michael Kashian
inline vec3 operator *(const vec3& lh, float rh)
{
	return rh * lh;
}

inline vec3& vec3::operator *=(const float t)
{
	x *= t;
	y *= t;
	z *= t;
	return *this;
}

inline vec3& vec3::operator /=(const float t)
{
	return *this *= 1 / t;
}

// division operator (get quotient of this and another)
// Original Code: Peter Shirley (2020) "Ray Tracing in One Weekend"
// Modified by: Michael Kashian
inline vec3 operator /(vec3 v, float t) {
	return (1 / t) * v;
}

// Caluclates the unit vector for a given vec3
// Original Code: Peter Shirley (2020) "Ray Tracing in One Weekend"
// Modified by: Michael Kashian
inline vec3 unit_vector(vec3 v)
{
	return v / v.length(v);
}

// Calculates the dot produce for a given vec3
// Original Code: Peter Shirley (2020) "Ray Tracing in One Weekend"
// Modified by: Michael Kashian
inline float dot(const vec3& lh, const vec3& rh) {
	return lh.x * rh.x
		+ lh.y * rh.y
		+ lh.z * rh.z;
}

// Calculates the cross produce for a given vec3
// Original Code: Peter Shirley (2020) "Ray Tracing in One Weekend"
// Modified by: Michael Kashian
inline vec3 cross(const vec3& rh, const vec3& lh) {
	return vec3(lh.y * rh.z - rh.z * lh.y,
		lh.z * rh.x - lh.x * rh.z,
		lh.x * rh.y - lh.y * rh.x);
}

#endif	// __cplusplus


inline floatv vec3default(float3 v_out)
{
	v_out[0] = v_out[1] = v_out[2] = 0.0f;
	return v_out;
}
inline floatv vec3init(float3 v_out, float const xc, float const yc, float const zc)
{
	v_out[0] = xc;
	v_out[1] = yc;
	v_out[2] = zc;
	return v_out;
}
inline floatv vec3copy(float3 v_out, float3 const v_rh)
{
	v_out[0] = v_rh[0];
	v_out[1] = v_rh[1];
	v_out[2] = v_rh[2];
	return v_out;
}

inline floatv vec3add(float3 v_lh_sum, float3 const v_rh)
{
	v_lh_sum[0] += v_rh[0];
	v_lh_sum[1] += v_rh[1];
	v_lh_sum[2] += v_rh[2];
	return v_lh_sum;
}

inline floatv vec3sum(float3 v_sum, float3 const v_lh, float3 const v_rh)
{
	return vec3init(v_sum, (v_lh[0] + v_rh[0]), (v_lh[1] + v_rh[1]), (v_lh[2] + v_rh[2]));
}


#endif	// !_GPRO_VECTOR_INL_
#endif	// _GPRO_VECTOR_H_