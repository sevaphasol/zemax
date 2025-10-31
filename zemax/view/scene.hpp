#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/font.hpp"
#include "gfx/core/primitive_type.hpp"
#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/text.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/vector3.hpp"
#include "gfx/core/vertex.hpp"
#include "gfx/core/window.hpp"

#include "gfx/ui/event.hpp"
#include "zemax/config.hpp"
#include "zemax/model/primitives/primitive.hpp"
#include "zemax/model/rendering/camera.hpp"
#include "zemax/model/rendering/scene_manager.hpp"
#include "zemax/view/info_panel.hpp"

#include <cstddef>
#include <iomanip>
#include <sstream>
#include <thread>
#include <vector>

namespace zemax {
namespace view {

class Scene : public gfx::ui::Widget {
  public:
    ~Scene() = default;

    explicit Scene( const gfx::core::Font&     font,
                    const gfx::core::Vector2f& pos,
                    const gfx::core::Vector2f& size,
                    const gfx::core::Color&    background_color,
                    const gfx::core::Vector3f& camera_pos )
        : gfx::ui::Widget( pos, size ),
          model_( zemax::Config::Camera::Position, size.x, size.y ),
          background_color_( background_color ),
          info_panel_( font, Config::Scene::ObjInfoPanel::Size ),
          pixels_( size.x * size.y )
    {
        info_panel_.parent_ = this;

        camera_pos_text_.setFont( font );
        camera_pos_text_.setFillColor( gfx::core::Color::White );
        camera_pos_text_.setCharacterSize( 16 );

        border_.setSize( size );
        border_.setFillColor( gfx::core::Color::Transparent );
        border_.setOutlineColor( { 118, 185, 0 } );
        border_.setOutlineThickness( 2.0f );

        model_.addLight( gfx::core::Vector3f( 3, 3, -3 ), 1.0, 0.3, 0.9 );
        model_.addLight( gfx::core::Vector3f( 0, 0, -11 ), 0.2, 0.3, 0.9 );

        model_.addAABB( model::Material( gfx::core::Color( 255, 8, 8 ), 0.8f ),
                        gfx::core::Vector3f( -2, 1, -8 ),
                        gfx::core::Vector3f( 0.75, 0.75, -6.75 ) );

        // model_.addAABB( model::Material( gfx::core::Color( 8, 8, 8 ), 0.5f ),
        //                 gfx::core::Vector3f( -1, 0.5, -5 ),
        //                 gfx::core::Vector3f( 0.25, 0.25, 0.25 ) );

        model_.addSphere( model::Material( gfx::core::Color( 8, 32, 8 ), 1.0f ),
                          gfx::core::Vector3f( 0, 0, -13 ),
                          0.3 );

        model_.addSphere( model::Material( gfx::core::Color( 8, 32, 8 ), 0.3f ),
                          gfx::core::Vector3f( 2, 2, -13 ),
                          1.5 );

        model_.addSphere( model::Material( gfx::core::Color( 118, 185, 0 ), 0.9f ),
                          gfx::core::Vector3f( 0, 3, -16 ),
                          1.5 );

        // model_.addAABB( model::Material( gfx::core::Color( 118, 185, 0 ), 0.9f ),
        //                 gfx::core::Vector3f( 0, -1, -8 ),
        //                 { 1.5, 0.5, 1.5 } );

        model_.addAABB( model::Material( gfx::core::Color( 118, 185, 0 ), 0.95f ),
                        gfx::core::Vector3f( -4, 0, -12 ),
                        { 0.1, 3, 3 } );

        model_.addAABB( model::Material( gfx::core::Color( 118, 185, 0 ), 0.95f ),
                        gfx::core::Vector3f( 4, 0, -12 ),
                        { 0.1, 3, 3 } );

        model_.addAABB( model::Material( gfx::core::Color( 118, 185, 0 ), 0.95f ),
                        gfx::core::Vector3f( 0, 0, -18 ),
                        { 3, 3, 0.1 } );

        // model_.addSphere( model::Material( gfx::core::Color( 8, 32, 8 ), 0.3f ),
        //   gfx::core::Vector3f( -2, 1, -1 ),
        //   1.5 );

        model_.addAABB( model::Material( gfx::core::Color( 58, 90, 0 ) ),
                        gfx::core::Vector3f( 0, -3.5f, -12 ),
                        gfx::core::Vector3f( 5.0f, 0.1, 5.0f ) );
        model_.addAABB( model::Material( gfx::core::Color( 58, 90, 0 ) ),
                        gfx::core::Vector3f( 0, 5.0f, -12 ),
                        gfx::core::Vector3f( 5.0f, 0.1, 5.0f ) );
        // model_.addPlane( model::Material( gfx::core::Color( 1, 8, 127 ), 0.5f ),
        //  gfx::core::Vector3f( -5, -5, -5 ),
        //  gfx::core::Vector3f( 1, 1, 1 ) );
    }

