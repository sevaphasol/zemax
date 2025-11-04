#pragma once

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "dr4/window.hpp"
#include "event.hpp"

// #include "gfx/core/drawable.hpp"
// #include "gfx/core/transformable.hpp"
// #include "gfx/core/vector2.hpp"

#include <memory>
#include <vector>

namespace hui {

class Widget {
  public:
    explicit Widget( float x, float y, float w, float h );
    explicit Widget( const dr4::Vec2f& pos  = { 0.0f, 0.0f },
                     const dr4::Vec2f& size = { 0.0f, 0.0f } );
    virtual ~Widget() = default;

    // clang-format off
    virtual bool onIdle   		( const hui::Event& event );
    virtual bool onTextEnter    ( const hui::Event& event );
    virtual bool onKeyPress     ( const hui::Event& event );
    virtual bool onKeyRelease   ( const hui::Event& event );
    virtual bool onMousePress   ( const hui::Event& event );
    virtual bool onMouseRelease ( const hui::Event& event );
    virtual bool onMouseMove    ( const hui::Event& event );
    // clang-format on

    bool
    isHovered() const;

    bool
    isDraggable() const;
    void
    setDraggable( bool state );

    Widget*
    getParent();
    void
    setParent( Widget* new_parent );

    dr4::Vec2f
    getSize() const;
    virtual void
    setSize( const dr4::Vec2f& size );
    dr4::Vec2f
    getRelPos() const;
    virtual void
    setRelPos( const dr4::Vec2f& pos );
    virtual void
    setRelPos( float x, float y );
    dr4::Vec2f
    getAbsPos() const;
    dr4::Vec2f
    getParentAbsPos() const;
    bool
    pointInside( const dr4::Vec2f& point ) const;

    void
    draw( dr4::Window& window ) const;

  protected:
    dr4::Window* window_;

    dr4::Texture* texture_;

    Widget* parent_ = nullptr;

    dr4::Vec2f size_;
    dr4::Vec2f pos_;

    bool is_pressed_ = false;
    bool is_hovered_ = false;

    bool       is_draggable_ = false;
    bool       is_dragging_  = false;
    dr4::Vec2f drag_offset_  = { 0.0f, 0.0f };
};

} // namespace hui
