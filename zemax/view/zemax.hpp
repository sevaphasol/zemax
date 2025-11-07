#pragma once

#include "custom-hui-impl/container_widget.hpp"
#include "custom-hui-impl/widget.hpp"
#include "dr4/texture.hpp"
#include "gfx/core/font.hpp"
#include "zemax/config.hpp"
#include "zemax/view/control_panel.hpp"
#include "zemax/view/scene.hpp"
#include <any>
#include <memory>

namespace zemax {
namespace view {

class Zemax : public hui::ContainerWidget {
  public:
    explicit Zemax( cum::PluginManager* pm, dr4::Font* font )
        : hui::ContainerWidget( pm, { 0, 0 }, { Config::Window::Width, Config::Window::Height } ),
          scene_( pm,
                  font,
                  Config::Scene::Position,
                  Config::Scene::Size,
                  Config::Scene::BackgroundColor,
                  Config::Camera::Position ),
          panel_( pm, font, scene_.getModel() )
    {
        // fprintf( stderr, "debug in %s:%d:%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ );
        scene_.setParent( this );
        panel_.setParent( this );
    }

    ~Zemax() = default;

    bool
    propagateEventToChildren( const hui::Event& event ) override
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
    RedrawMyTexture() const override
    {
        scene_.Redraw();
        panel_.Redraw();
    }

  private:
    Scene        scene_;
    ControlPanel panel_;
};

} // namespace view
} // namespace zemax
