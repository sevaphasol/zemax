#pragma once

#include "gfx/core/vector3.hpp"
#include "zemax/model/primitive.hpp"
#include "zemax/model/ray.hpp"

namespace zemax {
namespace model {

class Sphere : public Primitive {
  public:
    Sphere( const Material& material, const gfx::core::Vector3f& center, float radius );

    virtual void
    move( const gfx::core::Vector3f& delta ) override;

    virtual bool
    intersectRay( const Ray& ray ) const override;

    virtual gfx::core::Vector3f
    calcRayIntersection( const Ray& ray ) const override;

    virtual gfx::core::Vector3f
    normal( const gfx::core::Vector3f& point ) const override;

  private:
    gfx::core::Vector3f center_;
    float               radius_;
    float               radius_sq_;
};

} // namespace model
} // namespace zemax
