#pragma once

#include "gfx/core/vector3.hpp"
#include "zemax/model/ray.hpp"

namespace zemax {
namespace model {

class Camera {
  public:
    Camera( const gfx::core::Vector3f& pos, float screen_width, float screen_height );

    Ray
    emitRay( uint pixel_x, uint pixel_y ) const;

    gfx::core::Vector3f&
    getPos()
    {
        return pos_;
    }

    gfx::core::Vector3f&
    getHorOrt()
    {
        return hor_ort_;
    }

    gfx::core::Vector3f&
    getVerOrt()
    {
        return ver_ort_;
    }

    gfx::core::Vector3f&
    getFwdOrt()
    {
        return fwd_ort_;
    }

  private:
    gfx::core::Vector3f pos_;
    gfx::core::Vector3f hor_ort_;
    gfx::core::Vector3f ver_ort_;
    gfx::core::Vector3f fwd_ort_;
    float               screen_width_;
    float               screen_height_;
    float               aspect_ratio_;
};

} // namespace model
} // namespace zemax
