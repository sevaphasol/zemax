#include "zemax/model/camera.hpp"

namespace zemax {
namespace model {

Camera::Camera( const gfx::core::Vector3f& pos, float screen_width, float screen_height )
    : pos_( pos ),
      screen_width_( screen_width ),
      screen_height_( screen_height ),
      aspect_ratio_( screen_height / screen_width ),
      hor_ort_( 1, 0, 0 ),
      ver_ort_( 0, 1, 0 ),
      fwd_ort_( 0, 0, -1 )
{
}

Ray
Camera::emitRay( uint pixel_x, uint pixel_y ) const
{
    float x3d = ( 2 * ( ( float( pixel_x ) + 0.5 ) / screen_width_ ) - 1 );
    float y3d = ( 2 * ( ( float( pixel_y ) + 0.5 ) / screen_height_ ) - 1 ) * aspect_ratio_;

    gfx::core::Vector3f ray_dir = x3d * hor_ort_ + y3d * ver_ort_ + fwd_ort_;

    return Ray( ray_dir, pos_ );
}

} // namespace model
} // namespace zemax
