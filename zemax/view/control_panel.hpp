#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/font.hpp"
#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/vector3.hpp"
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
#include <optional>
#include <sstream>
#include <string>

namespace zemax {
namespace view {

class ControlPanel : public gfx::ui::ContainerWidget {
  public:
    explicit ControlPanel( const gfx::core::Font& font, zemax::model::SceneManager& scene_manager )
        : scene_manager_( scene_manager ),
          font_( font ),
          camera_( scene_manager.getCamera() ),
          scrollbar_( Config::ControlPanel::ScrollBar::Position,
                      Config::ControlPanel::ScrollBar::Size )
    {
        setDraggable( true );

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

        setupTextField( TextFieldCode::NewObjX,
                        Config::ControlPanel::TextField::X::Position,
                        Config::ControlPanel::TextField::X::Title );
        setupTextField( TextFieldCode::NewObjY,
                        Config::ControlPanel::TextField::Y::Position,
                        Config::ControlPanel::TextField::Y::Title );
        setupTextField( TextFieldCode::NewObjZ,
                        Config::ControlPanel::TextField::Z::Position,
                        Config::ControlPanel::TextField::Z::Title );
        setupTextField( TextFieldCode::NewObjS,
                        Config::ControlPanel::TextField::Size::Position,
                        Config::ControlPanel::TextField::Size::Title );
        setupTextField( TextFieldCode::NewObjR,
                        Config::ControlPanel::TextField::R::Position,
                        Config::ControlPanel::TextField::R::Title );
        setupTextField( TextFieldCode::NewObjG,
                        Config::ControlPanel::TextField::G::Position,
                        Config::ControlPanel::TextField::G::Title );
        setupTextField( TextFieldCode::NewObjB,
                        Config::ControlPanel::TextField::B::Position,
                        Config::ControlPanel::TextField::B::Title );
        setupTextField( TextFieldCode::NewObjF,
                        Config::ControlPanel::TextField::RefFactor::Position,
                        Config::ControlPanel::TextField::RefFactor::Title );

        scrollbar_.parent_ = this;
        setupScrollBarButton( ScrollBarButtonCode::Sphere, "Sphere" );
        setupScrollBarButton( ScrollBarButtonCode::Plane, "Plane" );
        setupScrollBarButton( ScrollBarButtonCode::AABB, "AABB" );
    }

    void
    setFont( const gfx::core::Font& font )
    {
        font_ = font;
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
            if ( scene_manager_.getTargetObj() != nullptr )
            {
                scene_manager_.getTargetObj()->move(
                    gfx::core::Vector3f( -Config::Camera::ObjMoveFactor, 0, 0 ) );
                scene_manager_.needUpdate() = true;
            }
        }
        if ( isPressed( MoveObjRight ) )
        {
            if ( scene_manager_.getTargetObj() != nullptr )
            {
                scene_manager_.getTargetObj()->move(
                    gfx::core::Vector3f( Config::Camera::ObjMoveFactor, 0, 0 ) );
                scene_manager_.needUpdate() = true;
            }
        }
        if ( isPressed( MoveObjUp ) )
        {
            if ( scene_manager_.getTargetObj() != nullptr )
            {
                scene_manager_.getTargetObj()->move(
                    gfx::core::Vector3f( 0, Config::Camera::ObjMoveFactor, 0 ) );
                scene_manager_.needUpdate() = true;
            }
        }
        if ( isPressed( MoveObjDown ) )
        {
            if ( scene_manager_.getTargetObj() != nullptr )
            {
                scene_manager_.getTargetObj()->move(
                    gfx::core::Vector3f( 0, -Config::Camera::ObjMoveFactor, 0 ) );
                scene_manager_.needUpdate() = true;
            }
        }
        if ( isPressed( MoveObjForward ) )
        {
            if ( scene_manager_.getTargetObj() != nullptr )
            {
                scene_manager_.getTargetObj()->move(
                    gfx::core::Vector3f( 0, 0, -Config::Camera::ObjMoveFactor ) );
                scene_manager_.needUpdate() = true;
            }
        }
        if ( isPressed( MoveObjBackward ) )
        {
            if ( scene_manager_.getTargetObj() != nullptr )
            {
                scene_manager_.getTargetObj()->move(
                    gfx::core::Vector3f( 0, 0, Config::Camera::ObjMoveFactor ) );
                scene_manager_.needUpdate() = true;
            }
        }

