#pragma once

#include "gfx/ui/container_widget.hpp"
#include "gfx/ui/widget.hpp"
#include "zemax/config.hpp"
#include "zemax/view/control_panel.hpp"
#include "zemax/view/scene.hpp"
#include <any>
#include <memory>

namespace zemax {
namespace view {

class Zemax : public gfx::ui::ContainerWidget {
  public:
    explicit Zemax()
        : scene_( Config::Scene::Position,
                  Config::Scene::Size,
                  Config::Scene::BackgroundColor,
                  Config::Camera::Position ),
          panel_( scene_.getModel() )
    {
    }

    ~Zemax() = default;

    bool
    propagateEventToChildren( const gfx::ui::Event& event ) override
    {
        if ( event.apply( &panel_ ) )
        {
            return true;
        }

        if ( event.apply( &scene_ ) )
        {
            return true;
        }

        return false;
    }

    void
    draw( gfx::core::Window& window, gfx::core::Transform transform ) const override
    {
        gfx::core::Transform widget_transform = transform.combine( getTransform() );
        window.draw( scene_, widget_transform );
        window.draw( panel_, widget_transform );
    }

  private:
    Scene        scene_;
    ControlPanel panel_;
};

} // namespace view
} // namespace zemax
