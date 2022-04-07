#pragma once
#include "Types.h"

class Camera
{
public:
	Camera(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up, float vfov, class Image* image);

	glm::vec2 ScreenToViewport(const glm::vec2& screen);
	ray ViewportToRay(const glm::vec2& viewport);

public:
	glm::vec3 m_eye = glm::vec3{ 0, 0, 0 };

	glm::vec3 m_right = glm::vec3{ 0, 0, 0 };
	glm::vec3 m_up = glm::vec3{ 0, 0, 0 };
	glm::vec3 m_forward = glm::vec3{ 0, 0, 0 };

	glm::vec3 m_lowerLeft = glm::vec3{ 0, 0, 0 };
	glm::vec3 m_horizontal = glm::vec3{ 0, 0, 0 };
	glm::vec3 m_vertical = glm::vec3{ 0, 0, 0 };

	class Image* m_image{ nullptr };
};

