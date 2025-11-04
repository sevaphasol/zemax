#pragma once

#include "dr4/math/vec2.hpp"
#include "event.hpp"
#include "widget.hpp"
#include <memory>

namespace hui {

class ContainerWidget : public Widget {
  public:
    explicit ContainerWidget( float x, float y, float w, float h ) : Widget( x, y, w, h ) {}
    explicit ContainerWidget( const dr4::Vec2f& pos  = { 0.0f, 0.0f },
                              const dr4::Vec2f& size = { 0.0f, 0.0f } )
        : Widget( pos, size ) {};
    virtual ~ContainerWidget() = default;

    virtual void
    bringToFront( Widget* child )
    {
    }

    virtual bool
    propagateEventToChildren( const Event& event ) = 0;

    virtual bool
    onIdle( const Event& event ) override
    {
        if ( propagateEventToChildren( event ) )
        {
            return true;
        }

        return Widget::onIdle( event );
    }

    virtual bool
    onTextEnter( const Event& event ) override
    {
        if ( propagateEventToChildren( event ) )
        {
            return true;
        }

        return Widget::onKeyPress( event );
    }

    virtual bool
    onKeyPress( const Event& event ) override
    {
        if ( propagateEventToChildren( event ) )
        {
            return true;
        }

        return Widget::onKeyPress( event );
    }

    virtual bool
    onKeyRelease( const Event& event ) override
    {
        if ( propagateEventToChildren( event ) )
        {
            return true;
        }

        return Widget::onKeyRelease( event );
    }

    virtual bool
    onMousePress( const Event& event ) override
    {
        if ( propagateEventToChildren( event ) )
        {
            return true;
        }

        return Widget::onMousePress( event );
    }

    virtual bool
    onMouseRelease( const Event& event ) override
    {
        if ( propagateEventToChildren( event ) )
        {
            return true;
        }

        return Widget::onMouseRelease( event );
    }

    virtual bool
    onMouseMove( const Event& event ) override
    {
        if ( propagateEventToChildren( event ) )
        {
            return true;
        }

        return Widget::onMouseMove( event );
    }
};

class VectorContainerWidget : public ContainerWidget {
  public:
    explicit VectorContainerWidget( float x, float y, float w, float h )
        : ContainerWidget( x, y, w, h )
    {
    }
    explicit VectorContainerWidget( const dr4::Vec2f& pos  = { 0.0f, 0.0f },
                                    const dr4::Vec2f& size = { 0.0f, 0.0f } )
        : ContainerWidget( pos, size ) {};
    virtual ~VectorContainerWidget() = default;

    virtual bool
    onIdle( const Event& event ) override
    {
        return propagateEventToChildren( event );
    }
    virtual bool
    onTextEnter( const Event& event ) override
    {
        return propagateEventToChildren( event );
    }
    virtual bool
    onKeyPress( const Event& event ) override
    {
        return propagateEventToChildren( event );
    }
    virtual bool
    onKeyRelease( const Event& event ) override
    {
        return propagateEventToChildren( event );
    }
    virtual bool
    onMousePress( const Event& event ) override
    {
        return propagateEventToChildren( event );
    }
    virtual bool
    onMouseRelease( const Event& event ) override
    {
        return propagateEventToChildren( event );
    }
    virtual bool
    onMouseMove( const Event& event ) override
    {
        return propagateEventToChildren( event );
    }

    void
    addChild( std::unique_ptr<Widget> child )
    {
        setParent( this );
        children_.emplace_back( std::move( child ) );
    }

    virtual bool
    propagateEventToChildren( const Event& event ) override
    {
        for ( auto& child : children_ )
        {
            if ( event.apply( child.get() ) )
            {
                return true;
            }
        }

        return false;
    }

    void
    bringToFront( Widget* child ) override
    {
        for ( auto it = children_.begin(); it != children_.end(); ++it )
        {
            if ( it->get() == child )
            {
                auto tmp = std::move( *it );
                children_.erase( it );
                children_.push_back( std::move( tmp ) );
                break;
            }
        }
    }

    void
    drawChildren( dr4::Window& window ) const
    {
        for ( const auto& child : children_ )
        {
            child->draw( window );
        }
    }

    void
    draw( dr4::Window& window ) const
    {
        drawChildren( window );
    }

  protected:
    std::vector<std::unique_ptr<Widget>> children_;
};

} // namespace hui
