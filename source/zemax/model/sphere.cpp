#include "zemax/model/sphere.hpp"
#include "gfx/core/vector3.hpp"

namespace zemax {
namespace model {

Sphere::Sphere( const Material& material, const gfx::core::Vector3f& center, float radius )
    : Primitive( material ), center_( center ), radius_( radius ), radius_sq_( radius * radius )
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
    gfx::core::Vector3f ro = ray.getBasePoint();
    gfx::core::Vector3f rd = ray.getDir();
    gfx::core::Vector3f oc = ro - center_;

    float b = scalarMul( oc, rd );
    float c = scalarMul( oc, oc ) - radius_sq_;

    float h = b * b - c;

    if ( h < 0.0f )
    {
        return gfx::core::Vector3f::Nan;
    }

    h = sqrt( h );

    float t = -b - h;

    if ( t < 0.0f )
    {
        return gfx::core::Vector3f::Nan;
    }

    return ro + t * rd;
}

gfx::core::Vector3f
Sphere::normal( const gfx::core::Vector3f& point ) const
{
    return point - center_;
}

} // namespace model
} // namespace zemax
