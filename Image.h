#pragma once
#include "Types.h"
#include <vector>

class Image
{
public:
	Image(int width, int height);

	void Clear(const glm::vec3& color);
	void SetPoint(const glm::ivec2& point, const glm::vec3& color);

	int width() { return m_width; }
	int height() { return m_height; }

	std::vector<pixel_t>& buffer() { return m_buffer; }

private:
	int m_width{ 0 };
	int m_height{ 0 };

	std::vector<pixel_t> m_buffer;
};
