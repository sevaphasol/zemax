// #include "gfx/core/color.hpp"
// #include "gfx/core/event.hpp"
// #include "gfx/core/mouse.hpp"
// #include "gfx/core/vector2.hpp"
// #include "gfx/core/window.hpp"
// #include "gfx/ui/widget.hpp"
// #include <cstdio>
// #include "gfx/ui/button.hpp"
// #include <iostream>
//
// namespace gfx {
// namespace ui {
//
// Button::Button( const gfx::core::Vector2f& pos,
//                 const gfx::core::Vector2f& size,
//                 const gfx::core::Color&    default_color,
//                 const gfx::core::Color&    hovered_color,
//                 const gfx::core::Color&    pressed_color,
//                 const gfx::core::Font&     font,
//                 const std::string&         title,
//                 const gfx::core::Color&    font_color,
//                 size_t                     font_size )
//     : Widget( pos, size ),
//       background_( size ),
//       default_color_( default_color ),
//       hovered_color_( hovered_color ),
//       pressed_color_( pressed_color )
// {
//     background_.setFillColor( default_color );
//     label_.setFont( font );
//     label_.setString( title );
//     label_.setCharacterSize( font_size );
//     label_.setFillColor( font_color );
//     label_.moveInCenterOfRect( size );
// }
//
// void
// Button::setRelPos( const gfx::core::Vector2f& pos )
// {
//     setPosition( pos );
//     label_.moveInCenterOfRect( size_ );
// }
//
// void
// Button::setSize( const gfx::core::Vector2f& size )
// {
//     size_ = size;
//     background_.setSize( size );
//     label_.moveInCenterOfRect( size );
// }
//
// void
// Button::setLabelText( const std::string& text )
// {
//     label_.setString( text );
// }
//
// void
// Button::setLabelFont( const gfx::core::Font& font, size_t size )
// {
//     label_.setFont( font );
//     label_.setCharacterSize( size );
// }
//
// void
// Button::setBackgroundColor( const gfx::core::Color& color )
// {
//     background_.setFillColor( color );
// }
//
// bool
// Button::isPressed() const
// {
//     return is_pressed_;
// }
//
// bool
// Button::isPressedJustNow() const
// {
//     return is_pressed_just_now_;
// }
//
// bool
// Button::onIdle( const Event& event )
// {
//     is_pressed_just_now_ = false;
//
//     updateVisuals();
//     return false;
// }
//
// bool
// Button::onMousePress( const Event& event )
// {
//     if ( Widget::onMousePress( event ) )
//     {
//         is_pressed_just_now_ = true;
//         return true;
//     }
//
//     return false;
// }
//
// void
// Button::updateVisuals()
// {
//     if ( is_pressed_ )
//     {
//         background_.setFillColor( pressed_color_ );
//     } else if ( is_hovered_ )
//     {
//         background_.setFillColor( hovered_color_ );
//     } else
//     {
//         background_.setFillColor( default_color_ );
//     }
// }
//
// void
// Button::draw( gfx::core::Window& window, gfx::core::Transform transform ) const
// {
//     core::Transform widget_transform = transform.combine( getTransform() );
//
//     window.draw( background_, widget_transform );
//     window.draw( label_, widget_transform );
// }
//
// } // namespace ui
// } // namespace gfx
