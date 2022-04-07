#pragma once
#include "Types.h"
#include <stdlib.h>
#include <algorithm>

inline float random01() {
	return rand() / (float) RAND_MAX;
}

inline float random(float min, float max) {
	if (min > max) std::swap(min, max);
	return min + ((max - min) * random01());
}

inline glm::vec3 randomInUnitSphere() {
	glm::vec3 p;
	do {
		p = glm::vec3{ random(-1,1), random(-1,1), random(-1,1) };
	} while (glm::length2(p) >= 1.0f);

	return p;
}

inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n) {
	return v - ((n * glm::dot(v, n)) * 2.0f);
}

inline bool refract(const glm::vec3& v, const glm::vec3& n, float index, glm::vec3& refracted)
{
	glm::vec3 nv = glm::normalize(v);
	float dt = dot(nv, n);
	float discriminant = 1 - (index * index) * (1 - dt * dt);
	if (discriminant > 0)
	{
		refracted = index * (nv - (n * dt)) - (n * std::sqrt(discriminant));
		return true;
	}
	return false;
}

inline float schlick(float cosine, float index)
{
	float r0 = (1 - index) / (1 + index);
	r0 = r0 * r0;
	return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}