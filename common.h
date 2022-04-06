#ifndef __COMMON_H__
#define __COMMON_H__

#include <limits>
#include <cstdlib>
#include "color.h"
//constants
const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385f;

//utility
inline float degree_to_radians(float degrees)
{
	return degrees * pi / 180;
}
//random float [0.f,1.f)
inline float random()
{
	return rand() / (RAND_MAX + 1.f);
}

inline float random(float min, float max) {
	// Returns a random real in [min,max).
	return min + (max - min) * random();
}

inline glm::vec3 random3()
{
	return glm::vec3(random(), random(), random());
}
inline glm::vec3 random3(float min, float max)
{
	return glm::vec3(random(min, max), random(min, max), random(min, max));
}

inline Color random_color()
{
	return Color(random(), random(), random(), 1.f);
}

inline Color random_color(float min, float max)
{
	return Color(random(min, max), random(min, max), random(min, max), random(min, max));
}

inline glm::vec3 random_in_unit_sphere()
{
	while (true)
	{
		glm::vec3 point = random3(-1.f, 1.f);
		if (glm::length(point) > 1.f) continue;
		return point;
	}
}

inline float clamp(float x, float min, float max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

inline bool near_zero(glm::vec3& v)
{
	const float delta = 1e-8f;
	float x = glm::abs(v.x);
	float y = glm::abs(v.y);
	float z = glm::abs(v.z);
	return (x < delta) || (y < delta) || (z < delta);
}

inline glm::vec3 reflect(const glm::vec3& ray_in_dir, const glm::vec3& normal)
{
	//reflected ray direction
	glm::vec3 in = ray_in_dir;
	glm::vec3 n = glm::normalize(normal);
	float t = 2 * glm::dot(in, n);
	glm::vec3 out = in -  n*t;

	return out;
}

inline glm::vec3 refract(const glm::vec3& ray_in_dir, const glm::vec3& normal, float refract_proportion)
{
	float cos_theta = glm::dot(-ray_in_dir, normal)/(glm::length(ray_in_dir)*glm::length(normal));

	//refraction direction parts that are perpendicualr to refraction normal
	glm::vec3 r_ortho = refract_proportion*(ray_in_dir+cos_theta*normal);
	//refraction direciton parts that are parellel to refraction normal
	glm::vec3 r_para = -glm::sqrt(glm::abs(1.f - (r_ortho.length() * r_ortho.length()))) * normal;
	return r_ortho + r_para;
}



#endif //__COMMON_H__