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
    window->SetSize( { zemax::Config::Window::Width, zemax::Config::Window::Height } );
    window->SetTitle( "Test" );
    pm.setWindow( window );
    hui::WindowManager wm( &pm, zemax::Config::Window::BackgroundColor );
    auto*              font = window->CreateFont();
    font->LoadFromFile( "assets/JetBrainsMono-Regular.ttf" );
    wm.addWidget( std::make_unique<zemax::view::Zemax>( &pm, font ) );

    wm.run();

    return 0;
}
