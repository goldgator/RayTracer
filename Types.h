#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/color_space.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Ray.h"

using pixel_t = std::uint32_t;

inline glm::vec4 PixelToVec4(pixel_t pixel)
{
    glm::vec4 color;

    color.r = (pixel >> 24) / 255.0f;
    color.g = ((pixel >> 16) & 0xff) / 255.0f;
    color.b = ((pixel >> 8) & 0xff) / 255.0f;
    color.a = (pixel & 0xff) / 255.0f;

    return color;
}

inline glm::vec3 PixelToVec3(pixel_t pixel)
{
    glm::vec3 color;

    color.r = (pixel >> 24) / 255.0f;
    color.g = ((pixel >> 16) & 0xff) / 255.0f;
    color.b = ((pixel >> 8) & 0xff) / 255.0f;

    return color;
}

inline pixel_t Vec3ToPixel(const glm::vec3& color)
{
    std::uint8_t r = static_cast<std::uint8_t>(glm::clamp(color.r, 0.0f, 1.0f) * 255);
    std::uint8_t g = static_cast<std::uint8_t>(glm::clamp(color.g, 0.0f, 1.0f) * 255);
    std::uint8_t b = static_cast<std::uint8_t>(glm::clamp(color.b, 0.0f, 1.0f) * 255);
    std::uint8_t a = 0;

    return (r << 24 | g << 16 | b << 8 | a);
}

inline pixel_t Vec4ToPixel(const glm::vec4& color)
{
    std::uint8_t r = static_cast<std::uint8_t>(glm::clamp(color.r, 0.0f, 1.0f) * 255);
    std::uint8_t g = static_cast<std::uint8_t>(glm::clamp(color.g, 0.0f, 1.0f) * 255);
    std::uint8_t b = static_cast<std::uint8_t>(glm::clamp(color.b, 0.0f, 1.0f) * 255);
    std::uint8_t a = static_cast<std::uint8_t>(glm::clamp(color.a, 0.0f, 1.0f) * 255);

    return (r << 24 | g << 16 | b << 8 | a);
}