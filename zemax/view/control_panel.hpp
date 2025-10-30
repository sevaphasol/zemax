#pragma once

#include "gfx/core/event.hpp"
#include "gfx/core/font.hpp"
#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"
#include "gfx/ui/button.hpp"
#include "gfx/ui/container_widget.hpp"
#include "gfx/ui/scrollbar.hpp"
#include "gfx/ui/widget.hpp"
#include "zemax/config.hpp"
#include "zemax/model/rendering/scene_manager.hpp"
#include "zemax/view/scrollable_buttons_widget.hpp"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

namespace zemax {
namespace view {

class ControlPanel : public gfx::ui::ContainerWidget {
  public:
    explicit ControlPanel( zemax::model::SceneManager& scene_manager )
        : scene_manager_( scene_manager ), camera_( scene_manager.getCamera() )
    //   scrollbar_( Config::ControlPanel::ScrollBar::Position.x,
    //               Config::ControlPanel::ScrollBar::Position.y,
    //               125,
    //               200 )

    {
        loadFont( Config::ControlPanel::Button::FontName );

        setPosition( Config::ControlPanel::Position );
        setSize( Config::ControlPanel::Size );

        border_.setSize( getSize() );
        border_.setFillColor( Config::ControlPanel::BackgroundColor );
        border_.setOutlineColor( Config::ControlPanel::BorderColor );
        border_.setOutlineThickness( Config::ControlPanel::BorderThickness );

        setupButton( ButtonCode::MoveLeft,
                     Config::ControlPanel::Button::MvL::Position,
                     Config::ControlPanel::Button::MvL::Title );
        setupButton( ButtonCode::MoveRight,
                     Config::ControlPanel::Button::MvR::Position,
                     Config::ControlPanel::Button::MvR::Title );
        setupButton( ButtonCode::MoveUp,
                     Config::ControlPanel::Button::MvU::Position,
                     Config::ControlPanel::Button::MvU::Title );
        setupButton( ButtonCode::MoveDown,
                     Config::ControlPanel::Button::MvD::Position,
                     Config::ControlPanel::Button::MvD::Title );
        setupButton( ButtonCode::MoveForward,
                     Config::ControlPanel::Button::MvF::Position,
                     Config::ControlPanel::Button::MvF::Title );
        setupButton( ButtonCode::MoveBackward,
                     Config::ControlPanel::Button::MvB::Position,
                     Config::ControlPanel::Button::MvB::Title );
        setupButton( ButtonCode::RotateLeft,
                     Config::ControlPanel::Button::RtL::Position,
                     Config::ControlPanel::Button::RtL::Title );
        setupButton( ButtonCode::RotateRight,
                     Config::ControlPanel::Button::RtR::Position,
                     Config::ControlPanel::Button::RtR::Title );
        setupButton( ButtonCode::RotateUp,
                     Config::ControlPanel::Button::RtU::Position,
                     Config::ControlPanel::Button::RtU::Title );
        setupButton( ButtonCode::RotateDown,
                     Config::ControlPanel::Button::RtD::Position,
                     Config::ControlPanel::Button::RtD::Title );
        setupButton( ButtonCode::DeleteObj,
                     Config::ControlPanel::Button::DelObj::Position,
                     Config::ControlPanel::Button::DelObj::Title );

        //         scrollbar_.parent_ = this;
        //
        //         for ( size_t i = 0; i < scene_manager.getObjectsCount(); i++ )
        //         {
        //             scrollbar_.addButton(
        //                 scene_manager_.getObjectInfo( i ),
        //                 std::make_unique<gfx::ui::Button>(
        //                     gfx::core::Vector2f( 25, 0 ),
        //                     gfx::core::Vector2f( Config::ControlPanel::Button::Size.x, 200 ),
        //                     Config::ControlPanel::Button::DefaultColor,
        //                     Config::ControlPanel::Button::HoveredColor,
        //                     Config::ControlPanel::Button::PressedColor,
        //                     labels_font_,
        //                     getObjInfoString( scene_manager_.getObjectInfo( i ) ),
        //                     Config::ControlPanel::Button::FontColor,
        //                     Config::ControlPanel::Button::FontSize ) );
        //         }
    }

    static std::string
    getObjInfoString( model::SceneManager::ObjectInfo info )
    {
        std::stringstream ss;

        ss << info.pos.x << " " << info.pos.y << " " << info.pos.z << "\n";
        ss << info.type_name;

        return ss.str();
    }

    bool
    propagateEventToChildren( const gfx::ui::Event& event ) override
    {
        for ( const auto& button : buttons_ )
        {
            if ( event.apply( button.get() ) )
            {
                return true;
            }
        }

        return false;
        // return event.apply( &scrollbar_ );
    }

