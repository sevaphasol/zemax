#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/transformable.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"
#include "gfx/ui/button.hpp"
#include "gfx/ui/container_widget.hpp"
#include "gfx/ui/scrollbar.hpp"
#include "zemax/model/rendering/scene_manager.hpp"
#include <memory>

namespace zemax {
namespace view {

class ScrollableButtonsWidget : public gfx::ui::ContainerWidget {
  public:
    explicit ScrollableButtonsWidget( const gfx::core::Vector2f& pos  = { 0.0f, 0.0f },
                                      const gfx::core::Vector2f& size = { 0.0f, 0.0f } )
        : ContainerWidget( pos, size ), scroll_bar_( 0, 0 )
    {
        setDraggable( true );

        // setPosition( Config::ControlPanel::Size );
        // setSize( Config::ControlPanel::Size );

        border_.setSize( size );
        border_.setFillColor( gfx::core::Color::Transparent );
        border_.setOutlineColor( gfx::core::Color::Red );
        border_.setOutlineThickness( 2.f );

        scroll_bar_.parent_ = this;
    };

    explicit ScrollableButtonsWidget( float x, float y, float w, float h )
        : ScrollableButtonsWidget( gfx::core::Vector2f( x, y ), gfx::core::Vector2f( w, h ) )
    {
    }

    virtual ~ScrollableButtonsWidget() = default;

    bool
    propagateEventToChildren( const gfx::ui::Event& event ) override
    {
        if ( event.apply( &scroll_bar_ ) )
        {
            return true;
        }

        if ( !buttons_.empty() )
        {
            if ( event.apply( buttons_[cur_active_button_].p_btn.get() ) )
            {
                return true;
            }
        }

        return false;
    }

    bool
    onIdle( const gfx::ui::Event& event ) override
    {
        if ( scroll_bar_.isScrolled() )
        {
            float scroll_factor = scroll_bar_.getScrollFactor();

            int tmp_idx = ( buttons_.size() - 1 ) * scroll_factor;

            if ( tmp_idx != cur_active_button_ )
            {
                prev_active_button_ = cur_active_button_;
            }

            cur_active_button_ = tmp_idx;
        }

        is_scroled_ = true;

        return propagateEventToChildren( event );
    }

    bool
    isActiveButtonPressed()
    {
        if ( !buttons_.empty() )
        {
            return buttons_[cur_active_button_].p_btn->isPressed();
        }

        return false;
    }

    bool
    isScrolled() const
    {
        return is_scroled_;
    }

    size_t
    getCurActiveButton() const
    {
        return cur_active_button_;
    }

    size_t
    getPrevActiveButton() const
    {
        return prev_active_button_;
    }

    // std::vector<std::unique_ptr<Button>>&
    // getButtons()
    // {
    // return buttons_;
    // }

    void
    addButton( model::SceneManager::ObjectInfo obj_info, std::unique_ptr<gfx::ui::Button> button )
    {
        button->parent_ = this;
        buttons_.push_back( { obj_info, std::move( button ) } );
    }

    struct ButtonCtx
    {
        model::SceneManager::ObjectInfo  obj_info;
        std::unique_ptr<gfx::ui::Button> p_btn;
    };

    ButtonCtx&
    getButtonCtx( size_t idx )
    {
        return buttons_[idx];
    }

  private:
    virtual void
    draw( gfx::core::Window& window, gfx::core::Transform transform ) const override final
    {
        gfx::core::Transform widget_transform = transform.combine( getTransform() );

        window.draw( scroll_bar_, widget_transform );
        if ( !buttons_.empty() )
        {
            window.draw( *buttons_[cur_active_button_].p_btn, widget_transform );
        }

        // std::cerr << border_.getSize().x << " " << border_.getSize().y << std::endl;
        // std::cerr << border_.getPosition().x << " " << border_.getPosition().y << std::endl;

        window.draw( border_, widget_transform );
    }

  private:
    gfx::ui::ScrollBar scroll_bar_;

    gfx::core::RectangleShape border_;

    int cur_active_button_  = 0;
    int prev_active_button_ = -1;

    bool is_scroled_ = false;

    std::vector<ButtonCtx> buttons_;
};

} // namespace view
} // namespace zemax
