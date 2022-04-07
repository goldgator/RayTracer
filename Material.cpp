#include "Material.h"
#include "Math.h"

bool Lambertian::Scatter(const ray& r, const raycastHit& hit, glm::vec3& attenuation, ray& scattered) const
{
    glm::vec3 target = hit.point + hit.normal + randomInUnitSphere();
    glm::vec3 direction = glm::normalize(target - hit.point);

    scattered = ray{ hit.point, direction };
    attenuation = m_albedo;

    return true;
}

bool Metal::Scatter(const ray& r, const raycastHit& hit, glm::vec3& attenuation, ray& scattered) const
{
    glm::vec3 reflected = reflect(glm::normalize(r.direction),hit.normal);
    //scattered = ray{ hit.point, reflected + m_fuzz * randomInUnitSphere() };
    scattered.origin = hit.point;
    scattered.direction = reflected + m_fuzz * randomInUnitSphere();

    attenuation = m_albedo;
    return (glm::dot(scattered.direction, hit.normal) > 0);
    //return true;
}

bool Dielectric::Scatter(const ray& r, const raycastHit& hit, glm::vec3& attenuation, ray& scattered) const
{
    glm::vec3 outNormal;
    glm::vec3 reflected = reflect(glm::normalize(r.direction), hit.normal);

    attenuation = m_albedo;

    glm::vec3 refracted;
    float reflectProbability = 1.0f;
    float cosine;
    float niOverNt;

    if (glm::dot(r.direction, hit.normal) > 0) {
        //hits inside of surface
        outNormal = -hit.normal;
        niOverNt = m_index;
        cosine = m_index * glm::dot(r.direction, hit.normal) / r.direction.length();
    }
    else {
        //ray hits outside of surface
        outNormal = hit.normal;
        niOverNt = 1.0f / m_index;
        cosine = -glm::dot(r.direction, hit.normal) / r.direction.length();
    }

    if (refract(r.direction, outNormal, niOverNt, refracted)) {
        reflectProbability = schlick(cosine, m_index);
    }

    scattered = (random01() < reflectProbability) ? ray{ hit.point, reflected } : ray{ hit.point, refracted };
    return true;
}
