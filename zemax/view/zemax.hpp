#pragma once

#include "gfx/ui/widget.hpp"
#include "gfx/ui/widget_container.hpp"
#include "zemax/config.hpp"
#include "zemax/view/control_panel.hpp"
#include "zemax/view/scene.hpp"
#include <memory>

namespace zemax {
namespace view {

class Zemax : public gfx::ui::WidgetVectorContainer {
  public:
    ~Zemax() = default;
    explicit Zemax()
    {
        addChild( std::make_unique<view::Scene>( Config::Scene::Position,
                                                 Config::Scene::Size,
                                                 Config::Scene::BackgroundColor,
                                                 Config::Camera::Position ) );

        addChild( std::make_unique<view::ControlPanel>(
            dynamic_cast<view::Scene*>( children_[Scene].get() )->getModel() ) );
    }

  private:
    enum ChildCode {
        Scene        = 0,
        ControlPanel = 1,
    };
};

} // namespace view
} // namespace zemax
