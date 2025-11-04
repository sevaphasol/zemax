// #pragma once
//
// #include "gfx/core/color.hpp"
// #include "gfx/core/font.hpp"
// #include "gfx/core/rectangle_shape.hpp"
// #include "gfx/core/text.hpp"
// #include "gfx/ui/widget.hpp"
//
// namespace gfx {
// namespace ui {
//
// class Button : public gfx::ui::Widget {
//   public:
//     explicit Button( const gfx::core::Vector2f& pos,
//                      const gfx::core::Vector2f& size,
//                      const gfx::core::Color&    default_color,
//                      const gfx::core::Color&    hovered_color,
//                      const gfx::core::Color&    pressed_color,
//                      const gfx::core::Font&     font,
//                      const std::string&         title,
//                      const gfx::core::Color&    font_color,
//                      size_t                     font_size );
//
//     void
//     setRelPos( const gfx::core::Vector2f& pos ) override;
//     void
//     setSize( const gfx::core::Vector2f& size ) override;
//
//     void
//     setLabelText( const std::string& text );
//     void
//     setLabelFont( const gfx::core::Font& font, size_t size );
//     void
//     setBackgroundColor( const gfx::core::Color& color );
//     bool
//     isPressed() const;
//     bool
//     isPressedJustNow() const;
//     bool
//     onMousePress( const Event& event ) override;
//
//     bool
//     onIdle( const Event& event ) override;
//
//   private:
//     // bool
//     // onMousePress( const Event& event ) override;
//     // bool
//     // onMouseRelease( const Event& event ) override;
//     // bool
//     // onMouseMove( const Event& event ) override;
//     void
//     draw( gfx::core::Window& window, gfx::core::Transform transform ) const override;
//     void
//     updateVisuals();
//
//     bool is_pressed_just_now_ = false;
//
//     gfx::core::RectangleShape background_;
//     gfx::core::Font           font_;
//     gfx::core::Text           label_;
//     gfx::core::Color          default_color_;
//     gfx::core::Color          hovered_color_;
//     gfx::core::Color          pressed_color_;
// };
//
// } // namespace ui
// } // namespace gfx
