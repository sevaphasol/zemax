#include "zemax/model/rendering/scene_manager.hpp"
#include "gfx/core/color.hpp"
#include "gfx/core/vector3.hpp"
#include "zemax/model/primitives/impls/aabb.hpp"
#include "zemax/model/primitives/impls/plane.hpp"
#include "zemax/model/primitives/impls/sphere.hpp"
#include "zemax/model/primitives/material.hpp"
#include "zemax/model/primitives/primitive.hpp"
#include "zemax/model/rendering/camera.hpp"
#include <cassert>
#include <iostream>
#include <memory>

namespace zemax {
namespace model {

SceneManager::SceneManager( const gfx::core::Vector3f& camera_pos,
                            float                      screen_width,
                            float                      screen_height )
    : camera_( camera_pos, screen_width, screen_height )
{
}

void
SceneManager::addLight( gfx::core::Vector3f pos,
                        float               embedded_intensity,
                        float               diffuse_intensity,
                        float               glare_intensity )
{
    lights_.push_back( Light( pos, embedded_intensity, diffuse_intensity, glare_intensity ) );
}

void
SceneManager::addSphere( const Material& material, const gfx::core::Vector3f& center, float radius )
{
    objects_.push_back( std::make_unique<Sphere>( material, center, radius ) );
}

void
SceneManager::addPlane( const Material&            material,
                        const gfx::core::Vector3f& base_point,
                        const gfx::core::Vector3f& normal )
{
    objects_.push_back( std::make_unique<Plane>( material, base_point, normal ) );
}

void
SceneManager::addAABB( const Material&            material,
                       const gfx::core::Vector3f& center,
                       const gfx::core::Vector3f& bounds )
{
    objects_.push_back( std::make_unique<AABB>( material, center, bounds ) );
}

void
SceneManager::moveLights( const gfx::core::Vector3f& delta )
{
    for ( auto& light : lights_ )
    {
        light.move( delta );
    }
}

bool
SceneManager::findClosestIntersection( IntersectionContext& ctx )
{
    bool  hit          = false;
    float min_distance = std::numeric_limits<float>::max();

    for ( auto& object : objects_ )
    {
        auto info = object->calcRayIntersection( ctx.view_ray );

        if ( !info.has_value() )
        {
            continue;
        }

        auto ro = ctx.view_ray.getBasePoint();
        auto rd = ctx.view_ray.getDir();

        if ( info->inside_object )
        {
            continue;
        }

        const gfx::core::Vector3f point = ro + info->close_distance * rd;

        float distance = ( point - ctx.view_ray.getBasePoint() ).getLen();
        if ( distance > 0 && distance < min_distance )
        {
            min_distance           = distance;
            ctx.closest_object     = object.get();
            ctx.intersection_point = point;
            ctx.normal =
                ( info->normal.has_value() ? info->normal.value()
                                           : object->calcNormal( point, info->inside_object ) );
            hit = true;
        }
    }

    return hit;
}

gfx::core::Color
SceneManager::calcLightsColor( IntersectionContext& ctx )
{
    gfx::core::Color sum_light;

    for ( const auto& light : lights_ )
    {
        sum_light += light.calcColor( ctx.view_ray.getDir(),
                                      ctx.intersection_point,
                                      ctx.normal,
                                      ctx.closest_object->getMaterial() );
    }

    sum_light.clamp( 0, 255 );

    return sum_light;
}

gfx::core::Color
SceneManager::calcReflectedColor( IntersectionContext& ctx )
{
    // // // // // // std::cerr << ctx.normal.x << " " << ctx.normal.y << " " << ctx.normal.z <<
    // std::endl;

    gfx::core::Vector3f reflect_dir = ctx.view_ray.getDir().calcReflected(
        ctx.normal ); // ctx.view_ray.getDir().calcReflected( ctx.normal );
                      // ctx.view_ray.getDir() -
                      // ctx.normal * ( scalarMul( ctx.view_ray.getDir(), ctx.normal ) * 2.0f );

    Ray reflected_ray( reflect_dir, ctx.intersection_point + 1e-4f * ctx.normal );

    auto old_ctx = ctx;

    ctx.view_ray = reflected_ray;
    ctx.depth++;
    gfx::core::Color color = calcRayColor( ctx );

    ctx = old_ctx;

    return color;
}

gfx::core::Color
SceneManager::calcColor( IntersectionContext& ctx )
{
    gfx::core::Color light_color     = calcLightsColor( ctx );
    gfx::core::Color reflected_color = calcReflectedColor( ctx );

    float reflection_factor = ctx.closest_object->getMaterial().reflection_factor;
    float refraction_factor = ctx.closest_object->getMaterial().refraction_factor;

    return ( 1 - reflection_factor - refraction_factor ) * light_color +
           reflection_factor * reflected_color;
}

gfx::core::Color
SceneManager::calcRayColor( IntersectionContext& ctx )
{
    if ( ctx.depth >= IntersectionContext::MaxDepth )
    {
        return ctx.background_color;
    }

    if ( findClosestIntersection( ctx ) )
    {
        return calcColor( ctx );
    }

    return ctx.background_color;
}

gfx::core::Color
SceneManager::calcPixelColor( uint row, uint col, const gfx::core::Color& background_color )
{
    const Ray view_ray = camera_.emitRay( col, row );

    IntersectionContext ctx( view_ray, background_color );

    gfx::core::Color ray_color = calcRayColor( ctx );

    return calcRayColor( ctx );
}
} // namespace model
} // namespace zemax
