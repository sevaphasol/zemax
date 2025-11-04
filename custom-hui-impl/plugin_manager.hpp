#pragma once

#include <cstddef>
#include <dlfcn.h>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "misc/dr4_ifc.hpp"

namespace cum {

class PluginManager {
  public:
    PluginManager() { std::cerr << "OK on " << __LINE__ << std::endl; }

    dr4::DR4Backend*
    getDrawLibBackend()
    {
        return drawlib_backend_;
    }

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

    dr4::DR4Backend* drawlib_backend_;
};

} // namespace cum
