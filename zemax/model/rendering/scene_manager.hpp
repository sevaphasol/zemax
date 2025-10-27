#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/vector3.hpp"
#include "zemax/model/primitives/material.hpp"
#include "zemax/model/primitives/primitive.hpp"
#include "zemax/model/rendering/camera.hpp"
#include "zemax/model/rendering/light.hpp"
#include "zemax/model/rendering/ray.hpp"
#include <memory>
#include <vector>

namespace zemax {
namespace model {

class SceneManager {
  public:
    SceneManager( const gfx::core::Vector3f& camera_pos, float screen_width, float screen_height );

    bool&
    needUpdate()
    {
        return need_update_;
    }

    bool
    needUpdate() const
    {
        return need_update_;
    }

    void
    addLight( gfx::core::Vector3f pos,
              float               embedded_intensity,
              float               diffuse_intensity,
              float               glare_intensity );

    void
    addSphere( const Material& material, const gfx::core::Vector3f& center, float radius );

    void
    addPlane( const Material&            material,
              const gfx::core::Vector3f& base_point,
              const gfx::core::Vector3f& normal );

    void
    addAABB( const Material&            material,
             const gfx::core::Vector3f& center,
             const gfx::core::Vector3f& bounds );

    void
    addCube( const Material& material, const gfx::core::Vector3f& center, float side );

    gfx::core::Color
    calcPixelColor( uint row, uint col, const gfx::core::Color& background_color );

    Camera&
    getCamera()
    {
        return camera_;
    }

  private:
    struct IntersectionContext
    {
        IntersectionContext( const Ray& view_ray, const gfx::core::Color& background_color )
            : view_ray( view_ray ), background_color( background_color )
        {
        }

        // IntersectionContext( const IntersectionContext& that )
        //     : background_color( that.background_color )
        // {
        //     this->view_ray           = that.view_ray;
        //     this->intersection_point = that.intersection_point;
        //     this->normal             = that.normal;
        //     this->closest_object     = that.closest_object;
        //     this->depth              = that.depth;
        // }

        IntersectionContext&
        operator=( const IntersectionContext& that )
        {
            this->view_ray           = that.view_ray;
            this->intersection_point = that.intersection_point;
            this->normal             = that.normal;
            this->background_color   = that.background_color;
            this->closest_object     = that.closest_object;
            this->depth              = that.depth;

            return *this;
        }

        Ray                     view_ray;
        gfx::core::Vector3f     intersection_point;
        gfx::core::Vector3f     normal;
        gfx::core::Color        background_color;
        Primitive*              closest_object = nullptr;
        size_t                  depth          = 0;
        static constexpr size_t MaxDepth       = 4;
    };

  private:
    gfx::core::Color
    calcRayColor( IntersectionContext& ctx );

    void
    moveLights( const gfx::core::Vector3f& delta );

    gfx::core::Color
    calcReflectedColor( IntersectionContext& ctx );

    gfx::core::Color
    calcColor( IntersectionContext& ctx );

    gfx::core::Color
    calcLightsColor( IntersectionContext& ctx );

    bool
    findClosestIntersection( IntersectionContext& ctx );

  private:
    bool need_update_ = true;

    std::vector<std::unique_ptr<Primitive>> objects_;
    std::vector<Light>                      lights_;
    Camera                                  camera_;
};

} // namespace model
} // namespace zemax
