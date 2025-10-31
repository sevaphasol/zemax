#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/vector3.hpp"
#include "zemax/model/primitives/impls/aabb.hpp"
#include "zemax/model/primitives/impls/plane.hpp"
#include "zemax/model/primitives/impls/sphere.hpp"
#include "zemax/model/primitives/material.hpp"
#include "zemax/model/primitives/primitive.hpp"
#include "zemax/model/rendering/camera.hpp"
#include "zemax/model/rendering/light.hpp"
#include "zemax/model/rendering/ray.hpp"
#include <assert.h>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace zemax {
namespace model {

class SceneManager {
  public:
    SceneManager( const gfx::core::Vector3f& camera_pos, float screen_width, float screen_height );

    size_t
    getObjectsCount()
    {
        return objects_.size();
    }

    struct ObjectInfo
    {
        gfx::core::Vector3f pos;
        std::string         type_name;
        size_t              objects_idx;
    };

    void
    paint( int idx )
    {
        if ( idx >= 0 && idx <= objects_.size() )
        {
            objects_[idx]->paint();
        }
    }

    void
    revert_paint( int idx )
    {
        if ( idx >= 0 && idx <= objects_.size() )
        {
            objects_[idx]->revert_paint();
        }
    }

    void
    copyTargetObj( float new_obj_x, float new_obj_y, float new_obj_z )
    {
        std::cerr << __PRETTY_FUNCTION__ << std::endl;
        std::cerr << new_obj_x << " " << new_obj_y << " " << new_obj_z << std::endl;

        if ( target_obj_ == nullptr )
        {
            std::cerr << "copyTargetObj: no target object set" << std::endl;
            return;
        }

        int idx = -1;
        for ( int i = 0; i < objects_.size(); ++i )
        {
            if ( objects_[i].get() == target_obj_ )
            {
                idx = i;
                break;
            }
        }

        assert( idx != -1 );

        auto new_obj = target_obj_->clone();

        gfx::core::Vector3f new_pos{ new_obj_x, new_obj_y, new_obj_z };
        new_obj->setOrigin( new_pos );

        target_obj_->revert_paint();
        target_obj_ = new_obj.get();

        objects_.push_back( std::move( new_obj ) );

        need_update_ = true;
    }

    ObjectInfo
    getObjectInfo( size_t idx )
    {
        auto* obj = objects_[idx].get();

        std::string obj_name;

        if ( typeid( *obj ).hash_code() == typeid( Sphere ).hash_code() )
        {
            obj_name = "Sphere";
        } else if ( typeid( *obj ).hash_code() == typeid( Plane ).hash_code() )
        {
            obj_name = "Plane";
        } else if ( typeid( *obj ).hash_code() == typeid( AABB ).hash_code() )
        {
            obj_name = "AABB";
        } else
        {
            assert( false );
        }

        return { .pos = obj->getOrigin(), .type_name = obj_name, .objects_idx = idx };
    }

    Primitive*
    getIntersectedObj( uint px, uint py )
    {
        Ray ray = camera_.emitRay( px, py );

        IntersectionContext ctx( ray );

        if ( !findClosestIntersection( ctx ) )
        {
            return nullptr;
        }

        return ctx.closest_object;
    }

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
    deleteTargetObj()
    {
        for ( size_t i = 0; i < objects_.size(); ++i )
        {
            if ( objects_[i].get() == target_obj_ )
            {
                objects_.erase( objects_.begin() + i );
                target_obj_ = nullptr;
                return;
            }
        }
    }

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

    const Camera&
    getCamera() const
    {
        return camera_;
    }

    Primitive*
    getTargetObj()
    {
        return target_obj_;
    }

    const Primitive*
    getTargetObj() const
    {
        return target_obj_;
    }

    void
    setTargetObj( Primitive* obj )
    {
        target_obj_ = obj;
    }

  private:
    struct IntersectionContext
    {
        IntersectionContext( const Ray& view_ray, const gfx::core::Color& background_color )
            : view_ray( view_ray ), background_color( background_color )
        {
        }

        IntersectionContext( const Ray& view_ray ) : view_ray( view_ray ) {}

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

    Primitive*                              target_obj_ = nullptr;
    std::vector<std::unique_ptr<Primitive>> objects_;
    std::vector<Light>                      lights_;
    Camera                                  camera_;
};

} // namespace model
} // namespace zemax
