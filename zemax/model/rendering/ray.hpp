#pragma once

#include "gfx/core/vector3.hpp"

namespace zemax {
namespace model {

class Ray {
  public:
    Ray( const gfx::core::Vector3f& dir, const gfx::core::Vector3f& base_point );

    Ray() = default;

    float
    calcDistance( const gfx::core::Vector3f& point ) const;

    gfx::core::Vector3f
    getDir() const
    {
        return dir_;
    }

    gfx::core::Vector3f
    getBasePoint() const
    {
        return base_point_;
    }

  private:
    gfx::core::Vector3f dir_;
    gfx::core::Vector3f base_point_;
};

} // namespace model
} // namespace zemax
