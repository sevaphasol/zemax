#pragma once

#include <cstddef>
#include <dlfcn.h>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "dr4/math/rect.hpp"
#include "dr4/window.hpp"
#include "misc/dr4_ifc.hpp"

namespace cum {

class PluginManager {
  public:
    PluginManager() {}

    dr4::DR4Backend*
    getDrawLibBackend()
    {
        return drawlib_backend_;
    }

    const dr4::Window*
    getWindow() const
    {
        return window_;
    }

    dr4::Window*
    getWindow()
    {
        return window_;
    }

    void
    setWindow( dr4::Window* window )
    {
        window_ = window;
    }

    // auto
    // getGetBounds()
    // {
    // return get_bounds_;
    // }

    //     void
    //     loadGetBounds()
    //     {
    //         auto* get_bounds_func = dlsym( drawlib_, "_ZNK3dr44Text9GetBoundsEv" );
    //         if ( get_bounds_func == nullptr )
    //         {
    //             std::cerr << "Couldn't load Text::GetBounds() symbol" << std::endl;
    //         }
    //
    //         get_bounds_ = reinterpret_cast<dr4::Rect2f ( dr4::Text::* )()>( get_bounds_func );
    //     }

    void
    loadDrawLib( const char* name )
    {
        drawlib_ = dlopen( name, RTLD_LAZY );
        if ( drawlib_ == nullptr )
        {
            throw std::runtime_error( dlerror() );
        }
    }

    void
    loadDrawBackend()
    {
        auto* create_backend_func = dlsym( drawlib_, dr4::DR4BackendFunctionName );
        if ( create_backend_func == nullptr )
        {
            std::cerr << "Couldn't load createDr4Backend symbol" << std::endl;
        }

        drawlib_backend_ = reinterpret_cast<dr4::DR4Backend* (*)()>( create_backend_func )();
        if ( drawlib_backend_ == nullptr )
        {
            std::cerr << "Couldn't create DR4Backend" << std::endl;
        }
    }

  private:
    void* drawlib_; // Library for drawing graphics

    dr4::Window* window_;
    // dr4::Rect2f ( dr4::Text::*get_bounds_ )();

    dr4::DR4Backend* drawlib_backend_;
};

} // namespace cum
