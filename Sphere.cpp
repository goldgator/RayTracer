#include "Sphere.h"
#include "Math.h"

bool Sphere::Hit(const ray& r, float tMin, float tMax, raycastHit& hit)
{
    glm::vec3 oc = r.origin - m_center;
    float a = glm::dot(r.direction, r.direction);
    float b = 2 * glm::dot(r.direction, oc);
    float c = glm::dot(oc, oc) - (m_radius * m_radius);

    //b^2 - 4ac
    float discriminant = (b * b) - 4 * a * c;


    if (discriminant >= 0) {
        float t = (-b - sqrt(discriminant)) / (2.0f * a);
        if (t > tMin && t < tMax) {
            hit.t = t;
            hit.point = r.pointAt(t);
            hit.normal = hit.point - m_center / m_radius;
            hit.material = m_material;
            return true;
        }

        t = (-b + sqrt(discriminant)) / (2.0f * a);
        if (t > tMin && t < tMax) {
            hit.t = t;
            hit.point = r.pointAt(t);
            hit.normal = hit.point - m_center / m_radius;
            hit.material = m_material;
            return true;
        }
    }


    return false;



}
