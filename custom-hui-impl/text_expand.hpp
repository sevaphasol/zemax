#pragma once

#include "dr4/math/rect.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "plugin_manager.hpp"

void
moveInCenterOfRect( cum::PluginManager* pm,
                    dr4::Text&          text,
                    const dr4::Vec2f&   rect_size,
                    const dr4::Vec2f&   rect_pos = { 0, 0 } )
{
    // auto get_bounds = pm->getGetBounds();

    // const dr4::Rect2f text_bounds = ( &text->*get_bounds )();

    // text.pos.x = rect_pos.x + rect_size.x / 2.0f; //- text_bounds.size.x / 2.0f;
    // text.pos.y = rect_pos.y + rect_size.y / 2.0f; //- text_bounds.size.y / 2.0f;

    text.pos.x = rect_pos.x + rect_size.x / 2.0f - text.text.length() * 3.2;
    text.pos.y = rect_pos.y + rect_size.y / 2.0f - 2.5f;
}
