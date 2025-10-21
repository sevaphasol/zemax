#pragma once

#include "gfx/core/vector2.hpp"
#include "zemax/model/camera.hpp"

namespace zemax {
namespace controller {

class Camera {
  public:
    Camera( model::Camera& model );

    void
    move( const gfx::core::Vector3f& delta );

    void
    rotate( const gfx::core::Vector2f& delta );

  private:
    void
    rotate( float angle, gfx::core::Vector3f& ort );

  private:
    model::Camera& model_;
};

} // namespace controller
} // namespace zemax