        if ( isPressedJustNow( AddObj ) )
        {
            auto new_obj_x = text_fields_[TextFieldCode::NewObjX]->strToDouble();
            auto new_obj_y = text_fields_[TextFieldCode::NewObjY]->strToDouble();
            auto new_obj_z = text_fields_[TextFieldCode::NewObjZ]->strToDouble();
            auto new_obj_s = text_fields_[TextFieldCode::NewObjS]->strToDouble();

            auto new_obj_r = text_fields_[TextFieldCode::NewObjR]->strToUint32();
            auto new_obj_g = text_fields_[TextFieldCode::NewObjG]->strToUint32();
            auto new_obj_b = text_fields_[TextFieldCode::NewObjB]->strToUint32();
            auto new_obj_f = text_fields_[TextFieldCode::NewObjF]->strToDouble();

            if ( new_obj_x.has_value() && new_obj_y.has_value() && new_obj_z.has_value() &&
                 new_obj_s.has_value() && new_obj_r.has_value() && new_obj_g.has_value() &&
                 new_obj_b.has_value() && new_obj_f.has_value() )
            {
                auto origin =
                    gfx::core::Vector3f( new_obj_x.value(), new_obj_y.value(), new_obj_z.value() );

                auto color =
                    gfx::core::Color( new_obj_r.value(), new_obj_g.value(), new_obj_b.value() );

                auto reflection_factor = new_obj_f.value();

                model::Material material( color, reflection_factor );

                switch ( scrollbar_.getCurActiveButton() )
                {
                    case ScrollBarButtonCode::Sphere:
                        scene_manager_.addSphere( material, origin, new_obj_s.value() );
                        break;
                    case ScrollBarButtonCode::AABB:
                        scene_manager_.addAABB( material,
                                                origin,
                                                gfx::core::Vector3f( new_obj_s.value(),
                                                                     new_obj_s.value(),
                                                                     new_obj_s.value() ) );
                        break;
                    case ScrollBarButtonCode::Plane:
                        scene_manager_.addPlane( material, origin, { 0.0f, 1.0f, 0.0f } );
                        break;
                    default:
                        break;
                }

                std::cerr << material.reflection_factor << std::endl;

                scene_manager_.needUpdate() = true;
            }
        }
        if ( isPressedJustNow( CopyObj ) )
        {
            auto new_obj_x = text_fields_[TextFieldCode::NewObjX]->strToDouble();
            auto new_obj_y = text_fields_[TextFieldCode::NewObjY]->strToDouble();
            auto new_obj_z = text_fields_[TextFieldCode::NewObjZ]->strToDouble();

            if ( new_obj_x.has_value() && new_obj_y.has_value() && new_obj_z.has_value() )
            {
                scene_manager_.copyTargetObj( new_obj_x.value(),
                                              new_obj_y.value(),
                                              new_obj_z.value() );
            }

            scene_manager_.needUpdate() = true;
        }
        if ( isPressedJustNow( DeleteObj ) )
        {
            scene_manager_.deleteTargetObj();
            scene_manager_.needUpdate() = true;
        }

        propagateEventToChildren( event );

        return false;
    }

  private:
    gfx::core::Font font_;

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
        NewObjX,
        NewObjY,
        NewObjZ,
        NewObjS,
        NewObjR,
        NewObjG,
        NewObjB,
        NewObjF,
        TextFieldCount,
    };

    std::unique_ptr<gfx::ui::TextField> text_fields_[TextFieldCount];

    enum ScrollBarButtonCode {
        Sphere,
        Plane,
        AABB,
        ScrollBarButtonCodeCount,
    };

    ScrollableButtonsWidget scrollbar_;

    bool
    isPressedJustNow( ButtonCode code )
    {
        return dynamic_cast<gfx::ui::Button*>( buttons_[code].get() )->isPressedJustNow();
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
                                               font_,
                                               title,
                                               Config::ControlPanel::Button::FontColor,
                                               Config::ControlPanel::Button::FontSize ) );
        buttons_[code]->parent_ = this;
    }

    void
    setupTextField( TextFieldCode code, const gfx::core::Vector2f& pos, const std::string& title )
    {
        text_fields_[code] = std::move(
            std::make_unique<gfx::ui::TextField>( title,
                                                  font_,
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
                                               font_,
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
