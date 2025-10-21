#include "zemax/model/sphere.hpp"

namespace zemax {
namespace model {

Sphere::Sphere( const Material& material, const gfx::core::Vector3f& center, float radius )
    : Primitive( material ), center_( center ), radius_( radius )
{
}

void
Sphere::move( const gfx::core::Vector3f& delta )
{
    center_ += delta;
}

bool
Sphere::intersectRay( const Ray& ray ) const
{
    return ray.calcDistance( center_ ) <= radius_;
}

gfx::core::Vector3f
Sphere::calcRayIntersection( const Ray& ray ) const
{
    if ( !intersectRay( ray ) )
    {
        return gfx::core::Vector3f::Nan;
    }

    gfx::core::Vector3f r0 = ray.getBasePoint();
    gfx::core::Vector3f a  = ray.getDir();
    gfx::core::Vector3f b  = r0 - center_;

    float a_len = a.getLen();
    float b_len = b.getLen();

    float cos_phi    = scalarMul( a, b ) / ( a_len * b_len );
    float cos_phi_sq = cos_phi * cos_phi;

    float b_len_sq  = b_len * b_len;
    float b_cos_phi = b_len * cos_phi;

    float r_sq = radius_ * radius_;

    float t = -( b_cos_phi - sqrt( ( b_len_sq * ( cos_phi_sq - 1 ) ) + r_sq ) ) / a_len;

    return ( t > 0 ) ? gfx::core::Vector3f::Nan : r0 + a * t;
}

gfx::core::Vector3f
Sphere::normal( const gfx::core::Vector3f& point ) const
{
    return point - center_;
}

} // namespace model
} // namespace zemax