    void
    setFont( const gfx::core::Font& font )
    {
        info_panel_.setFont( font );
    }

    model::SceneManager&
    getModel()
    {
        return model_;
    }

    virtual bool
    onIdle( const gfx::ui::Event& event ) override final
    {
        update();
        model_.needUpdate() = false;

        return false;
    }

    virtual bool
    onMousePress( const gfx::ui::Event& event ) override final
    {
        if ( !isHovered() )
        {
            return false;
        }

        auto px = event.info.mouse_button.x - getAbsPos().x;
        auto py = event.info.mouse_button.y - getAbsPos().y;

        model::Primitive* obj = model_.getIntersectedObj( px, py );

        std::cerr << model_.getTargetObj() << std::endl;
        std::cerr << obj << std::endl;

        // if ( model_.getTargetObj() != nullptr )
        // {
        // model_.getTargetObj()->revert_paint();
        // }

        model_.setTargetObj( obj );

        if ( obj != nullptr )
        {
            info_panel_.setPosition( px, py );
            info_panel_.update( obj );
            info_panel_.setVisible( true );
        } else
        {
            info_panel_.setVisible( false );
        }

        // if ( obj != nullptr )
        // {
        // model_.getTargetObj()->paint();
        // }

        return true;
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
                        gfx::core::Color    color =
                            model_.calcPixelColor( row, col, background_color_ );
                        pixels_[row * w + col] = gfx::core::Vertex( pos, color );
                    }
                }
            } );
        }

        for ( auto& worker : workers )
        {
            worker.join();
        }

        setCameraPosString();
    }

    void
    setCameraPosString()
    {
        auto cam_pos = model_.getCamera().getPos();

        std::ostringstream oss;
        oss << "( " << std::fixed << std::setprecision( 1 ) << cam_pos.x << ", " << cam_pos.y
            << ", " << cam_pos.z << " )";

        camera_pos_text_.setString( oss.str() );
    }

    void
    draw( gfx::core::Window& window, gfx::core::Transform transform ) const override final
    {
        gfx::core::Transform widget_transform = transform.combine( getTransform() );

        window.draw( border_, widget_transform );

        window.draw( pixels_.data(),
                     pixels_.size(),
                     gfx::core::PrimitiveType::Points,
                     widget_transform );

        if ( model_.getTargetObj() != nullptr )
        {
            auto corners3d = model_.getTargetObj()->getCircumscribedAABB();

            float min_x = std::numeric_limits<float>::max();
            float min_y = std::numeric_limits<float>::max();
            float max_x = -std::numeric_limits<float>::max();
            float max_y = -std::numeric_limits<float>::max();

            float scr_w = getSize().x;
            float scr_h = getSize().y;

            for ( const auto& p3d : corners3d )
            {
                auto p2d = model_.getCamera().projectToScreen( p3d );

                if ( p2d.has_value() )
                {
                    min_x = std::max( 0.0f, std::min( min_x, p2d.value().x ) );
                    max_x = std::min( scr_w, std::max( max_x, p2d.value().x ) );
                    min_y = std::max( 0.0f, std::min( min_y, p2d.value().y ) );
                    max_y = std::min( scr_h, std::max( max_y, p2d.value().y ) );
                }
            }

            std::vector<gfx::core::Vertex> outline = {
                { { min_x, min_y }, gfx::core::Color::Red },
                { { max_x, min_y }, gfx::core::Color::Red },
                { { max_x, max_y }, gfx::core::Color::Red },
                { { min_x, max_y }, gfx::core::Color::Red },
                { { min_x, min_y }, gfx::core::Color::Red } };

            window.draw( outline.data(),
                         outline.size(),
                         gfx::core::PrimitiveType::LineStrip,
                         widget_transform );
        }

        window.draw( info_panel_, widget_transform );
        window.draw( camera_pos_text_, widget_transform );
    }

  private:
    gfx::core::Text                camera_pos_text_;
    gfx::core::RectangleShape      border_;
    model::SceneManager            model_;
    gfx::core::Color               background_color_;
    view::ObjInfoPanel             info_panel_;
    std::vector<gfx::core::Vertex> pixels_;
};

} // namespace view
} // namespace zemax
