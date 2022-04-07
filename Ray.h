#pragma once
#include "Types.h"

struct raycastHit {
	float t{ 0 };
	glm::vec3 point{ 0,0,0 };
	glm::vec3 normal{ 0,0,0 };

	class Material* material{ nullptr };
};


struct ray
{
	glm::vec3 origin{ 0, 0, 0 };
	glm::vec3 direction{ 0, 0, 0 };

	ray() {}
	ray(const glm::vec3& origin, const glm::vec3& direction) : 
		origin(origin), direction(direction) {}
	glm::vec3 pointAt(float t) const { return origin + (t * direction); }
};