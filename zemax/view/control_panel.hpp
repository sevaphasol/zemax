#pragma once

#include "gfx/core/event.hpp"
#include "gfx/core/font.hpp"
#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"
#include "gfx/ui/button.hpp"
#include "gfx/ui/container_widget.hpp"
#include "gfx/ui/scrollable_buttons_widget.hpp"
#include "gfx/ui/scrollbar.hpp"
#include "gfx/ui/widget.hpp"
#include "zemax/config.hpp"
#include "zemax/model/rendering/scenes_manager.hpp"
#include <iostream>
#include <memory>

namespace zemax {
namespace view {

class ControlPanel : public gfx::ui::VectorContainerWidget {
  public:
    explicit ControlPanel( zemax::model::ScenesManager& scenes_manager )
        : scenes_manager_( scenes_manager ), camera_( scenes_manager.getActiveScene().getCamera() )
    {
        loadFont( Config::ControlPanel::Button::FontName );

        setPosition( Config::ControlPanel::Position );
        setSize( Config::ControlPanel::Size );

        border_.setSize( getSize() );
        border_.setFillColor( Config::ControlPanel::BackgroundColor );
        border_.setOutlineColor( Config::ControlPanel::BorderColor );
        border_.setOutlineThickness( Config::ControlPanel::BorderThickness );

        setupButton( Config::ControlPanel::Button::MvL::Position,
                     Config::ControlPanel::Button::MvL::Title );
        setupButton( Config::ControlPanel::Button::MvR::Position,
                     Config::ControlPanel::Button::MvR::Title );
        setupButton( Config::ControlPanel::Button::MvU::Position,
                     Config::ControlPanel::Button::MvU::Title );
        setupButton( Config::ControlPanel::Button::MvD::Position,
                     Config::ControlPanel::Button::MvD::Title );
        setupButton( Config::ControlPanel::Button::MvF::Position,
                     Config::ControlPanel::Button::MvF::Title );
        setupButton( Config::ControlPanel::Button::MvB::Position,
                     Config::ControlPanel::Button::MvB::Title );
        setupButton( Config::ControlPanel::Button::RtL::Position,
                     Config::ControlPanel::Button::RtL::Title );
        setupButton( Config::ControlPanel::Button::RtR::Position,
                     Config::ControlPanel::Button::RtR::Title );
        setupButton( Config::ControlPanel::Button::RtU::Position,
                     Config::ControlPanel::Button::RtU::Title );
        setupButton( Config::ControlPanel::Button::RtD::Position,
                     Config::ControlPanel::Button::RtD::Title );
        setupScrollBar( Config::ControlPanel::ScrollBar::Position );

        addChild( std::make_unique<gfx::ui::ScrollableButtonsWidget>( 150, 450, 125, 200 ) );

        children_[ObjectsInfo]->parent_ = this;

        dynamic_cast<gfx::ui::ScrollableButtonsWidget*>( children_[ObjectsInfo].get() )
            ->addButton( std::make_unique<gfx::ui::Button>(
                gfx::core::Vector2f( 25, 0 ),
                gfx::core::Vector2f( Config::ControlPanel::Button::Size.x, 200 ),
                Config::ControlPanel::Button::DefaultColor,
                Config::ControlPanel::Button::HoveredColor,
                Config::ControlPanel::Button::PressedColor,
                labels_font_,
                "TestBtn1",
                Config::ControlPanel::Button::FontColor,
                Config::ControlPanel::Button::FontSize ) );
        dynamic_cast<gfx::ui::ScrollableButtonsWidget*>( children_[ObjectsInfo].get() )
            ->addButton( std::make_unique<gfx::ui::Button>(
                gfx::core::Vector2f( 25, 0 ),
                gfx::core::Vector2f( Config::ControlPanel::Button::Size.x, 200 ),
                Config::ControlPanel::Button::DefaultColor,
                Config::ControlPanel::Button::HoveredColor,
                Config::ControlPanel::Button::PressedColor,
                labels_font_,
                "TestBtn2",
                Config::ControlPanel::Button::FontColor,
                Config::ControlPanel::Button::FontSize ) );
    }

