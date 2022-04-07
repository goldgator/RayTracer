#include "Plane.h"

bool Plane::Hit(const ray& r, float tMin, float tMax, raycastHit& hit)
{
    float denominator = glm::dot(r.direction, m_normal);

    if (abs(denominator) < std::numeric_limits<float>::epsilon()) {
        return false;
    }


    float t = glm::dot(m_center - r.origin, m_normal) / denominator;

    if (t < 0) {
        //hits the backside of the plane, false
        return false;
    }
    else if (t > tMin && t < tMax) {
        //hits the front of the plane
        hit.t = t;
        hit.point = r.pointAt(t);
        hit.normal = m_normal;
        hit.material = m_material;
        return true;
    }


    return false;
}
