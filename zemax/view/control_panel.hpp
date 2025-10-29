// #pragma once
//
// #include "gfx/core/event.hpp"
// #include "gfx/core/font.hpp"
// #include "gfx/core/rectangle_shape.hpp"
// #include "gfx/core/vector2.hpp"
// #include "gfx/core/window.hpp"
// #include "gfx/ui/button.hpp"
// #include "gfx/ui/scrollable_buttons_widget.hpp"
// // #include "gfx/ui/scrollbar.hpp"
// #include "gfx/ui/widget/container.hpp"
// #include "zemax/config.hpp"
// #include "zemax/model/rendering/scene_manager_.hpp"
//
// #include <iostream>
//
// namespace zemax {
// namespace view {
//
// class ControlPanel : public gfx::ui::ContainerWidget {
//   public:
//     explicit ControlPanel( zemax::model::SceneManager& scenes_manager )
//         : ContainerWidget( Config::ControlPanel::Position, Config::ControlPanel::Size ),
//           scenes_manager_( scenes_manager ),
//           camera_( scenes_manager.getCamera() ),
//           // clang-format off
//           mv_l_( Config::ControlPanel::Button::MvL::Position,Config::ControlPanel::Button::Size
//           ), mv_r_(
//           Config::ControlPanel::Button::MvR::Position,Config::ControlPanel::Button::Size ),
//           mv_f_( Config::ControlPanel::Button::MvF::Position,Config::ControlPanel::Button::Size
//           ), mv_b_(
//           Config::ControlPanel::Button::MvB::Position,Config::ControlPanel::Button::Size ),
// 		  mv_u_(
// Config::ControlPanel::Button::MvU::Position,Config::ControlPanel::Button::Size ),
//           mv_d_( Config::ControlPanel::Button::MvD::Position,Config::ControlPanel::Button::Size
//           ), rt_l_(
//           Config::ControlPanel::Button::RtL::Position,Config::ControlPanel::Button::Size ),
//           rt_r_( Config::ControlPanel::Button::RtR::Position,Config::ControlPanel::Button::Size
//           ), rt_u_(
//           Config::ControlPanel::Button::RtU::Position,Config::ControlPanel::Button::Size ),
//           rt_d_( Config::ControlPanel::Button::RtD::Position,Config::ControlPanel::Button::Size )
//     // clang-format on
//     {
//         rect_.setSize( getSize() );
//         rect_.setFillColor( Config::ControlPanel::BackgroundColor );
//         rect_.setOutlineColor( Config::ControlPanel::BorderColor );
//         rect_.setOutlineThickness( Config::ControlPanel::BorderThickness );
//     }
//
//     bool
//     propagate( const gfx::ui::Event& event ) override
//     {
//         std::cerr << __PRETTY_FUNCTION__ << std::endl;
//
//         for ( auto* button : buttons_ )
//         {
//             std::cerr << "propagating " << typeid( event ).name() << std::endl;
//
//             event.apply( button );
//             // {
//             // return true;
//             // }
//         }
//
//         return false;
//     }
//
//     virtual bool
//     onIdle( const gfx::ui::Event& event ) override final
//     {
//         return false;
//     }
//
//   private:
//     virtual void
//     drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const override final
//     {
//         window.draw( rect_, transform );
//     }
//
//     void
//     drawChildren( gfx::core::Window& window, gfx::core::Transform transform ) const override
//     {
//         for ( const auto& button : buttons_ )
//         {
//             window.draw( *button, transform );
//         }
//     }
//
//   private:
//     zemax::model::SceneManager& scenes_manager_;
//     zemax::model::Camera&       camera_;
//
//     gfx::ui::Button mv_l_;
//     gfx::ui::Button mv_r_;
//     gfx::ui::Button mv_f_;
//     gfx::ui::Button mv_b_;
//     gfx::ui::Button mv_u_;
//     gfx::ui::Button mv_d_;
//     gfx::ui::Button rt_u_;
//     gfx::ui::Button rt_d_;
//     gfx::ui::Button rt_r_;
//     gfx::ui::Button rt_l_;
//
//     gfx::ui::Button* buttons_[10] =
//         { &mv_l_, &mv_r_, &mv_f_, &mv_b_, &mv_u_, &mv_d_, &rt_u_, &rt_d_, &rt_r_, &rt_l_ };
//
//     gfx::core::RectangleShape rect_;
// };
//
// } // namespace view
// } // namespace zemax

