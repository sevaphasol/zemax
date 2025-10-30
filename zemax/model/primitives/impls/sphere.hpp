#pragma once

#include "gfx/core/vector3.hpp"
#include "zemax/model/primitives/primitive.hpp"
#include "zemax/model/rendering/ray.hpp"
#include <optional>

namespace zemax {
namespace model {

class Sphere : public Primitive {
  public:
    Sphere( const Material& material, const gfx::core::Vector3f& center, float radius );

    virtual std::optional<Primitive::IntersectionInfo>
    calcRayIntersection( const Ray& ray ) const override final;

    virtual gfx::core::Vector3f
    calcNormal( const gfx::core::Vector3f& point, bool inside_object ) const override final;

    const char*
    getName() override final
    {
        return "Sphere";
    }

  private:
    float radius_;
    float radius_sq_;
};

} // namespace model
} // namespace zemax
