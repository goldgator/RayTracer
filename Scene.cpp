#include "Scene.h"
#include "Geometry.h"
#include "Math.h"
#include "Material.h"

glm::vec3 Scene::Trace(const ray& r, float tMin, float tMax, raycastHit& hit)
{
    bool rayHit = false;

    float tClosest = tMax;

    for (auto object : m_objects) {
        if (object->Hit(r, tMin, tClosest, hit)) {
            rayHit = true;
            tClosest = hit.t;
        }
    }

    if (rayHit) {
        ray scattered;
        glm::vec3 attenuation;

        if (hit.material->Scatter(r, hit, attenuation, scattered)) {
            return attenuation * Trace(scattered, tMin, tMax, hit);
        }
        else {
            return { 0,0,0 };
        }
        
        
    }
    else {
        glm::vec3 direction = glm::normalize(r.direction);
        float t = (direction.y * 0.5f);
        return glm::lerp(glm::vec3(0.5f, 0.7f, 1.0f), glm::vec3(1, 1, 1), t);

    }
    
}

void Scene::Add(Geometry* geometry)
{
    m_objects.push_back(geometry);
}
