#include "Camera.h"
#include "Image.h"

Camera::Camera(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up, float vfov, Image* image)
{
	m_image = image;
	float aspectRatio = m_image->width() / (float) m_image->height();

	float theta = glm::radians(vfov);
	float h = tan(theta * 0.5f);

	float viewportHeight = h * 2.0f;
	float viewportWidth = aspectRatio * viewportHeight;

	m_forward = glm::normalize(eye - lookAt);
	m_right = glm::normalize(glm::cross(up, m_forward));
	m_up = glm::cross(m_forward, m_right);

	m_eye = eye;

	m_horizontal = viewportWidth * m_right;
	m_vertical = viewportHeight * m_up;

	m_lowerLeft = m_eye - (m_horizontal * 0.5f) - (m_vertical * 0.5f) - m_forward;

}

glm::vec2 Camera::ScreenToViewport(const glm::vec2& screen)
{
	glm::vec2 viewport;
	viewport.x = screen.x / m_image->width();
	viewport.y = screen.y / m_image->height();

	return viewport;
}

ray Camera::ViewportToRay(const glm::vec2& viewport)
{
	ray r;
	r.origin = m_eye;
	r.direction = m_lowerLeft + (viewport.x * m_horizontal) + (viewport.y * m_vertical) - m_eye;

	return r;
}
