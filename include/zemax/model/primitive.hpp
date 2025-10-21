#pragma once

#include "gfx/core/vector3.hpp"
#include "zemax/model/material.hpp"
#include "zemax/model/ray.hpp"

namespace zemax {
namespace model {

class Primitive {
  public:
    Primitive( const Material& material ) : material_( material ) {}
    virtual ~Primitive() = default;

    virtual void
    move( const gfx::core::Vector3f& delta ) = 0;

    virtual bool
    intersectRay( const Ray& line ) const = 0;

    virtual gfx::core::Vector3f
    calcRayIntersection( const Ray& ray ) const = 0;

    virtual gfx::core::Vector3f
    normal( const gfx::core::Vector3f& point ) const = 0;

    Material
    getMaterial() const
    {
        return material_;
    }

  private:
    Material material_;
};

} // namespace model
} // namespace zemax
