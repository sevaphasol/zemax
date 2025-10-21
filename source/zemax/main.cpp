
#include "gfx/core/color.hpp"
#include "gfx/ui/window_manager.hpp"
#include "zemax/config.hpp"
#include "zemax/view/zemax.hpp"

int
main()
{
    gfx::ui::WindowManager wm( config::Window::Width,
                               config::Window::Height,
                               config::Window::Title );

    wm.setBackgroundColor( gfx::core::Color( 100, 100, 100 ) );

    wm.addWidget( std::make_unique<zemax::view::Zemax>() );

    wm.run();

    return 0;
}
