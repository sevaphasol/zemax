#pragma once

#include "gfx/core/event.hpp"
#include "gfx/core/font.hpp"
#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"
#include "gfx/ui/button.hpp"
#include "gfx/ui/container_widget.hpp"
#include "gfx/ui/scrollbar.hpp"
#include "gfx/ui/text_field.hpp"
#include "gfx/ui/widget.hpp"
#include "zemax/config.hpp"
#include "zemax/model/rendering/scene_manager.hpp"
#include "zemax/view/scrollable_buttons_widget.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

namespace zemax {
namespace view {

class ControlPanel : public gfx::ui::ContainerWidget {
  public:
    explicit ControlPanel( zemax::model::SceneManager& scene_manager )
        : scene_manager_( scene_manager ),
          camera_( scene_manager.getCamera() ),
          scrollbar_( Config::ControlPanel::ScrollBar::Position,
                      Config::ControlPanel::ScrollBar::Size )
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
        setupButton( ButtonCode::ScaleUp,
                     Config::ControlPanel::Button::ScaleUp::Position,
                     Config::ControlPanel::Button::ScaleUp::Title );
        setupButton( ButtonCode::ScaleDown,
                     Config::ControlPanel::Button::ScaleDown::Position,
                     Config::ControlPanel::Button::ScaleDown::Title );

        setupButton( ButtonCode::MoveObjLeft,
                     Config::ControlPanel::Button::MoveObjLeft::Position,
                     Config::ControlPanel::Button::MoveObjLeft::Title );
        setupButton( ButtonCode::MoveObjRight,
                     Config::ControlPanel::Button::MoveObjRight::Position,
                     Config::ControlPanel::Button::MoveObjRight::Title );
        setupButton( ButtonCode::MoveObjUp,
                     Config::ControlPanel::Button::MoveObjUp::Position,
                     Config::ControlPanel::Button::MoveObjUp::Title );
        setupButton( ButtonCode::MoveObjDown,
                     Config::ControlPanel::Button::MoveObjDown::Position,
                     Config::ControlPanel::Button::MoveObjDown::Title );
        setupButton( ButtonCode::MoveObjForward,
                     Config::ControlPanel::Button::MoveObjForwrd::Position,
                     Config::ControlPanel::Button::MoveObjForwrd::Title );
        setupButton( ButtonCode::MoveObjBackward,
                     Config::ControlPanel::Button::MoveObjBackward::Position,
                     Config::ControlPanel::Button::MoveObjBackward::Title );

        setupButton( ButtonCode::AddObj,
                     Config::ControlPanel::Button::AddObj::Position,
                     Config::ControlPanel::Button::AddObj::Title );
        setupButton( ButtonCode::CopyObj,
                     Config::ControlPanel::Button::CopyObj::Position,
                     Config::ControlPanel::Button::CopyObj::Title );
        setupButton( ButtonCode::DeleteObj,
                     Config::ControlPanel::Button::DeleteObj::Position,
                     Config::ControlPanel::Button::DeleteObj::Title );

        setupTextField( TextFieldCode::NewObjX, Config::ControlPanel::TextField::X::Position );
        setupTextField( TextFieldCode::NewObjY, Config::ControlPanel::TextField::Y::Position );
        setupTextField( TextFieldCode::NewObjZ, Config::ControlPanel::TextField::Z::Position );

        scrollbar_.parent_ = this;
        setupScrollBarButton( ScrollBarButtonCode::Sphere, "Sphere" );
        setupScrollBarButton( ScrollBarButtonCode::Plane, "Plane" );
        setupScrollBarButton( ScrollBarButtonCode::AABB, "AABB" );
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

        for ( const auto& text_field : text_fields_ )
        {
            if ( event.apply( text_field.get() ) )
            {
                return true;
            }
        }

        return event.apply( &scrollbar_ );
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
        if ( isPressed( ScaleUp ) )
        {
            scene_manager_.getCamera().scale( -Config::Camera::ScaleFactor );
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( ScaleDown ) )
        {
            scene_manager_.getCamera().scale( Config::Camera::ScaleFactor );
            scene_manager_.needUpdate() = true;
        }

