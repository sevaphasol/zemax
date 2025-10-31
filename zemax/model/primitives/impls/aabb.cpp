#include "zemax/model/primitives/impls/aabb.hpp"
#include "gfx/core/vector3.hpp"
#include "zemax/model/primitives/primitive.hpp"
#include <optional>

namespace zemax {
namespace model {

AABB::AABB( const Material&            material,
            const gfx::core::Vector3f& center,
            const gfx::core::Vector3f& half_size )
    : Primitive( material, center ), half_size_( half_size )
{
}

std::optional<Primitive::IntersectionInfo>
AABB::calcRayIntersection( const Ray& ray ) const
{
    gfx::core::Vector3f ro = ray.getBasePoint() - getOrigin();
    gfx::core::Vector3f rd = ray.getDir();

    gfx::core::Vector3f m;
    m.x = ( std::abs( rd.x ) > 1e-6f ) ? 1.0f / rd.x : std::numeric_limits<float>::max();
    m.y = ( std::abs( rd.y ) > 1e-6f ) ? 1.0f / rd.y : std::numeric_limits<float>::max();
    m.z = ( std::abs( rd.z ) > 1e-6f ) ? 1.0f / rd.z : std::numeric_limits<float>::max();

    gfx::core::Vector3f n = { m.x * ro.x, m.y * ro.y, m.z * ro.z };
    gfx::core::Vector3f k = { std::abs( m.x ) * half_size_.x,
                              std::abs( m.y ) * half_size_.y,
                              std::abs( m.z ) * half_size_.z };

    gfx::core::Vector3f t1 = { -n.x - k.x, -n.y - k.y, -n.z - k.z };
    gfx::core::Vector3f t2 = { -n.x + k.x, -n.y + k.y, -n.z + k.z };

    float t_n = std::max( { t1.x, t1.y, t1.z } );
    float t_f = std::min( { t2.x, t2.y, t2.z } );

    if ( t_n > t_f || t_f < 0.0f )
    {
        return std::nullopt;
    }

    Primitive::IntersectionInfo info;
    info.close_distance = t_n;
    info.far_distance   = t_f;
    info.inside_object  = ( t_n <= 0.0f );

    gfx::core::Vector3f normal_axis;
    if ( !info.inside_object )
    {
        info.normal = step( gfx::core::Vector3f{ t_n, t_n, t_n }, t1 );
    } else
    {
        info.normal = step( t2, gfx::core::Vector3f{ t_f, t_f, t_f } );
    }

    info.normal = info.normal.value() * sign( rd );

    return info;
}

gfx::core::Vector3f
AABB::calcNormal( const gfx::core::Vector3f& point, bool inside_object ) const
{
    gfx::core::Vector3f local     = point - getOrigin();
    gfx::core::Vector3f abs_local = { std::abs( local.x ),
                                      std::abs( local.y ),
                                      std::abs( local.z ) };

    if ( abs_local.x >= abs_local.y && abs_local.x >= abs_local.z )
    {
        return gfx::core::Vector3f{ ( local.x >= 0.0f ) ? 1.0f : -1.0f, 0.0f, 0.0f };
    }
    if ( abs_local.y >= abs_local.z )
    {
        return gfx::core::Vector3f{ 0.0f, ( local.y >= 0.0f ) ? 1.0f : -1.0f, 0.0f };
    }
    return gfx::core::Vector3f{ 0.0f, 0.0f, ( local.z >= 0.0f ) ? 1.0f : -1.0f };
}

std::array<gfx::core::Vector3f, 8>
AABB::getCircumscribedAABB() const
{
    gfx::core::Vector3f c = getOrigin();
    gfx::core::Vector3f h = half_size_;

    return { { { c.x - h.x, c.y - h.y, c.z - h.z },
               { c.x + h.x, c.y - h.y, c.z - h.z },
               { c.x - h.x, c.y + h.y, c.z - h.z },
               { c.x + h.x, c.y + h.y, c.z - h.z },
               { c.x - h.x, c.y - h.y, c.z + h.z },
               { c.x + h.x, c.y - h.y, c.z + h.z },
               { c.x - h.x, c.y + h.y, c.z + h.z },
               { c.x + h.x, c.y + h.y, c.z + h.z } } };
}

} // namespace model
} // namespace zemax
