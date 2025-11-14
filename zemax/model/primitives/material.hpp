#pragma once

#include "gfx/core/color.hpp"

namespace zemax {
namespace model {

struct Material
{
    Material( const gfx::core::Color& color_ ) : color( color_ ) {}
    Material( const gfx::core::Color& color_, float reflection_factor_ )
        : color( color_ ), reflection_factor( reflection_factor_ )
    {
    }
    Material( const gfx::core::Color& color_,
              float                   reflection_factor_,
              float                   refraction_factor_,
              float                   refraction_eta_ )
        : color( color_ ),
          reflection_factor( reflection_factor_ ),
          refraction_factor( refraction_factor_ ),
          refraction_eta( refraction_eta_ )
    {
    }

    gfx::core::Color color             = gfx::core::Color::Transparent;
    float            refraction_factor = 0.0F;
    float            refraction_eta    = 0.0F;
    float            reflection_factor = 0.0F;
    bool             painted           = false;
};

} // namespace model
} // namespace zemax
