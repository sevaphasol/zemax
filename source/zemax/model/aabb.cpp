#include "zemax/model/aabb.hpp"
#include "gfx/core/vector3.hpp"

namespace zemax {
namespace model {

AABB::AABB( const Material&            material,
            const gfx::core::Vector3f& center,
            const gfx::core::Vector3f& bounds )
    : Primitive( material ), center_( center ), bounds_( bounds )
{
}

void
AABB::move( const gfx::core::Vector3f& delta )
{
    center_ += delta;
}

bool
AABB::intersectRay( const Ray& ray ) const
{
    const auto& r0 = ray.getBasePoint();
    const auto& a  = ray.getDir();

    float t_min = std::numeric_limits<float>::min();
    float t_max = std::numeric_limits<float>::max();

    for ( size_t i = 0; i < 3; ++i )
    {
        float t0 = ( -center_[i] - bounds_[i] + r0[i] ) / a[i];
        float t1 = ( -center_[i] + bounds_[i] + r0[i] ) / a[i];

        if ( a[i] < 0.0f )
        {
            std::swap( t0, t1 );
        }

        t_min = std::max( t_min, t0 );
        t_max = std::min( t_max, t1 );

        if ( t_max <= t_min )
        {
            return false;
        }
    }

    return t_max >= 0.0f;
}

gfx::core::Vector3f
AABB::calcRayIntersection( const Ray& ray ) const
{
    if ( !intersectRay( ray ) )
    {
        return gfx::core::Vector3f::Nan;
    }

    const auto& r0 = ray.getBasePoint();
    const auto& a  = ray.getDir();

    float t_min = -std::numeric_limits<float>::max();
    float t_max = std::numeric_limits<float>::max();

    for ( int i = 0; i < 3; ++i )
    {
        if ( a[i] == 0 )
        {
            continue;
        }

        float t0 = ( -center_[i] - bounds_[i] + r0[i] ) / a[i];
        float t1 = ( -center_[i] + bounds_[i] + r0[i] ) / a[i];

        if ( a[i] < 0.0f )
        {
            std::swap( t0, t1 );
        }

        t_min = std::max( t_min, t0 );
        t_max = std::min( t_max, t1 );
    }

    float t = ( t_min >= 0.0f ) ? t_min : t_max;

    return r0 + a * t;
}

gfx::core::Vector3f
AABB::normal( const gfx::core::Vector3f& point ) const
{
    gfx::core::Vector3f local     = point - center_;
    gfx::core::Vector3f abs_local = { std::abs( local.x ),
                                      std::abs( local.y ),
                                      std::abs( local.z ) };

    if ( abs_local.x > abs_local.y && abs_local.x > abs_local.z )
    {
        return gfx::core::Vector3f( local.x > 0 ? 1 : -1, 0, 0 );
    }

    if ( abs_local.y > abs_local.z )
    {
        return gfx::core::Vector3f( 0, local.y > 0 ? 1 : -1, 0 );
    }

    return gfx::core::Vector3f( 0, 0, local.z > 0 ? 1 : -1 );
}

} // namespace model
} // namespace zemax
