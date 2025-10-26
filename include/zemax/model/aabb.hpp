#pragma once

#include "gfx/core/vector3.hpp"
#include "zemax/model/primitive.hpp"
#include "zemax/model/ray.hpp"

namespace zemax {
namespace model {

class AABB : public Primitive {
  public:
    AABB( const Material&            material,
          const gfx::core::Vector3f& center,
          const gfx::core::Vector3f& half_size );

    virtual std::optional<Primitive::IntersectionInfo>
    calcRayIntersection( const Ray& ray ) const override final;

    virtual gfx::core::Vector3f
    calcNormal( const gfx::core::Vector3f& point, bool inside_object ) const override final;

  private:
    gfx::core::Vector3f half_size_;
};

} // namespace model
} // namespace zemax
