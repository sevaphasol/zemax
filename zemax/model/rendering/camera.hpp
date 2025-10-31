#pragma once

#include "gfx/core/vector2.hpp"
#include "gfx/core/vector3.hpp"
#include "zemax/model/rendering/ray.hpp"
#include <optional>

namespace zemax {
namespace model {

class Camera {
  public:
    Camera( const gfx::core::Vector3f& pos,
            float                      screen_width,
            float                      screen_height,
            float                      fov = 1.0f );

    gfx::core::Vector3f&
    getPos()
    {
        return pos_;
    }

    Ray
    emitRay( uint pixel_x, uint pixel_y ) const;

    std::optional<gfx::core::Vector2f>
    projectToScreen( const gfx::core::Vector3f& world_pos ) const;

    void
    move( const gfx::core::Vector3f& delta );

    void
    rotate( const gfx::core::Vector2f& delta );

    void
    scale( float scale_factor );

  private:
    void
    rotate( float angle, gfx::core::Vector3f& ort );

  private:
    gfx::core::Vector3f pos_;
    gfx::core::Vector3f hor_ort_;
    gfx::core::Vector3f ver_ort_;
    gfx::core::Vector3f fwd_ort_;
    float               screen_width_;
    float               screen_height_;
    float               aspect_ratio_;
    float               fov_;
};

} // namespace model
} // namespace zemax
