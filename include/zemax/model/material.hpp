#pragma once

#include "gfx/core/color.hpp"

namespace zemax {
namespace model {

struct Material
{
    Material( const gfx::core::Color& color ) : color( color ) {}
    Material( const gfx::core::Color& color, float reflective_factor )
        : color( color ), reflective_factor( reflective_factor )
    {
    }

    gfx::core::Color color             = gfx::core::Color::Transparent;
    float            refractive_factor = 0.0F;
    float            reflective_factor = 0.0F;
};

} // namespace model
} // namespace zemax
