#pragma once

#include "custom-hui-impl/widget.hpp"
#include "dr4/texture.hpp"
#include "gfx/core/color.hpp"
#include "gfx/core/font.hpp"
#include "gfx/core/primitive_type.hpp"
#include "gfx/core/rect.hpp"
#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/text.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/vector3.hpp"
#include "gfx/core/vertex.hpp"
#include "gfx/core/window.hpp"

#include "gfx/ui/event.hpp"
#include "zemax/config.hpp"
#include "zemax/model/primitives/material.hpp"
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

class Scene : public hui::Widget {
  public:
    ~Scene() = default;

    explicit Scene( cum::PluginManager*        pm,
                    const dr4::Font*           font,
                    const dr4::Vec2f&          pos,
                    const dr4::Vec2f&          size,
                    const dr4::Color&          background_color,
                    const gfx::core::Vector3f& camera_pos )
        : hui::Widget( pm, pos, size ),
          model_( zemax::Config::Camera::Position, size.x, size.y ),
          background_color_( background_color ),
          info_panel_( pm, font, Config::Scene::ObjInfoPanel::Size )
    {
        // texture_ = window->CreateTexture();
        //
        // texture_->SetSize( zemax::Config::Scene::Size );

        // // fprintf( stderr, "debug in %s:%d:%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ );

        // std::cerr << pixels_ << std::endl;

        pixels_ = window_->CreateImage();

        pixels_->SetSize( size );

        // // fprintf( stderr, "debug in %s:%d:%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ );

        info_panel_.setParent( this );

        // // fprintf( stderr, "debug in %s:%d:%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ );

        camera_pos_text_.font     = font;
        camera_pos_text_.color    = { 255, 255, 255, 255 };
        camera_pos_text_.fontSize = 16;
        camera_pos_text_.pos      = { 5.0f, 5.0f };

        // // fprintf( stderr, "debug in %s:%d:%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ );

        border_.rect.size       = size;
        border_.fill            = { 0, 0, 0, 0 };
        border_.borderColor     = { 118, 185, 0, 255 };
        border_.borderThickness = 2.0f;

        // // fprintf( stderr, "debug in %s:%d:%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ );

        model_.addLight( gfx::core::Vector3f( 3, 3, -3 ), 1.0, 0.3, 0.9 );
        model_.addLight( gfx::core::Vector3f( 0, 0, -11 ), 0.2, 0.3, 0.9 );

        // // fprintf( stderr, "debug in %s:%d:%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ );

        // model_.addTorus( model::Material( gfx::core::Color( 118, 185, 0 ) ), { 0, 0, -5 }, 1, 2
        // );

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

        // model_.addAABB( model::Material( gfx::core::Color( 118, 185, 0 ), 0.9f
        // ),
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

        // model_.addSphere( model::Material( gfx::core::Color( 8, 32, 8 ), 0.3f
        // ),
        //   gfx::core::Vector3f( -2, 1, -1 ),
        //   1.5 );

        model_.addAABB( model::Material( gfx::core::Color( 58, 90, 0 ) ),
                        gfx::core::Vector3f( 0, -3.5f, -12 ),
                        gfx::core::Vector3f( 5.0f, 0.1, 5.0f ) );
        model_.addAABB( model::Material( gfx::core::Color( 58, 90, 0 ) ),
                        gfx::core::Vector3f( 0, 5.0f, -12 ),
                        gfx::core::Vector3f( 5.0f, 0.1, 5.0f ) );

        // model_.addHexPrism( model::Material( gfx::core::Color( 32, 255, 32 ), 0.3f ),
        // gfx::core::Vector3f( -3, 0, -6 ),
        // 1.0f, // R
        // 2.0f  // r
        // );

        // model_.addPlane( model::Material( gfx::core::Color( 1, 8, 127 ), 0.5f
        // ),
        //  gfx::core::Vector3f( -5, -5, -5 ),
        //  gfx::core::Vector3f( 1, 1, 1 ) );

        // // fprintf( stderr, "debug in %s:%d:%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ );
    }

    void
    setFont( const dr4::Font* font )
    {
        info_panel_.setFont( font );
    }

    model::SceneManager&
    getModel()
    {
        return model_;
    }

    virtual bool
    onIdle( const hui::Event& event ) override final
    {
        update();
        model_.needUpdate() = false;

        return false;
    }

    virtual bool
    onMousePress( const hui::Event& event ) override final
    {
        if ( !isHovered() )
        {
            return false;
        }

        auto px = event.info.mouseButton.pos.x - getAbsPos().x;
        auto py = event.info.mouseButton.pos.y - getAbsPos().y;

        model::Primitive* obj = model_.getIntersectedObj( px, py );

        // if ( model_.getTargetObj() != nullptr )
        // {
        // model_.getTargetObj()->revert_paint();
        // }

        model_.setTargetObj( obj );

        if ( obj != nullptr )
        {
            info_panel_.setRelPos( px, py );
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
                        gfx::core::Color color = model_.calcPixelColor( row,
                                                                        col,
                                                                        { background_color_.r,
                                                                          background_color_.g,
                                                                          background_color_.b,
                                                                          background_color_.a } );
                        pixels_->SetPixel( col, row, { color.r, color.g, color.b, color.a } );
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

        camera_pos_text_.text = oss.str();
    }

  public:
    void
    RedrawMyTexture() const override final
    {
        // gfx::core::Transform widget_transform = transform.combine( getTransform() );

        // dr4::Rectangle cp = border_;
        // cp.rect.pos       = { 1, 1 };

        texture_->Draw( *pixels_, { 0, 0 } );

        // window.draw( border_, widget_transform );

        // window.draw( pixels_.data(),
        //  pixels_.size(),
        //  gfx::core::PrimitiveType::Points,
        //  widget_transform );

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

            // std::vector<gfx::core::Vertex> outline = {
            // { { min_x, min_y }, gfx::core::Color::Red },
            // { { max_x, min_y }, gfx::core::Color::Red },
            // { { max_x, max_y }, gfx::core::Color::Red },
            // { { min_x, max_y }, gfx::core::Color::Red },
            // { { min_x, min_y }, gfx::core::Color::Red } };

            dr4::Rectangle rect;
            rect.rect.pos        = { min_x, min_y };
            rect.rect.size       = { max_x - min_x, max_y - min_y };
            rect.fill            = { 0, 0, 0, 0 };
            rect.borderColor     = { 255, 0, 0, 255 };
            rect.borderThickness = 2.0f;

            texture_->Draw( rect );
            //
            // window.draw( outline.data(),
            //  outline.size(),
            //  gfx::core::PrimitiveType::LineStrip,
            //  widget_transform );
        }

        info_panel_.Redraw();

        texture_->Draw( camera_pos_text_ );

        texture_->Draw( border_ );

        // parent_->getTexture()->Draw( *texture_, pos_ );
    }

  private:
    dr4::Text           camera_pos_text_;
    dr4::Rectangle      border_;
    model::SceneManager model_;
    dr4::Color          background_color_;
    view::ObjInfoPanel  info_panel_;
    dr4::Image*         pixels_;
};

} // namespace view
} // namespace zemax
