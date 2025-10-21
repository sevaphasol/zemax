#pragma once

#include "gfx/core/vector3.hpp"
#include "gfx/core/vertex.hpp"
#include "gfx/ui/widget.hpp"
#include "zemax/controller/camera.hpp"
#include "zemax/model/camera.hpp"
#include "zemax/model/scene_manager.hpp"

#include <vector>

namespace zemax {
namespace view {

class Zemax : public gfx::ui::Widget {
  public:
    explicit Zemax();
    virtual ~Zemax() = default;

    virtual bool
    onIdleSelf( const gfx::core::Event::IdleEvent& event ) override;

    virtual bool
    onKeyPressSelf( const gfx::core::Event::KeyEvent& event ) override;

    bool
    onKeyEvent( const gfx::core::Event::KeyEvent& event, bool pressed );

    virtual bool
    onKeyReleaseSelf( const gfx::core::Event::KeyEvent& event ) override;

  private:
    void
    drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const override;

  private:
    gfx::core::Vector3f            cam_move_delta_;
    gfx::core::Vector2f            cam_rotate_delta_;
    std::vector<gfx::core::Vertex> pixels_;
    model::SceneManager            scene_manager_;
    controller::Camera             camera_controller_;
};

} // namespace view
} // namespace zemax
