#pragma once

#include "zemax/model/rendering/scene_manager.hpp"
#include <vector>

namespace zemax {
namespace model {

class ScenesManager {
  public:
    ScenesManager() {}

    void
    onScroll( float factor )
    {
        active_scene_idx = ( factor < 0.5 ) ? 0 : 1;
    }

    model::SceneManager&
    getActiveScene()
    {
        return scenes[active_scene_idx];
    }

    size_t                    active_scene_idx = 0;
    std::vector<SceneManager> scenes;
};

} // namespace model
} // namespace zemax
