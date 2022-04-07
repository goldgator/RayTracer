#include "Canvas.h"

Canvas::Canvas(SDL_Renderer* renderer, int width, int height)
{
    m_width = width;
    m_height = height;

    m_texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
        width, height);

    m_buffer.resize(width * height);
}

Canvas::~Canvas()
{
    SDL_DestroyTexture(m_texture);
}

void Canvas::Update()
{
    SDL_UpdateTexture(m_texture, nullptr, m_buffer.data(), m_width * sizeof(pixel_t));
}

void Canvas::Draw(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, m_texture, nullptr, nullptr);
}

void Canvas::Clear(const glm::vec3& color)
{
    std::fill(m_buffer.begin(), m_buffer.end(), Vec3ToPixel(color));
}

void Canvas::DrawPoint(const glm::ivec2& point, const glm::vec3& color)
{
    if (point.x < 0 || point.x >= m_width || point.y < 0 || point.y >= m_height) return;

    m_buffer[point.x + (point.y * m_width)] = Vec3ToPixel(color);

}

void Canvas::DrawImage(Image& image)
{
    std::copy(image.buffer().begin(), image.buffer().end(), m_buffer.begin());
}
