#pragma once

#include "gfx/core/color.hpp"

namespace zemax {
namespace model {

struct Material
{
    Material( const gfx::core::Color& color ) : color( color ) {}
    Material( const gfx::core::Color& color, float reflection_factor )
        : color( color ), reflection_factor( reflection_factor )
    {
    }

    gfx::core::Color color             = gfx::core::Color::Transparent;
    float            refraction_factor = 0.0F;
    float            reflection_factor = 0.0F;
};

} // namespace model
} // namespace zemax
