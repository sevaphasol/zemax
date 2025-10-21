#include "zemax/controller/camera.hpp"

namespace zemax {
namespace controller {

Camera::Camera( model::Camera& model ) : model_( model ) {}

void
Camera::move( const gfx::core::Vector3f& delta )
{
    model_.getPos() += ( delta.x * model_.getHorOrt() + delta.y * model_.getVerOrt() -
                         delta.z * model_.getFwdOrt() );
}

void
Camera::rotate( const gfx::core::Vector2f& delta )
{
    rotate( delta.x, model_.getHorOrt() );
    rotate( delta.y, model_.getVerOrt() );
}

void
Camera::rotate( float angle, gfx::core::Vector3f& ort )
{
    float cos_angle = std::cos( angle );
    float sin_angle = std::sin( angle );

    gfx::core::Vector3f old_fwd_ort = model_.getFwdOrt();
    gfx::core::Vector3f old_ort     = ort;

    model_.getFwdOrt() = old_fwd_ort * cos_angle - old_ort * sin_angle;
    ort                = old_fwd_ort * sin_angle + old_ort * cos_angle;
}

} // namespace controller
} // namespace zemax
