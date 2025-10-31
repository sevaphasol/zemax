#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/font.hpp"
#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/text.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"
#include "gfx/ui/widget.hpp"
#include "zemax/config.hpp"
#include "zemax/model/primitives/primitive.hpp"

#include <iomanip>

namespace zemax {
namespace view {

class ObjInfoPanel : public gfx::ui::Widget {
  public:
    ObjInfoPanel( const gfx::core::Font& font, float w, float h )
        : gfx::ui::Widget( 0.0f, 0.0f, w, h ), rect_( { w, h } )
    {
        text_.setFillColor( Config::Scene::ObjInfoPanel::FontColor );
        text_.setCharacterSize( Config::Scene::ObjInfoPanel::FontSize );
        text_.setFont( font );

        rect_.setFillColor( Config::Scene::ObjInfoPanel::FillColor );
        rect_.setOutlineColor( Config::Scene::ObjInfoPanel::OutlineColor );
        rect_.setOutlineThickness( Config::Scene::ObjInfoPanel::OutlineThickness );
    }

    ObjInfoPanel( const gfx::core::Font& font, const gfx::core::Vector2f& size )
        : ObjInfoPanel( font, size.x, size.y )
    {
    }

    void
    update( model::Primitive* obj )
    {
        setType( obj );
        setCoords( obj );
        setColor( obj );
        setReflection( obj );

        text_.setString( type_ + '\n' + coords_ + '\n' + color_ + '\n' + reflection_ );
        // text_.setString( type_ );
    }

    void
    setFont( const gfx::core::Font& font )
    {
        text_.setFont( font );
    }

    bool
    isVisible() const
    {
        return is_visible_;
    }

    void
    setVisible( bool state )
    {
        is_visible_ = state;
    }

  private:
    void
    setType( model::Primitive* obj )
    {
        type_.clear();
        type_ += type_template_;
        type_ += obj->getName();
    }

    void
    setReflection( model::Primitive* obj )
    {
        reflection_.clear();

        std::ostringstream oss;
        oss << reflection_template_ << std::fixed << std::setprecision( 2 )
            << obj->getMaterial().reflection_factor;

        reflection_ = oss.str();
    }

    void
    setCoords( model::Primitive* obj )
    {
        coords_.clear();
        auto obj_origin = obj->getOrigin();

        std::ostringstream oss;
        oss << coords_template_ << "( " << std::fixed << std::setprecision( 1 ) << obj_origin.x
            << ", " << obj_origin.y << ", " << obj_origin.z << " )";

        coords_ = oss.str();
    }

    void
    setColor( model::Primitive* obj )
    {
        color_.clear();
        auto obj_color = obj->getMaterial().color;

        color_ += color_template_;
        color_ += "( ";
        color_ += std::to_string( obj_color.r );
        color_ += ", ";
        color_ += std::to_string( obj_color.g );
        color_ += ", ";
        color_ += std::to_string( obj_color.b );
        color_ += " )";
    }

    void
    draw( gfx::core::Window& window, gfx::core::Transform transform ) const override
    {
        transform = transform.combine( getTransform() );

        if ( isVisible() )
        {
            window.draw( rect_, transform );
            window.draw( text_, transform );
        }
    }

  private:
    const char* type_template_       = "Type:       ";
    const char* coords_template_     = "Coords:     ";
    const char* color_template_      = "Color:      ";
    const char* reflection_template_ = "Reflection: ";

    std::string type_;
    std::string coords_;
    std::string color_;
    std::string reflection_;

    gfx::core::RectangleShape rect_;
    gfx::core::Text           text_;

    bool is_visible_ = false;
};

} // namespace view
} // namespace zemax