    virtual bool
    onIdle( const gfx::ui::Event& event ) override final
    {
        if ( isPressed( MoveLeft ) )
        {
            scenes_manager_.getActiveScene().getCamera().move(
                { -Config::Camera::MoveFactor, 0.0f, 0.0f } );
            scenes_manager_.getActiveScene().needUpdate() = true;
        }
        if ( isPressed( MoveRight ) )
        {

            scenes_manager_.getActiveScene().getCamera().move(
                { Config::Camera::MoveFactor, 0.0f, 0.0f } );
            scenes_manager_.getActiveScene().needUpdate() = true;
        }
        if ( isPressed( MoveUp ) )
        {

            scenes_manager_.getActiveScene().getCamera().move(
                { 0.0f, Config::Camera::MoveFactor, 0.0f } );
            scenes_manager_.getActiveScene().needUpdate() = true;
        }
        if ( isPressed( MoveDown ) )
        {
            scenes_manager_.getActiveScene().getCamera().move(
                { 0.0f, -Config::Camera::MoveFactor, 0.0f } );
            scenes_manager_.getActiveScene().needUpdate() = true;
        }
        if ( isPressed( MoveForward ) )
        {

            scenes_manager_.getActiveScene().getCamera().move(
                { 0.0f, 0.0f, -Config::Camera::MoveFactor } );
            scenes_manager_.getActiveScene().needUpdate() = true;
        }
        if ( isPressed( MoveBackward ) )
        {
            scenes_manager_.getActiveScene().getCamera().move(
                { 0.0f, 0.0f, Config::Camera::MoveFactor } );
            scenes_manager_.getActiveScene().needUpdate() = true;
        }
        if ( isPressed( RotateLeft ) )
        {
            scenes_manager_.getActiveScene().getCamera().rotate(
                { Config::Camera::RotateFactor, 0.0f } );
            scenes_manager_.getActiveScene().needUpdate() = true;
        }
        if ( isPressed( RotateRight ) )
        {
            scenes_manager_.getActiveScene().getCamera().rotate(
                { -Config::Camera::RotateFactor, 0.0f } );
            scenes_manager_.getActiveScene().needUpdate() = true;
        }
        if ( isPressed( RotateUp ) )
        {
            scenes_manager_.getActiveScene().getCamera().rotate(
                { 0.0f, -Config::Camera::RotateFactor } );
            scenes_manager_.getActiveScene().needUpdate() = true;
        }
        if ( isPressed( RotateDown ) )
        {
            scenes_manager_.getActiveScene().getCamera().rotate(
                { 0.0f, Config::Camera::RotateFactor } );
            scenes_manager_.getActiveScene().needUpdate() = true;
        }
        if ( isScrolled( ChangeScene ) )
        {
            scenes_manager_.onScroll(
                dynamic_cast<gfx::ui::ScrollBar*>( children_[ButtonCode::ChangeScene].get() )
                    ->getScrollFactor() );
            scenes_manager_.getActiveScene().needUpdate() = true;
        }

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
        ChangeScene  = 10,
        ObjectsInfo  = 11,
    };

    void
    loadFont( const std::string& font_name )
    {
        labels_font_.loadFromFile( font_name );
    }

    bool
    isPressed( ButtonCode code )
    {
        return dynamic_cast<gfx::ui::Button*>( children_[code].get() )->isPressed();
    }

    bool
    isScrolled( ButtonCode code )
    {
        return dynamic_cast<gfx::ui::ScrollBar*>( children_[code].get() )->isScrolled();
    }

    void
    setupButton( const gfx::core::Vector2f& pos, const char* title )
    {
        addChild( std::make_unique<gfx::ui::Button>( pos,
                                                     Config::ControlPanel::Button::Size,
                                                     Config::ControlPanel::Button::DefaultColor,
                                                     Config::ControlPanel::Button::HoveredColor,
                                                     Config::ControlPanel::Button::PressedColor,
                                                     labels_font_,
                                                     title,
                                                     Config::ControlPanel::Button::FontColor,
                                                     Config::ControlPanel::Button::FontSize ) );
    }

    void
    setupScrollBar( const gfx::core::Vector2f& pos )
    {
        addChild( std::make_unique<gfx::ui::ScrollBar>( pos ) );
    }

    virtual void
    draw( gfx::core::Window& window, gfx::core::Transform transform ) const override final
    {
        gfx::core::Transform widget_transform = transform.combine( getTransform() );

        window.draw( border_, widget_transform );
        drawChildren( window, widget_transform );
    }

  private:
    zemax::model::ScenesManager& scenes_manager_;
    zemax::model::Camera&        camera_;

    gfx::core::RectangleShape border_;
    gfx::core::Font           labels_font_;
};

} // namespace view
} // namespace zemax
