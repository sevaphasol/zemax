#include "zemax/model/ray.hpp"
#include "gfx/core/vector3.hpp"

namespace zemax {
namespace model {

Ray::Ray( const gfx::core::Vector3f& dir, const gfx::core::Vector3f& base_point )
    : dir_( dir ), base_point_( base_point )
{
    dir_.normalize();
}

float
Ray::calcDistance( const gfx::core::Vector3f& point ) const
{
    return vectorMulModule( ( point - base_point_ ), dir_ );
}

} // namespace model
} // namespace zemax
