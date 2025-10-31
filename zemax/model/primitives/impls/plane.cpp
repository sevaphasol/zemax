#include "zemax/model/primitives/impls/plane.hpp"
#include "gfx/core/vector3.hpp"

namespace zemax {
namespace model {

Plane::Plane( const Material&            material,
              const gfx::core::Vector3f& base_point,
              const gfx::core::Vector3f& normal )
    : Primitive( material, base_point ), normal_( normal )
{
    normal_.normalize();
}

std::optional<Primitive::IntersectionInfo>
Plane::calcRayIntersection( const Ray& ray ) const
{
    auto r0 = ray.getBasePoint();
    auto a  = ray.getDir();
    auto rp = getOrigin();
    auto n  = normal_;

    auto a_pr = scalarMul( a, n );

    if ( a_pr == 0 )
    {
        return std::nullopt;
    }

    float t = scalarMul( rp - r0, n ) / a_pr;

    if ( t < 0.0f )
    {
        return std::nullopt;
    }

    IntersectionInfo info;

    info.close_distance = t;
    info.far_distance   = t;
    info.inside_object  = false;
    info.normal         = normal_;

    return info;
}

gfx::core::Vector3f
Plane::calcNormal( const gfx::core::Vector3f& point, bool inside_object ) const
{
    return normal_;
}

std::array<gfx::core::Vector3f, 8>
Plane::getCircumscribedAABB() const
{
    gfx::core::Vector3f c = getOrigin();

    float h = 1.0f;

    return { { { c.x - h, c.y - h, c.z - h },
               { c.x + h, c.y - h, c.z - h },
               { c.x - h, c.y + h, c.z - h },
               { c.x + h, c.y + h, c.z - h },
               { c.x - h, c.y - h, c.z + h },
               { c.x + h, c.y - h, c.z + h },
               { c.x - h, c.y + h, c.z + h },
               { c.x + h, c.y + h, c.z + h } } };
}

} // namespace model
} // namespace zemax
