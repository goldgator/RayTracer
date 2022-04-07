#pragma once
#include "Image.h"
#include "Types.h"
#include "SDL.h"
#include <vector>

class Canvas
{
public:
	Canvas(SDL_Renderer* renderer, int width, int height);
	~Canvas();

	void Update();
	void Draw(SDL_Renderer* renderer);
	void Clear(const glm::vec3& color);
	void DrawPoint(const glm::ivec2& point, const glm::vec3& color);
	void DrawImage(Image& image);

private:
	SDL_Texture* m_texture{ nullptr };
	std::vector<pixel_t> m_buffer;
	int m_width{ 0 };
	int m_height{ 0 };
};