        if ( isPressed( MoveObjLeft ) )
        {
            scene_manager_.getTargetObj()->move(
                gfx::core::Vector3f( -Config::Camera::ObjMoveFactor, 0, 0 ) );
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( MoveObjRight ) )
        {
            scene_manager_.getTargetObj()->move(
                gfx::core::Vector3f( Config::Camera::ObjMoveFactor, 0, 0 ) );
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( MoveObjUp ) )
        {
            scene_manager_.getTargetObj()->move(
                gfx::core::Vector3f( 0, Config::Camera::ObjMoveFactor, 0 ) );
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( MoveObjDown ) )
        {
            scene_manager_.getTargetObj()->move(
                gfx::core::Vector3f( 0, -Config::Camera::ObjMoveFactor, 0 ) );
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( MoveObjForward ) )
        {
            scene_manager_.getTargetObj()->move(
                gfx::core::Vector3f( 0, 0, -Config::Camera::ObjMoveFactor ) );
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( MoveObjBackward ) )
        {
            scene_manager_.getTargetObj()->move(
                gfx::core::Vector3f( 0, 0, Config::Camera::ObjMoveFactor ) );
            scene_manager_.needUpdate() = true;
        }

        if ( isPressed( AddObj ) )
        {
            std::cerr << "AddObj" << std::endl;
            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( CopyObj ) )
        {
            std::cerr << "CopyObj" << std::endl;
            float new_obj_x = text_fields_[TextFieldCode::NewObjX]->strToDouble();
            float new_obj_y = text_fields_[TextFieldCode::NewObjY]->strToDouble();
            float new_obj_z = text_fields_[TextFieldCode::NewObjZ]->strToDouble();

            if ( !std::isnan( new_obj_x ) && !std::isnan( new_obj_y ) && !std::isnan( new_obj_z ) )
            {
                scene_manager_.copyTargetObj( new_obj_x, new_obj_y, new_obj_z );
            }

            scene_manager_.needUpdate() = true;
        }
        if ( isPressed( DeleteObj ) )
        {
            scene_manager_.deleteTargetObj();
            scene_manager_.needUpdate() = true;
        }

        propagateEventToChildren( event );

        return false;
    }

  private:
    gfx::core::Font labels_font_;

    enum ButtonCode {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        MoveForward,
        MoveBackward,
        RotateLeft,
        RotateRight,
        RotateUp,
        RotateDown,
        ScaleUp,
        ScaleDown,
        MoveObjLeft,
        MoveObjRight,
        MoveObjUp,
        MoveObjDown,
        MoveObjForward,
        MoveObjBackward,
        AddObj,
        CopyObj,
        DeleteObj,
        ButtonCount,
    };

    std::unique_ptr<gfx::ui::Button> buttons_[ButtonCount];

    enum TextFieldCode {
        NewObjX = 0,
        NewObjY = 1,
        NewObjZ = 2,
        TextFieldCount,
    };

    std::unique_ptr<gfx::ui::TextField> text_fields_[TextFieldCount];

    enum ScrollBarButtonCode {
        Sphere = 0,
        Plane  = 1,
        AABB   = 2,
        ScrollBarButtonCodeCount,
    };

    ScrollableButtonsWidget scrollbar_;

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
        buttons_[code]->parent_ = this;
    }

    void
    setupTextField( TextFieldCode code, const gfx::core::Vector2f& pos )
    {
        text_fields_[code] = std::move(
            std::make_unique<gfx::ui::TextField>( labels_font_,
                                                  pos,
                                                  Config::ControlPanel::TextField::Size ) );
        text_fields_[code]->parent_ = this;
    }

    void
    setupScrollBarButton( ScrollBarButtonCode code, const char* label )
    {
        scrollbar_.addButton(
            std::make_unique<gfx::ui::Button>( Config::ControlPanel::ScrollBar::Button::Position,
                                               Config::ControlPanel::ScrollBar::Button::Size,
                                               Config::ControlPanel::Button::DefaultColor,
                                               Config::ControlPanel::Button::HoveredColor,
                                               Config::ControlPanel::Button::PressedColor,
                                               labels_font_,
                                               label,
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

        for ( const auto& text_field : text_fields_ )
        {
            window.draw( *text_field, widget_transform );
        }

        window.draw( scrollbar_, widget_transform );
    }

  private:
    zemax::model::SceneManager& scene_manager_;
    zemax::model::Camera&       camera_;

    gfx::core::RectangleShape border_;
};

} // namespace view
} // namespace zemax
