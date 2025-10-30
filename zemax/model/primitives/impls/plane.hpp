#pragma once

#include "gfx/core/vector3.hpp"
#include "zemax/model/primitives/primitive.hpp"
#include "zemax/model/rendering/ray.hpp"

namespace zemax {
namespace model {

class Plane : public Primitive {
  public:
    Plane( const Material&            material,
           const gfx::core::Vector3f& base_point,
           const gfx::core::Vector3f& normal );

    virtual std::optional<Primitive::IntersectionInfo>
    calcRayIntersection( const Ray& ray ) const override final;

    virtual gfx::core::Vector3f
    calcNormal( const gfx::core::Vector3f& point, bool inside_object ) const override final;

    const char*
    getName() override final
    {
        return "Plane";
    }

  private:
    gfx::core::Vector3f normal_;
};

} // namespace model
} // namespace zemax
