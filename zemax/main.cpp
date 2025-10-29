#include "gfx/ui/window_manager.hpp"
#include "zemax/config.hpp"
#include "zemax/view/zemax.hpp"

int
main()
{
    gfx::ui::WindowManager wm( zemax::Config::Window::Width,
                               zemax::Config::Window::Height,
                               zemax::Config::Window::Title,
                               std::make_unique<zemax::view::Zemax>() );

    wm.run();

    return 0;
}
