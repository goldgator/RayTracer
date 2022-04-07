#pragma once

#include "Types.h"
#include <vector>

class Geometry;

class Scene {
public:
	glm::vec3 Trace(const ray& r, float tMin, float tMax, raycastHit& hit);
	void Add(Geometry* geometry);

protected:
	std::vector<Geometry*> m_objects;


};
