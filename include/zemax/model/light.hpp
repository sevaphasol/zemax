#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/vector3.hpp"

namespace zemax {
namespace model {

class Light {
  public:
    Light( const gfx::core::Vector3f& pos,
           float                      embedded_intensity,
           float                      diffuse_intensity,
           float                      glare_intensity );

    void
    move( const gfx::core::Vector3f& delta );

    gfx::core::Color
    calcColor( const gfx::core::Vector3f& ray,
               const gfx::core::Vector3f& point,
               const gfx::core::Vector3f& normal,
               const gfx::core::Color&    color ) const;

  private:
    gfx::core::Color
    calcEmbeddedLight( const gfx::core::Color& color ) const;

    float
    calcDiffuseLight( const gfx::core::Vector3f& light_ray,
                      const gfx::core::Vector3f& normal ) const;

    float
    calcGlareLight( const gfx::core::Vector3f& light_ray,
                    const gfx::core::Vector3f& normal,
                    const gfx::core::Vector3f& view ) const;

  private:
    gfx::core::Vector3f pos_;
    float               embedded_intensity_;
    float               diffuse_intensity_;
    float               glare_intensity_;
};

} // namespace model
} // namespace zemax
