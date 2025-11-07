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

    // pm.loadGetBounds();
    fprintf( stderr, "debug in %s:%d:%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ );
    auto* window = dr4_backend->CreateWindow();
    fprintf( stderr, "debug in %s:%d:%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ );
    window->SetSize( { zemax::Config::Window::Width, zemax::Config::Window::Height } );
    std::cerr << window->GetSize().x << " " << window->GetSize().y << std::endl;
    window->SetTitle( "Test" );
    fprintf( stderr, "debug in %s:%d:%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ );
    pm.setWindow( window );
    fprintf( stderr, "debug in %s:%d:%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ );
    hui::WindowManager wm( &pm, dr4::Color( 128, 128, 128, 255 ) );
    fprintf( stderr, "debug in %s:%d:%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ );
    auto* font = window->CreateFont();
    fprintf( stderr, "debug in %s:%d:%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ );
    font->loadFromFile( "assets/JetBrainsMono-Regular.ttf" );
    fprintf( stderr, "debug in %s:%d:%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ );
    wm.addWidget( std::make_unique<zemax::view::Zemax>( &pm, font ) );
    fprintf( stderr, "debug in %s:%d:%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__ );

    wm.run();

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
