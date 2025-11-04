// #include "gfx/core/color.hpp"
// #include "gfx/core/event.hpp"
// #include "gfx/core/primitive_type.hpp"
// #include "gfx/core/rectangle_shape.hpp"
// #include "gfx/core/vector2.hpp"
// #include "gfx/core/vertex.hpp"
// #include "gfx/core/window.hpp"
// #include "gfx/ui/event.hpp"
// #include "gfx/ui/widget.hpp"
// #include "gfx/ui/container_widget.hpp"
//
// #include "gfx/ui/scrollbar.hpp"
//
// #include <algorithm>
// #include <cassert>
// #include <memory>
//
// namespace gfx {
// namespace ui {
//
// namespace detail {
//
// struct ScrollBar
// {
//     static inline const gfx::core::Vector2f Size = { 15.0f, 110.0f };
//
//     struct ArrowField
//     {
//         static constexpr float SizeCoef = 0.1;
//
//         static inline const gfx::core::Vector2f Size = { ScrollBar::Size.x,
//                                                          ScrollBar::Size.y* SizeCoef };
//
//         struct Color
//         {
//             static const inline auto Default = gfx::core::Color( 96 + 32, 96 + 32, 96 + 32 );
//             static const inline auto Hover   = gfx::core::Color( 64 + 32, 64 + 32, 64 + 32 );
//             static const inline auto Pressed = gfx::core::Color( 32 + 32, 32 + 32, 32 + 32 );
//         };
//
//         struct Triangle
//         {
//             struct Color
//             {
//                 static const inline auto Default = gfx::core::Color( 96, 96, 96 );
//                 static const inline auto Hover   = gfx::core::Color( 64, 64, 64 );
//                 static const inline auto Pressed = gfx::core::Color( 32, 32, 32 );
//             };
//
//             struct Up
//             {
//                 static inline const gfx::core::Vector2f Pos = { 0.0f, 0.0f };
//
//                 static inline const gfx::core::Vector2f Triangle[] = {
//                     gfx::core::Vector2f( ScrollBar::ArrowField::Size.x / 2,
//                                          ScrollBar::ArrowField::Size.y / 3 ),
//                     gfx::core::Vector2f( ScrollBar::ArrowField::Size.x / 3,
//                                          2 * ScrollBar::ArrowField::Size.y / 3 ),
//                     gfx::core::Vector2f( 2 * ScrollBar::ArrowField::Size.x / 3,
//                                          2 * ScrollBar::ArrowField::Size.y / 3 ) };
//             };
//
//             struct Down
//             {
//                 static inline const gfx::core::Vector2f Pos = { 0.0f,
//                                                                 ScrollBar::Size.y *
//                                                                     ( 1 - SizeCoef ) };
//
//                 static inline const gfx::core::Vector2f Triangle[] = {
//                     gfx::core::Vector2f( ScrollBar::ArrowField::Size.x / 2,
//                                          2 * ScrollBar::ArrowField::Size.y / 3 ),
//                     gfx::core::Vector2f( ScrollBar::ArrowField::Size.x / 3,
//                                          ScrollBar::ArrowField::Size.y / 3 ),
//                     gfx::core::Vector2f( 2 * ScrollBar::ArrowField::Size.x / 3,
//                                          ScrollBar::ArrowField::Size.y / 3 ) };
//             };
//         };
//     };
//
//     struct Thumb
//     {
//         static constexpr float SizeCoef = 0.3;
//
//         struct Color
//         {
//             static const inline auto Default = gfx::core::Color( 96 + 32, 96 + 32, 96 + 32, 100 );
//             static const inline auto Hover   = gfx::core::Color( 64 + 32, 64 + 32, 64 + 32, 200 );
//             static const inline auto Pressed = gfx::core::Color( 32 + 32, 32 + 32, 32 + 32, 255 );
//         };
//
//         static inline const gfx::core::Vector2f Size = { ScrollBar::Size.x,
//                                                          ScrollBar::Size.y* SizeCoef };
//
//         static inline const gfx::core::Vector2f StartPos = { 0.0f,
//                                                              ScrollBar::Size.y * ( 1 - SizeCoef ) -
//                                                                  ArrowField::Size.y };
//     };
// };
//
// } // namespace detail
//
// Thumb::Thumb( ScrollBar* owner, const gfx::core::Vector2f& pos, const gfx::core::Vector2f& size )
//     : gfx::ui::Widget( pos, size ), owner_( owner )
// {
//     parent_ = owner;
//
//     setDraggable( true );
//
//     rect_.setSize( size );
//     rect_.setFillColor( detail::ScrollBar::Thumb::Color::Default );
// }
//
// bool
// Thumb::onIdle( const Event& event )
// {
//     updateVisuals();
//
//     return false;
// }
//
// bool
// Thumb::onMousePress( const Event& event )
// {
//     if ( is_hovered_ && event.info.mouse_button.button == gfx::core::Mouse::Left )
//     {
//         is_pressed_  = true;
//         is_dragging_ = true;
//         gfx::core::Vector2f mouse_pos( event.info.mouse_button.x, event.info.mouse_button.y );
//         drag_offset_ = mouse_pos - getAbsPos();
//
//         return true;
//     }
//
//     return false;
// }
//
// bool
// Thumb::onMouseMove( const Event& event )
// {
//     gfx::core::Vector2f mouse_pos( event.info.mouse_move.x, event.info.mouse_move.y );
//     is_hovered_ = pointInside( mouse_pos );
//
//     if ( !is_hovered_ )
//     {
//         is_pressed_ = false;
//     }
//
//     if ( is_dragging_ )
//     {
//         auto new_pos = owner_->clampThumbPosition( mouse_pos - getParentAbsPos() - drag_offset_ );
//         owner_->onThumbMove( new_pos.y - getRelPos().y );
//     }
//
//     return is_hovered_;
// }
//
// bool
// Thumb::onMouseRelease( const Event& event )
// {
//     return Widget::onMouseRelease( event );
// }
//
// void
// Thumb::updateVisuals()
// {
//     if ( is_pressed_ )
//     {
//         rect_.setFillColor( detail::ScrollBar::Thumb::Color::Pressed );
//     } else if ( is_hovered_ )
//     {
//         rect_.setFillColor( detail::ScrollBar::Thumb::Color::Hover );
//     } else
//     {
//         rect_.setFillColor( detail::ScrollBar::Thumb::Color::Default );
//     }
// }
//
// void
// Thumb::draw( gfx::core::Window& window, gfx::core::Transform transform ) const
// {
//     core::Transform widget_transform = transform.combine( getTransform() );
//     window.draw( rect_, widget_transform );
// }
//
// Arrow::Arrow( ScrollBar*                 owner,
//               const gfx::core::Vector2f& pos,
//               const gfx::core::Vector2f& size,
//               bool                       is_up )
//     : gfx::ui::Widget( pos, size ), is_up_( is_up ), owner_( owner )
// {
//     parent_ = owner;
//
//     rect_.setSize( size );
//     rect_.setFillColor( detail::ScrollBar::ArrowField::Color::Default );
//
//     setUpTriangle();
// }
//
// bool
// Arrow::onIdle( const Event& event )
// {
//     updateVisuals();
//
//     return false;
// }
//
// void
// Arrow::setUpTriangle()
// {
//     updateTriangleColor( detail::ScrollBar::ArrowField::Triangle::Color::Default );
//     updateTrianglePosition();
// }
//
// bool
// Arrow::onMousePress( const Event& event )
// {
//     if ( is_hovered_ && event.info.mouse_button.button == gfx::core::Mouse::Left )
//     {
//         is_pressed_ = true;
//
//         owner_->onArrowClick( is_up_ );
//         return true;
//     }
//
//     return false;
// }
//
// bool
// Arrow::onMouseMove( const Event& event )
// {
//     core::Vector2f mouse_pos( event.info.mouse_move.x, event.info.mouse_move.y );
//     is_hovered_ = pointInside( mouse_pos );
//
//     if ( !is_hovered_ )
//     {
//         is_pressed_ = false;
//     }
//
//     if ( is_dragging_ )
//     {
//         setRelPos( mouse_pos - drag_offset_ - getParentAbsPos() );
//         return true;
//     }
//
//     return is_hovered_;
//
//     return Widget::onMouseMove( event );
// }
//
// bool
// Arrow::onMouseRelease( const Event& event )
// {
//     return Widget::onMouseRelease( event );
// }
//
// void
// Arrow::updateTriangleColor( const gfx::core::Color& color )
// {
//     for ( auto& vertex : triangle_ )
//     {
//         vertex.color = color;
//     }
// }
//
// void
// Arrow::updateTrianglePosition()
// {
//     if ( is_up_ )
//     {
//         triangle_[0].position = gfx::core::Vector2f( size_.x / 2, size_.y / 3 );
//         triangle_[1].position = gfx::core::Vector2f( size_.x / 3, 2 * size_.y / 3 );
//         triangle_[2].position = gfx::core::Vector2f( 2 * size_.x / 3, 2 * size_.y / 3 );
//     } else
//     {
//         triangle_[0].position = gfx::core::Vector2f( size_.x / 2, 2 * size_.y / 3 );
//         triangle_[1].position = gfx::core::Vector2f( size_.x / 3, size_.y / 3 );
//         triangle_[2].position = gfx::core::Vector2f( 2 * size_.x / 3, size_.y / 3 );
//     }
// }
//
// void
// Arrow::updateVisuals()
// {
//     if ( is_pressed_ )
//     {
//         rect_.setFillColor( detail::ScrollBar::ArrowField::Color::Pressed );
//         updateTriangleColor( detail::ScrollBar::ArrowField::Triangle::Color::Pressed );
//     } else if ( is_hovered_ )
//     {
//         rect_.setFillColor( detail::ScrollBar::ArrowField::Color::Hover );
//         updateTriangleColor( detail::ScrollBar::ArrowField::Triangle::Color::Hover );
//     } else
//     {
//         rect_.setFillColor( detail::ScrollBar::ArrowField::Color::Default );
//         updateTriangleColor( detail::ScrollBar::ArrowField::Triangle::Color::Default );
//     }
// }
//
// void
// Arrow::draw( gfx::core::Window& window, gfx::core::Transform transform ) const
// {
//     core::Transform widget_transform = transform.combine( getTransform() );
//
//     window.draw( rect_, widget_transform );
//     window.draw( triangle_, 3, gfx::core::PrimitiveType::Triangles, widget_transform );
// }
//
// ScrollBar::ScrollBar( float x, float y ) : ScrollBar( gfx::core::Vector2f( x, y ) ) {}
//
// ScrollBar::ScrollBar( const gfx::core::Vector2f& pos )
//     : gfx::ui::ContainerWidget( pos, detail::ScrollBar::Size ),
//       thumb_( this,
//               detail::ScrollBar::Thumb::StartPos,
//               core::Vector2f( detail::ScrollBar::Size.x,
//                               detail::ScrollBar::Size.y * detail::ScrollBar::Thumb::SizeCoef ) ),
//       up_arrow_(
//           this,
//           gfx::core::Vector2f( 0.0f, 0.0f ),
//           core::Vector2f( detail::ScrollBar::Size.x,
//                           detail::ScrollBar::Size.y * detail::ScrollBar::ArrowField::SizeCoef ),
//           true ),
//       down_arrow_(
//           this,
//           gfx::core::Vector2f( 0.0f,
//                                detail::ScrollBar::Size.y *
//                                    ( 1 - detail::ScrollBar::ArrowField::SizeCoef ) ),
//           core::Vector2f( detail::ScrollBar::Size.x,
//                           detail::ScrollBar::Size.y * detail::ScrollBar::ArrowField::SizeCoef ),
//           false )
// {
//     border_.setSize( getSize() );
//     border_.setFillColor( gfx::core::Color( 64, 64, 64, 128 ) );
//     border_.setOutlineColor( gfx::core::Color( 32, 32, 32 ) );
//     border_.setOutlineThickness( 4.0f );
// }
//
// void
// ScrollBar::bringToFront( Widget* child )
// {
// }
//
// bool
// ScrollBar::propagateEventToChildren( const Event& event )
// {
//     if ( event.apply( &thumb_ ) )
//     {
//         return true;
//     }
//
//     if ( event.apply( &up_arrow_ ) )
//     {
//         return true;
//     }
//
//     if ( event.apply( &down_arrow_ ) )
//     {
//         return true;
//     }
//
//     return false;
// }
//
// double
// ScrollBar::getScrollFactor() const
// {
//     return scroll_factor_;
// }
//
// bool
// ScrollBar::isScrolled()
// {
//     if ( is_scrolled_ )
//     {
//         is_scrolled_ = false;
//         return true;
//     }
//
//     return false;
// }
//
// gfx::core::Vector2f
// ScrollBar::clampThumbPosition( const gfx::core::Vector2f& vector )
// {
//     return { std::clamp( vector.x, 0.0f, size_.x - thumb_.getSize().x ),
//              std::clamp( vector.y,
//                          up_arrow_.getSize().y,
//                          size_.y - thumb_.getSize().y - up_arrow_.getSize().y ) };
// }
//
// void
// ScrollBar::onThumbMove( float vertical_delta )
// {
//     float norm_delta =
//         vertical_delta / ( size_.y - thumb_.getSize().y - 2 * up_arrow_.getSize().y );
//
//     scroll_factor_ = std::clamp( scroll_factor_ - norm_delta, 0.0, 1.0 );
//
//     is_scrolled_ = true;
//
//     updateThumbPosition();
// }
//
// void
// ScrollBar::onArrowClick( bool is_up )
// {
//     scroll_factor_ = std::clamp( scroll_factor_ + ( is_up ? 0.1 : -0.1 ), 0.0, 1.0 );
//
//     is_scrolled_ = true;
//
//     updateThumbPosition();
// }
//
// void
// ScrollBar::updateThumbPosition()
// {
//     float thumb_y =
//         up_arrow_.getSize().y +
//         ( 1 - scroll_factor_ ) * ( size_.y - thumb_.getSize().y - 2 * up_arrow_.getSize().y );
//
//     thumb_.setRelPos( gfx::core::Vector2f( 0.0, thumb_y ) );
// }
//
// void
// ScrollBar::draw( gfx::core::Window& window, gfx::core::Transform transform ) const
// {
//     core::Transform widget_transform = transform.combine( getTransform() );
//
//     window.draw( border_, widget_transform );
//     window.draw( thumb_, widget_transform );
//     window.draw( up_arrow_, widget_transform );
//     window.draw( down_arrow_, widget_transform );
// }
//
// } // namespace ui
// } // namespace gfx
