#include "custom-hui-impl/plugin_manager.hpp"
#include "custom-hui-impl/window_manager.hpp"
#include "dr4/math/vec2.hpp"
#include "gfx/ui/window_manager.hpp"
#include "zemax/config.hpp"
#include "zemax/view/zemax.hpp"

#include "misc/dr4_ifc.hpp"
#include <memory>

int
main()
{
    cum::PluginManager pm;

    pm.loadDrawLib( "lib/libdr4.so" );
    pm.loadDrawBackend();

    auto* dr4_backend = pm.getDrawLibBackend();

    auto* window = dr4_backend->CreateWindow();

    window->SetSize( dr4::Vec2f( 1000.0f, 1000.0f ) );
    window->SetTitle( "Test" );

    hui::WindowManager wm( window, dr4::Color( 128, 128, 128, 255 ) );

    wm.run();

    wm.addWidget( std::make_unique<zemax::view::Zemax>() );

    // gfx::ui::WindowManager wm( zemax::Config::Window::Width,
    //    zemax::Config::Window::Height,
    //    zemax::Config::Window::Title );
    //
    // wm.setBackgroundColor( zemax::Config::Window::BackgroundColor );
    //
    // wm.addWidget( std::make_unique<zemax::view::Zemax>() );
    //
    // wm.run();

    return 0;
}
