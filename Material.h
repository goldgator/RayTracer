#pragma once
#include "Ray.h"


class Material {
public:
	virtual bool Scatter(const ray& r, const raycastHit& hit, glm::vec3& attenuation, ray& scattered) const = 0;

};

class Lambertian : public Material {
public:
	Lambertian(const glm::vec3& albedo) : m_albedo{ albedo } {}
	virtual bool Scatter(const ray& r, const raycastHit& hit, glm::vec3& attenuation, ray& scattered) const override;


	glm::vec3 m_albedo;
};

class Metal : public Material {
public:
	Metal(const glm::vec3& albedo, float fuzz) : m_albedo{ albedo }, m_fuzz(fuzz){}

	virtual bool Scatter(const ray& r, const raycastHit& hit, glm::vec3& attenuation, ray& scattered) const override;

public:
	glm::vec3 m_albedo{ 0,0,0 };
	float m_fuzz = 0;
};

class Dielectric : public Material {
public:
	Dielectric(const glm::vec3& albedo, float index) : m_albedo{albedo}, m_index(index) {}
	virtual bool Scatter(const ray& r, const raycastHit& hit, glm::vec3& attenuation, ray& scattered) const override;


protected:
	glm::vec3 m_albedo{ 1,1,1 };
	float m_index{ 1 };
};