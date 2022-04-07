#include "Image.h"
#include "SDL.h"

Image::Image(int width, int height)
{
    this->m_width = width;
    this->m_height = height;

    int imageSize = width * height;

    m_buffer.resize(imageSize);
}

void Image::Clear(const glm::vec3& color)
{
    std::fill(m_buffer.begin(), m_buffer.end(), Vec3ToPixel(color));
}

void Image::SetPoint(const glm::ivec2& point, const glm::vec3& color)
{
    if (point.x < 0 || point.x >= m_width || point.y < 0 || point.y >= m_height) return;

    m_buffer[point.x + (point.y * m_width)] = Vec3ToPixel(color);
}
