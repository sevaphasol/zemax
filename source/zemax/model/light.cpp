#include "zemax/model/light.hpp"
#include "gfx/core/color.hpp"
#include "gfx/core/vector3.hpp"

namespace zemax {
namespace model {

Light::Light( const gfx::core::Vector3f& pos,
              float                      embedded_intensity,
              float                      diffuse_intensity,
              float                      glare_intensity )
    : pos_( pos ),
      embedded_intensity_( embedded_intensity ),
      diffuse_intensity_( diffuse_intensity ),
      glare_intensity_( glare_intensity ) {};

void
Light::move( const gfx::core::Vector3f& delta )
{
    pos_ += delta;
}

gfx::core::Color
Light::calcColor( const gfx::core::Vector3f& ray,
                  const gfx::core::Vector3f& point,
                  const gfx::core::Vector3f& normal,
                  const gfx::core::Color&    color ) const
{
    gfx::core::Vector3f light_ray = point - pos_;

    gfx::core::Color embedded_light = calcEmbeddedLight( color );
    gfx::core::Color diffuse_light  = calcDiffuseLight( light_ray, normal );
    gfx::core::Color glare_light    = calcGlareLight( light_ray, normal, ray );

    return embedded_light + diffuse_light + glare_light;
}

gfx::core::Color
Light::calcEmbeddedLight( const gfx::core::Color& color ) const
{
    return color * embedded_intensity_;
}

float
Light::calcDiffuseLight( const gfx::core::Vector3f& light_ray,
                         const gfx::core::Vector3f& normal ) const
{
    float cos       = -calcCos( light_ray, normal );
    float intensity = diffuse_intensity_ * cos;

    return std::max( 0.0f, intensity * 255 );
}

float
Light::calcGlareLight( const gfx::core::Vector3f& light_ray,
                       const gfx::core::Vector3f& normal,
                       const gfx::core::Vector3f& view_ray ) const
{
    gfx::core::Vector3f reflected_ray = light_ray.calcReflected( normal );

    float cos       = -calcCos( view_ray, reflected_ray );
    float intensity = glare_intensity_ * float( std::pow( cos, 11 ) );

    return std::max( 0.0f, intensity * 255 );
}

} // namespace model
} // namespace zemax