    virtual bool
    onIdle( const gfx::ui::Event& event ) override final
    {
        if ( isPressed( MoveLeft ) )
        {
            scene_manager_.getCamera().move( { -Config::Camera::MoveFactor, 0.0f, 0.0f } );
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( MoveRight ) )
        {

            scene_manager_.getCamera().move( { Config::Camera::MoveFactor, 0.0f, 0.0f } );
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( MoveUp ) )
        {

            scene_manager_.getCamera().move( { 0.0f, Config::Camera::MoveFactor, 0.0f } );
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( MoveDown ) )
        {
            scene_manager_.getCamera().move( { 0.0f, -Config::Camera::MoveFactor, 0.0f } );
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( MoveForward ) )
        {

            scene_manager_.getCamera().move( { 0.0f, 0.0f, -Config::Camera::MoveFactor } );
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( MoveBackward ) )
        {
            scene_manager_.getCamera().move( { 0.0f, 0.0f, Config::Camera::MoveFactor } );
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( RotateLeft ) )
        {
            scene_manager_.getCamera().rotate( { Config::Camera::RotateFactor, 0.0f } );
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( RotateRight ) )
        {
            scene_manager_.getCamera().rotate( { -Config::Camera::RotateFactor, 0.0f } );
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( RotateUp ) )
        {
            scene_manager_.getCamera().rotate( { 0.0f, -Config::Camera::RotateFactor } );
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( RotateDown ) )
        {
            scene_manager_.getCamera().rotate( { 0.0f, Config::Camera::RotateFactor } );
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( DeleteObj ) )
        {
            scene_manager_.deleteTargetObj();
            scene_manager_.needUpdate() = true;
        }

        //         if ( scrollbar_.isScrolled() )
        //         {
        //             auto& cur_active_obj_ctx  = scrollbar_.getButtonCtx(
        //             scrollbar_.getCurActiveButton() ); auto& prev_active_obj_ctx =
        //             scrollbar_.getButtonCtx( scrollbar_.getPrevActiveButton() );
        //
        //             scene_manager_.revert_paint( prev_active_obj_ctx.obj_info.objects_idx );
        //             scene_manager_.paint( cur_active_obj_ctx.obj_info.objects_idx );
        //         }
        //
        //         if ( scrollbar_.isActiveButtonPressed() )
        //         {
        //             // std::cerr << "Pressed" << std::endl;
        //
        //             // auto& obj_ctx = scrollbar_.getButtonCtx( scrollbar_.getActiveButton() );
        //
        //             // scene_manager_.paint( obj_ctx.obj_info.objects_idx );
        //         }

        propagateEventToChildren( event );

        return false;
    }

  private:
    enum ButtonCode {
        MoveLeft     = 0,
        MoveRight    = 1,
        MoveUp       = 2,
        MoveDown     = 3,
        MoveForward  = 4,
        MoveBackward = 5,
        RotateLeft   = 6,
        RotateRight  = 7,
        RotateUp     = 8,
        RotateDown   = 9,
        DeleteObj    = 10,
        Count,
    };

    std::unique_ptr<gfx::ui::Button> buttons_[ButtonCode::Count];

    // ScrollableButtonsWidget scrollbar_;

    void
    loadFont( const std::string& font_name )
    {
        labels_font_.loadFromFile( font_name );
    }

    bool
    isPressed( ButtonCode code )
    {
        return dynamic_cast<gfx::ui::Button*>( buttons_[code].get() )->isPressed();
    }

    void
    setupButton( ButtonCode code, const gfx::core::Vector2f& pos, const char* title )
    {
        buttons_[code] = std::move(
            std::make_unique<gfx::ui::Button>( pos,
                                               Config::ControlPanel::Button::Size,
                                               Config::ControlPanel::Button::DefaultColor,
                                               Config::ControlPanel::Button::HoveredColor,
                                               Config::ControlPanel::Button::PressedColor,
                                               labels_font_,
                                               title,
                                               Config::ControlPanel::Button::FontColor,
                                               Config::ControlPanel::Button::FontSize ) );
    }

    virtual void
    draw( gfx::core::Window& window, gfx::core::Transform transform ) const override final
    {
        gfx::core::Transform widget_transform = transform.combine( getTransform() );

        window.draw( border_, widget_transform );

        for ( const auto& button : buttons_ )
        {
            window.draw( *button, widget_transform );
        }

        // window.draw( scrollbar_, widget_transform );
    }

  private:
    zemax::model::SceneManager& scene_manager_;
    zemax::model::Camera&       camera_;

    gfx::core::RectangleShape border_;
    gfx::core::Font           labels_font_;
};

} // namespace view
} // namespace zemax
