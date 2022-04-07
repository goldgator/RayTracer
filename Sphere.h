#pragma once
#include "Types.h"
#include "Geometry.h"


class Sphere : public Geometry {
public:
	Sphere() {}
	Sphere(const glm::vec3& center, float radius, Material* material) : m_center(center), m_radius(radius), Geometry{material} {}

	bool Hit(const ray& r, float tMin, float tMax, raycastHit& hit) override;



private:
	glm::vec3 m_center{ 0,0,0 };
	float m_radius = 1;
};