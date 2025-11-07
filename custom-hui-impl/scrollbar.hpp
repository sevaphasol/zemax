#pragma once

#include "container_widget.hpp"
#include "widget.hpp"

namespace hui {

class ScrollBar;

class Thumb : public hui::Widget {
  public:
    Thumb( cum::PluginManager* pm,
           ScrollBar*          owner,
           const dr4::Vec2f&   pos,
           const dr4::Vec2f&   size );

    bool
    onIdle( const Event& event ) override;
    bool
    onMousePress( const Event& event ) override;
    bool
    onMouseMove( const Event& event ) override;
    bool
    onMouseRelease( const Event& event ) override;

    void
    RedrawMyTexture() const override;

  private:
    void
    updateVisuals();

  private:
    ScrollBar* owner_;

    dr4::Rectangle rect_;
};

class Arrow : public hui::Widget {
  public:
    Arrow( cum::PluginManager* pm,
           ScrollBar*          owner,
           const dr4::Vec2f&   pos,
           const dr4::Vec2f&   size,
           bool                is_up );

    bool
    onIdle( const Event& event ) override;
    bool
    onMousePress( const Event& event ) override;
    bool
    onMouseMove( const Event& event ) override;
    bool
    onMouseRelease( const Event& event ) override;

    void
    setUpTriangle();

    void
    RedrawMyTexture() const override;

  private:
    void
    updateTriangleColor( const dr4::Color& color );
    void
    updateTrianglePosition();
    void
    updateVisuals();

  private:
    ScrollBar* owner_;

    bool is_up_;

    dr4::Rectangle rect_;
    // dr4::Vertex    triangle_[3];
};

class ScrollBar : public hui::ContainerWidget {
  public:
    ScrollBar( cum::PluginManager* pm, const dr4::Vec2f& pos );
    ScrollBar( cum::PluginManager* pm, float x, float y );

    void
    bringToFront( Widget* child ) override;

    bool
    propagateEventToChildren( const Event& event ) override final;

    dr4::Vec2f
    clampThumbPosition( const dr4::Vec2f& vector );

    void
    onThumbMove( float vertical_delta );
    void
    onArrowClick( bool is_up );

    void
    RedrawMyTexture() const override;

    double
    getScrollFactor() const;

    bool
    isScrolled();

  private:
    void
    updateThumbPosition();

  private:
    bool   is_scrolled_   = false;
    double scroll_factor_ = 0.0;

    dr4::Rectangle border_;

    Thumb thumb_;
    Arrow up_arrow_;
    Arrow down_arrow_;
};

} // namespace hui
