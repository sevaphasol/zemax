#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/vector3.hpp"
#include <sys/types.h>

namespace config {

struct Common
{
    struct Font
    {
        static constexpr const char* const   Name  = "assets/JetBrainsMono-Regular.ttf";
        static inline const gfx::core::Color Color = gfx::core::Color::White;
    };
};

struct Window
{
    static constexpr uint              Width  = 1300.0f;
    static constexpr uint              Height = 900.0f;
    static constexpr const char* const Title  = "Zemax";
};

struct Zemax
{
    static constexpr gfx::core::Vector2f WidgetPosition  = { 50.0f, 50.0f };
    static constexpr gfx::core::Vector2f WidgetSize      = { 1200.0f, 800.0f };
    static constexpr gfx::core::Color    BackgroundColor = { 16, 16, 16 };
    static constexpr gfx::core::Vector3f CameraPos       = { 0, 0, 0 };
    static constexpr float               MoveScale       = 0.1f;
    static constexpr float               RotateScale     = 0.04f;
};

} // namespace config
