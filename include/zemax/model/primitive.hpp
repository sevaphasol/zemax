#pragma once

#include "gfx/core/vector2.hpp"
#include "gfx/core/vector3.hpp"
#include "zemax/model/material.hpp"
#include "zemax/model/ray.hpp"
#include <optional>

namespace zemax {
namespace model {

class Primitive {
  public:
    virtual ~Primitive() = default;
    Primitive( const Material& material, const gfx::core::Vector3f& origin )
        : material_( material ), origin_( origin )
    {
    }

    Material
    getMaterial() const
    {
        return material_;
    }

    gfx::core::Vector3f
    getOrigin() const
    {
        return origin_;
    }

    virtual void
    move( const gfx::core::Vector3f& delta )
    {
        origin_ += delta;
    }

    struct IntersectionInfo
    {
        float                              close_distance;
        float                              far_distance;
        bool                               inside_object;
        std::optional<gfx::core::Vector3f> normal;
    };

    virtual std::optional<Primitive::IntersectionInfo>
    calcRayIntersection( const Ray& ray ) const = 0;

    virtual gfx::core::Vector3f
    calcNormal( const gfx::core::Vector3f& point, bool inside_object ) const = 0;

  private:
    gfx::core::Vector3f origin_;
    Material            material_;
};

} // namespace model
} // namespace zemax
