#pragma once

#include "gfx/core/vector3.hpp"
#include "zemax/model/primitive.hpp"
#include "zemax/model/ray.hpp"

namespace zemax {
namespace model {

class Plane : public Primitive {
  public:
    Plane( const Material&            material,
           const gfx::core::Vector3f& base_point,
           const gfx::core::Vector3f& normal );

    virtual void
    move( const gfx::core::Vector3f& delta ) override;

    virtual bool
    intersectRay( const Ray& ray ) const override;

    virtual gfx::core::Vector3f
    calcRayIntersection( const Ray& ray ) const override;

    virtual gfx::core::Vector3f
    normal( const gfx::core::Vector3f& point ) const override;

  private:
    gfx::core::Vector3f base_point_;
    gfx::core::Vector3f normal_;
};

} // namespace model
} // namespace zemax
