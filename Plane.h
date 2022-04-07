#pragma once
#include "Geometry.h"

class Plane : public Geometry {
public:
	Plane(const glm::vec3& center, const glm::vec3& normal, Material* material) :
		Geometry{material},
		m_center{ center },
		m_normal{ normal } {}

	bool Hit(const ray& r, float tMin, float tMax, raycastHit& hit) override;


private:
	glm::vec3 m_center{ 0,0,0 };
	glm::vec3 m_normal{ 0,0,0 };
};