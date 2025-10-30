#pragma once

#include "gfx/core/vector2.hpp"
#include "gfx/core/vector3.hpp"
#include "zemax/model/primitives/material.hpp"
#include "zemax/model/rendering/ray.hpp"
#include <memory>
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

    virtual const char*
    getName() = 0;

    virtual std::unique_ptr<Primitive>
    clone() const = 0;

    void
    paint()
    {
        material_.painted = true;
    }

    void
    revert_paint()
    {
        material_.painted = false;
    }

    void
    setColor( gfx::core::Color color )
    {
        material_.color = color;
    }

    void
    setMaterial( Material material )
    {
        material_ = material;
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

    void
    setOrigin( const gfx::core::Vector3f& new_origin )
    {
        origin_ = new_origin;
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
    bool painted_;

    gfx::core::Vector3f origin_;
    Material            material_;
};

} // namespace model
} // namespace zemax