#pragma once

#include "gfx/core/font.hpp"
#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/window.hpp"
#include "gfx/ui/button.hpp"
#include "gfx/ui/widget/container.hpp"
#include "zemax/config.hpp"
#include "zemax/model/rendering/scene_manager.hpp"

namespace zemax {
namespace view {

class ControlPanel : public gfx::ui::ContainerWidget {
  public:
    explicit ControlPanel( model::SceneManager& scene_manager_ )
        : ContainerWidget( Config::ControlPanel::Position, Config::ControlPanel::Size ),
          scene_manager_( scene_manager_ ),
          camera_( scene_manager_.getCamera() ),

#define BUTTON_CONSTRUCTOR( _var_name_, _config_name_ )                                            \
    _var_name_( Config::ControlPanel::Button::_config_name_::Position,                             \
                Config::ControlPanel::Button::Size,                                                \
                labels_font_,                                                                      \
                Config::ControlPanel::Button::_config_name_::Title,                                \
                Config::ControlPanel::Button::FontSize )

          BUTTON_CONSTRUCTOR( mv_l_, MvL ),
          BUTTON_CONSTRUCTOR( mv_r_, MvR ),
          BUTTON_CONSTRUCTOR( mv_u_, MvU ),
          BUTTON_CONSTRUCTOR( mv_d_, MvD ),
          BUTTON_CONSTRUCTOR( mv_f_, MvF ),
          BUTTON_CONSTRUCTOR( mv_b_, MvB ),
          BUTTON_CONSTRUCTOR( rt_l_, RtL ),
          BUTTON_CONSTRUCTOR( rt_r_, RtR ),
          BUTTON_CONSTRUCTOR( rt_u_, RtU ),
          BUTTON_CONSTRUCTOR( rt_d_, RtD )

#undef BUTTON_CONSTRUCTOR

    {
        loadFont( Config::ControlPanel::Button::FontName );

        setPosition( Config::ControlPanel::Position );
        setSize( Config::ControlPanel::Size );

        border_.setSize( getSize() );
        border_.setFillColor( Config::ControlPanel::BackgroundColor );
        border_.setOutlineColor( Config::ControlPanel::BorderColor );
        border_.setOutlineThickness( Config::ControlPanel::BorderThickness );
    }

    bool
    propagate( const gfx::ui::Event& event ) override final
    {
        return event.apply( &mv_l_ ) || event.apply( &mv_r_ ) || event.apply( &mv_u_ ) ||
               event.apply( &mv_d_ ) || event.apply( &mv_f_ ) || event.apply( &mv_b_ ) ||
               event.apply( &rt_l_ ) || event.apply( &rt_r_ ) || event.apply( &rt_u_ ) ||
               event.apply( &rt_d_ );
    }

    virtual bool
    onIdle( const gfx::ui::Event& event ) override final
    {
        return false;
    }

  private:
    void
    loadFont( const std::string& font_name )
    {
        labels_font_.loadFromFile( font_name );
    }

    virtual void
    drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const override final
    {
        window.draw( border_, transform );
    }

    virtual void
    drawChildren( gfx::core::Window& window, gfx::core::Transform transform ) const override final
    {
        window.draw( mv_l_, transform );
        window.draw( mv_r_, transform );
        window.draw( mv_u_, transform );
        window.draw( mv_d_, transform );
        window.draw( mv_f_, transform );
        window.draw( mv_b_, transform );
        window.draw( rt_l_, transform );
        window.draw( rt_r_, transform );
        window.draw( rt_u_, transform );
        window.draw( rt_d_, transform );
    }

  private:
    gfx::core::Font labels_font_;

    model::SceneManager& scene_manager_;
    model::Camera&       camera_;

    gfx::ui::Button mv_l_;
    gfx::ui::Button mv_r_;
    gfx::ui::Button mv_u_;
    gfx::ui::Button mv_d_;
    gfx::ui::Button mv_f_;
    gfx::ui::Button mv_b_;
    gfx::ui::Button rt_l_;
    gfx::ui::Button rt_r_;
    gfx::ui::Button rt_u_;
    gfx::ui::Button rt_d_;

    gfx::core::RectangleShape border_;
};

} // namespace view
} // namespace zemax
