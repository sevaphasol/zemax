#include "zemax/model/rendering/camera.hpp"

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
    float y3d = ( -2 * ( ( float( pixel_y ) + 0.5 ) / screen_height_ ) + 1 ) * aspect_ratio_;

    gfx::core::Vector3f ray_dir = x3d * hor_ort_ + y3d * ver_ort_ + fwd_ort_;

    return Ray( ray_dir, pos_ );
}

void
Camera::move( const gfx::core::Vector3f& delta )
{
    pos_ += ( delta.x * hor_ort_ + delta.y * ver_ort_ - delta.z * fwd_ort_ );
}

void
Camera::rotate( const gfx::core::Vector2f& delta )
{
    rotate( delta.x, hor_ort_ );
    rotate( delta.y, ver_ort_ );
}

void
Camera::rotate( float angle, gfx::core::Vector3f& ort )
{
    float cos_angle = std::cos( angle );
    float sin_angle = std::sin( angle );

    gfx::core::Vector3f old_fwd_ort = fwd_ort_;
    gfx::core::Vector3f old_ort     = ort;

    fwd_ort_ = old_fwd_ort * cos_angle - old_ort * sin_angle;
    ort      = old_fwd_ort * sin_angle + old_ort * cos_angle;
}

} // namespace model
} // namespace zemax
