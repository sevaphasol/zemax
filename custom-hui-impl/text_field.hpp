// #pragma once
//
// #include "gfx/core/color.hpp"
// #include "gfx/core/rectangle_shape.hpp"
// #include "gfx/core/text.hpp"
// #include "gfx/core/vector2.hpp"
// #include "gfx/core/window.hpp"
// #include "gfx/ui/container_widget.hpp"
// #include "gfx/ui/event.hpp"
// #include "gfx/ui/widget.hpp"
//
// #include <atomic>
// #include <cmath>
// #include <iostream>
// #include <limits>
// #include <optional>
// #include <stdexcept>
//
// namespace gfx {
// namespace ui {
//
// class Cursor : public Widget {
//   public:
//     Cursor( float w, float h ) : Widget( 0.0f, 0.0f, w, h ), color_( core::Color::White )
//     {
//         rect_.setFillColor( color_ );
//         rect_.setSize( w, h );
//     }
//
//     void
//     move( float x )
//     {
//         setPosition( getPosition().x + x, getPosition().y );
//     }
//
//     bool
//     onIdle( const Event& event ) override
//     {
//         // TODO blinking logic
//         return false;
//     }
//
//     void
//     setColor( const core::Color& color )
//     {
//         rect_.setFillColor( color );
//     }
//
//     void
//     draw( core::Window& window, core::Transform transform ) const override final
//     {
//         transform = transform.combine( getTransform() );
//
//         window.draw( rect_, transform );
//     }
//
//   private:
//     core::Color          color_;
//     core::RectangleShape rect_;
// };
//
// class TextField : public ContainerWidget {
//   public:
//     TextField( const std::string& label,
//                const core::Font&  font,
//                float              x,
//                float              y,
//                float              w,
//                float              h )
//         : ContainerWidget( x, y, w, h ), cursor_( 1.0f, h * 0.8 )
//     {
//         label_.setCharacterSize( 12 );
//         label_.setFillColor( core::Color::White );
//         label_.setFont( font );
//         label_.setString( label );
//
//         text_.setCharacterSize( 12 );
//         text_.setFillColor( core::Color::White );
//         text_.setFont( font );
//         text_.setPosition( 1.8 * label_.getLocalBounds().w, h * 0.1f );
//
//         border_.setFillColor( core::Color::Transparent );
//         border_.setOutlineColor( { 118, 185, 0 } );
//         border_.setOutlineThickness( 1.0f );
//         border_.setSize( w - 1.05 * label_.getLocalBounds().w, h );
//         border_.setPosition( 1.75 * label_.getLocalBounds().w, 0 );
//
//         cursor_.setPosition( 1.9 * label_.getLocalBounds().w, h * 0.1f );
//     }
//
//     TextField( const std::string&    label,
//                const core::Font&     font,
//                const core::Vector2f& pos,
//                const core::Vector2f& size )
//         : TextField( label, font, pos.x, pos.y, size.x, size.y )
//     {
//     }
//
//     bool
//     propagateEventToChildren( const Event& event ) override
//     {
//         return event.apply( &cursor_ );
//     }
//
//     bool
//     onMousePress( const Event& event ) override
//     {
//         is_focused_ = Widget::onMousePress( event );
//
//         return is_focused_;
//     }
//
//     bool
//     onIdle( const Event& event ) override
//     {
//         ++govnokod_;
//
//         if ( govnokod_ % 15 != 0 )
//         {
//             return false;
//         }
//
//         if ( govnokod_ % 10 < 5 )
//         {
//             cursor_.setColor( core::Color::Transparent );
//         } else
//         {
//             cursor_.setColor( core::Color::White );
//         }
//
//         return false;
//     }
//
//     bool
//     onMouseMove( const Event& event ) override
//     {
//         // Widget::onMouseMove( event );
//
//         core::Vector2f mouse_pos( event.info.mouse_move.x, event.info.mouse_move.y );
//         // is_hovered_ = pointInside( mouse_pos );
//
//         core::Vector2f rel_pos        = getRelPos();
//         core::Vector2f parent_abs_pos = getParentAbsPos();
//
//         core::Vector2f abs_pos = parent_abs_pos + rel_pos;
//         core::Vector2f sz      = getSize();
//
//         is_hovered_ = ( ( mouse_pos.x >= abs_pos.x && mouse_pos.x <= abs_pos.x + sz.x ) &&
//                         ( mouse_pos.y >= abs_pos.y && mouse_pos.y <= abs_pos.y + sz.y ) );
//
//         if ( !is_hovered_ )
//         {
//             is_pressed_ = false;
//         }
//
//         if ( is_dragging_ )
//         {
//             setRelPos( mouse_pos - drag_offset_ - getParentAbsPos() );
//             return true;
//         }
//
//         return is_hovered_;
//     }
//
//     bool
//     onTextEnter( const Event& event ) override
//     {
//         if ( !is_focused_ )
//         {
//             return false;
//         }
//
//         auto ch    = event.info.text.unicode;
//         auto old_w = text_.getLocalBounds().w;
//
//         if ( ch == '\b' )
//         {
//             if ( str_.size() > 0 )
//             {
//                 str_.pop_back();
//             }
//         } else
//         {
//             if ( old_w >= 0.8 * border_.getSize().x )
//             {
//                 return true;
//             }
//
//             str_ += ch;
//         }
//
//         text_.setString( str_ );
//
//         auto  new_w = text_.getLocalBounds().w;
//         float ch_w  = new_w - old_w;
//
//         cursor_.move( ch_w );
//
//         return true;
//     }
//
//     std::optional<double>
//     strToDouble()
//     {
//         try
//         {
//             return std::stod( str_ );
//         } catch ( const std::invalid_argument& e )
//         {
//             return std::nullopt;
//         } catch ( const std::out_of_range& e )
//         {
//             return std::nullopt;
//         }
//     }
//
//     std::optional<uint32_t>
//     strToUint32()
//     {
//         try
//         {
//             return std::stoul( str_ );
//         } catch ( const std::invalid_argument& e )
//         {
//             return std::nullopt;
//         } catch ( const std::out_of_range& e )
//         {
//             return std::nullopt;
//         }
//     }
//
//   private:
//     void
//     draw( core::Window& window, core::Transform transform ) const override final
//     {
//         transform = transform.combine( getTransform() );
//
//         window.draw( label_, transform );
//         window.draw( text_, transform );
//         window.draw( border_, transform );
//
//         if ( is_focused_ )
//         {
//             window.draw( cursor_, transform );
//         }
//     }
//
//   private:
//     bool is_focused_;
//
//     int govnokod_ = 0;
//
//     core::Text label_;
//
//     Cursor               cursor_;
//     core::RectangleShape border_;
//
//     std::string str_;
//     core::Text  text_;
// };
//
// } // namespace ui
// } // namespace gfx
