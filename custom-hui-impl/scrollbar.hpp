// #pragma once
//
// #include "gfx/core/rectangle_shape.hpp"
// #include "gfx/core/vector2.hpp"
// #include "gfx/core/window.hpp"
// #include "gfx/ui/widget.hpp"
// #include "gfx/ui/container_widget.hpp"
//
// namespace gfx {
// namespace ui {
//
// class ScrollBar;
//
// class Thumb : public gfx::ui::Widget {
//   public:
//     Thumb( ScrollBar* owner, const gfx::core::Vector2f& pos, const gfx::core::Vector2f& size );
//
//     bool
//     onIdle( const Event& event ) override;
//     bool
//     onMousePress( const Event& event ) override;
//     bool
//     onMouseMove( const Event& event ) override;
//     bool
//     onMouseRelease( const Event& event ) override;
//
//     void
//     draw( gfx::core::Window& window, gfx::core::Transform transform ) const override;
//
//   private:
//     void
//     updateVisuals();
//
//   private:
//     ScrollBar* owner_;
//
//     gfx::core::RectangleShape rect_;
// };
//
// class Arrow : public gfx::ui::Widget {
//   public:
//     Arrow( ScrollBar*                 owner,
//            const gfx::core::Vector2f& pos,
//            const gfx::core::Vector2f& size,
//            bool                       is_up );
//
//     bool
//     onIdle( const Event& event ) override;
//     bool
//     onMousePress( const Event& event ) override;
//     bool
//     onMouseMove( const Event& event ) override;
//     bool
//     onMouseRelease( const Event& event ) override;
//
//     void
//     setUpTriangle();
//
//     void
//     draw( gfx::core::Window& window, gfx::core::Transform transform ) const override;
//
//   private:
//     void
//     updateTriangleColor( const gfx::core::Color& color );
//     void
//     updateTrianglePosition();
//     void
//     updateVisuals();
//
//   private:
//     ScrollBar* owner_;
//
//     bool is_up_;
//
//     gfx::core::RectangleShape rect_;
//     gfx::core::Vertex         triangle_[3];
// };
//
// class ScrollBar : public gfx::ui::ContainerWidget {
//   public:
//     ScrollBar( const gfx::core::Vector2f& pos );
//     ScrollBar( float x, float y );
//
//     void
//     bringToFront( Widget* child ) override;
//
//     bool
//     propagateEventToChildren( const Event& event ) override final;
//
//     gfx::core::Vector2f
//     clampThumbPosition( const gfx::core::Vector2f& vector );
//
//     void
//     onThumbMove( float vertical_delta );
//     void
//     onArrowClick( bool is_up );
//
//     void
//     draw( gfx::core::Window& window, gfx::core::Transform transform ) const override;
//
//     double
//     getScrollFactor() const;
//
//     bool
//     isScrolled();
//
//   private:
//     void
//     updateThumbPosition();
//
//   private:
//     bool   is_scrolled_   = false;
//     double scroll_factor_ = 0.0;
//
//     gfx::core::RectangleShape border_;
//
//     Thumb thumb_;
//     Arrow up_arrow_;
//     Arrow down_arrow_;
// };
//
// } // namespace ui
// } // namespace gfx
