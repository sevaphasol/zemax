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

    std::unique_ptr<Primitive>
    clone() const override
    {
        return std::make_unique<Plane>( *this );
    }

    const char*
    getName() override final
    {
        return "Plane";
    }

    std::array<gfx::core::Vector3f, 8>
    getCircumscribedAABB() const override final;

  private:
    gfx::core::Vector3f normal_;
};

} // namespace model
} // namespace zemax
