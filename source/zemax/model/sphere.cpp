#include "zemax/model/sphere.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/vector3.hpp"
#include <optional>

namespace zemax {
namespace model {

Sphere::Sphere( const Material& material, const gfx::core::Vector3f& center, float radius )
    : Primitive( material, center ), radius_( radius ), radius_sq_( radius * radius )
{
}

std::optional<Primitive::IntersectionInfo>
Sphere::calcRayIntersection( const Ray& ray ) const
{
    gfx::core::Vector3f ro = ray.getBasePoint();
    gfx::core::Vector3f rd = ray.getDir();
    gfx::core::Vector3f ce = getOrigin();
    gfx::core::Vector3f oc = ro - ce;

    float b = scalarMul( oc, rd );
    float c = scalarMul( oc, oc ) - radius_sq_;

    float h = b * b - c;

    if ( h < 0.0f )
    {
        return std::nullopt;
    }

    h = sqrt( h );

    float t = -b - h;

    IntersectionInfo info;

    info.close_distance = -b - h;
    info.far_distance   = -b + h;
    info.inside_object  = info.close_distance < 0.0f;
    info.normal         = std::nullopt;

    return info;
}

gfx::core::Vector3f
Sphere::calcNormal( const gfx::core::Vector3f& point, bool inside_object ) const
{
    gfx::core::Vector3f normal = ( point - getOrigin() ).normalize();

    if ( inside_object )
    {
        normal = -normal;
    }

    return normal;
}

} // namespace model
} // namespace zemax
