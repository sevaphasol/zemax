#include "zemax/model/ray.hpp"
#include "gfx/core/vector3.hpp"

namespace zemax {
namespace model {

Ray::Ray( const gfx::core::Vector3f& dir, const gfx::core::Vector3f& base_point )
    : dir_( dir ), base_point_( base_point )
{
}

float
Ray::calcDistance( const gfx::core::Vector3f& point ) const
{
    float square = vectorMulModule( ( point - base_point_ ), dir_ );
    float height = dir_.getLen();

    return square / height;
}

} // namespace model
} // namespace zemax
