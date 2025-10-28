#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/primitive_type.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/vector3.hpp"
#include "gfx/core/vertex.hpp"
#include "gfx/core/window.hpp"

#include "gfx/ui/widget.hpp"

#include "gfx/ui/widget_container.hpp"
#include "zemax/model/rendering/scene_manager.hpp"
#include "zemax/model/rendering/scenes_manager.hpp"

#include <thread>
#include <vector>

namespace zemax {
namespace view {

class Scene : public gfx::ui::WidgetVectorContainer {
  public:
    ~Scene() = default;

    explicit Scene( const gfx::core::Vector2f& pos,
                    const gfx::core::Vector2f& size,
                    const gfx::core::Color&    background_color,
                    const gfx::core::Vector3f& camera_pos )
        : gfx::ui::WidgetVectorContainer( pos, size ),
          background_color_( background_color ),
          pixels_( size.x * size.y )
    {
        model_.scenes.emplace_back( model::SceneManager( camera_pos, size.x, size.y ) );
        model_.scenes.emplace_back( model::SceneManager( camera_pos, size.x, size.y ) );

        model_.scenes[0].addLight( gfx::core::Vector3f( 3, 3, 3 ), 1.0, 0.3, 0.9 );
        model_.scenes[0].addLight( gfx::core::Vector3f( 0, 0, -5 ), 0.2, 0.3, 0.9 );

        model_.scenes[0].addAABB( model::Material( gfx::core::Color( 255, 8, 8 ), 0.5f ),
                                  gfx::core::Vector3f( -2, 1, -8 ),
                                  gfx::core::Vector3f( 0.75, 0.75, 0.75 ) );

        model_.scenes[0].addAABB( model::Material( gfx::core::Color( 8, 8, 8 ), 0.5f ),
                                  gfx::core::Vector3f( -1, 0.5, -5 ),
                                  gfx::core::Vector3f( 0.25, 0.25, 0.25 ) );

        model_.scenes[0].addSphere( model::Material( gfx::core::Color( 8, 32, 8 ), 0.3f ),
                                    gfx::core::Vector3f( 2, 0, -7 ),
                                    1.5 );

        model_.scenes[0].addSphere( model::Material( gfx::core::Color( 8, 32, 8 ), 0.3f ),
                                    gfx::core::Vector3f( -2, 1, -1 ),
                                    1.5 );

        model_.scenes[0].addPlane( model::Material( gfx::core::Color( 128, 8, 127 ), 0.5f ),
                                   gfx::core::Vector3f( 0, -1.75, 0 ),
                                   gfx::core::Vector3f( 0, 1, 0 ) );

        model_.scenes[1].addLight( gfx::core::Vector3f( 3, 3, 3 ), 1.0, 0.3, 0.9 );
        model_.scenes[1].addLight( gfx::core::Vector3f( 0, 0, -5 ), 0.2, 0.3, 0.9 );

        model_.scenes[1].addAABB( model::Material( gfx::core::Color( 255, 8, 8 ), 0.5f ),
                                  gfx::core::Vector3f( -2, 1, -8 ),
                                  gfx::core::Vector3f( 0.75, 0.75, 0.75 ) );

        model_.scenes[1].addSphere( model::Material( gfx::core::Color( 8, 32, 8 ), 0.3f ),
                                    gfx::core::Vector3f( -2, 1, -1 ),
                                    1.5 );
    }

    model::ScenesManager&
    getModel()
    {
        return model_;
    }

    virtual bool
    onIdle( const gfx::ui::Event& event ) override final
    {
        // // // std::cerr << "Scene: " << __PRETTY_FUNCTION__ << std::endl;

        if ( model_.scenes[model_.active_scene_idx].needUpdate() )
        {
            update();
            model_.scenes[model_.active_scene_idx].needUpdate() = false;
        }

        return false;
    }

  private:
    void
    update()
    {
        const size_t w = getSize().x;
        const size_t h = getSize().y;

        constexpr size_t         num_threads     = 16;
        const size_t             rows_per_thread = h / num_threads;
        std::vector<std::thread> workers;
        workers.reserve( num_threads );

        for ( size_t t = 0; t < num_threads; ++t )
        {
            const size_t start_row = t * rows_per_thread;
            const size_t end_row   = ( t == num_threads - 1 ) ? h : ( t + 1 ) * rows_per_thread;

            workers.emplace_back( [this, w, start_row, end_row]() {
                for ( size_t row = start_row; row < end_row; ++row )
                {
                    for ( size_t col = 0; col < w; ++col )
                    {
                        gfx::core::Vector2f pos( static_cast<float>( col ),
                                                 static_cast<float>( row ) );
                        gfx::core::Color    color = model_.scenes[model_.active_scene_idx]
                                                     .calcPixelColor( row, col, background_color_ );
                        pixels_[row * w + col] = gfx::core::Vertex( pos, color );
                    }
                }
            } );
        }

        for ( auto& worker : workers )
        {
            worker.join();
        }
    }

    void
    draw( gfx::core::Window& window, gfx::core::Transform transform ) const override final
    {
        gfx::core::Transform widget_transform = transform.combine( getTransform() );

        // // std::cerr << __PRETTY_FUNCTION__ << std::endl;

        window.draw( pixels_.data(),
                     pixels_.size(),
                     gfx::core::PrimitiveType::Points,
                     widget_transform );
    }

  private:
    model::ScenesManager           model_;
    gfx::core::Color               background_color_;
    std::vector<gfx::core::Vertex> pixels_;
};

} // namespace view
} // namespace zemax
