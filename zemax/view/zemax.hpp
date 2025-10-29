#pragma once

#include "gfx/ui/widget/container.hpp"
#include "zemax/config.hpp"
#include "zemax/view/control_panel.hpp"
#include "zemax/view/scene.hpp"

#include <iostream>

namespace zemax {
namespace view {

class Zemax : public gfx::ui::ContainerWidget {
  public:
    explicit Zemax()
        : scene_( Config::Scene::Position,
                  Config::Scene::Size,
                  Config::Scene::BackgroundColor,
                  Config::Camera::Position ),
          gfx::ui::ContainerWidget( { 0, 0 }, { Config::Window::Width, Config::Window::Height } ),
          panel_( scene_.getModel() )
    {
    }

    ~Zemax() = default;

    bool
    propagate( const gfx::ui::Event& event ) override final
    {
        std::cerr << "propagate " << typeid( event ).name() << std::endl;

        if ( event.apply( &scene_ ) )
        {
            return true;
        }

        if ( event.apply( &panel_ ) )
        {
            return true;
        }

        return false;
    }

    void
    drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const override
    {
    }

    void
    drawChildren( gfx::core::Window& window, gfx::core::Transform transform ) const override
    {
        std::cerr << __PRETTY_FUNCTION__ << ":" << getPosition().x << " " << getPosition().y
                  << std::endl;

        window.draw( scene_ );
        window.draw( panel_ );
    }

  private:
    Scene        scene_;
    ControlPanel panel_;
};

} // namespace view
} // namespace zemax
