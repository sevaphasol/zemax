#include "zemax/view/zemax.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/keyboard.hpp"
#include "gfx/core/vector3.hpp"
#include "gfx/core/window.hpp"
#include "zemax/config.hpp"
#include "zemax/controller/camera.hpp"

namespace zemax {
namespace view {

Zemax::Zemax()
    : scene_manager_( config::Zemax::CameraPos,
                      config::Zemax::WidgetSize.x,
                      config::Zemax::WidgetSize.y ),
      pixels_( config::Zemax::WidgetSize.x * config::Zemax::WidgetSize.y ),
      camera_controller_( scene_manager_.getCamera() )
{
    setPosition(
        gfx::core::Vector2f( config::Zemax::WidgetPosition.x, config::Zemax::WidgetPosition.y ) );
    setSize( gfx::core::Vector2f( config::Zemax::WidgetSize.x, config::Zemax::WidgetSize.y ) );

    scene_manager_.addLight( gfx::core::Vector3f( -15, -5, 10 ), 1.0, 0.3, 0.5 );
    scene_manager_.addLight( gfx::core::Vector3f( 0, 3, 3 ), 1.0, 0.3, 0.5 );
    // scene_manager_.addLight( gfx::core::Vector3f( 0, 0, 0 ), 0.2, 0.3, 0.5 );

    scene_manager_.addSphere( model::Material( gfx::core::Color( 255, 8, 8 ), 0.5f ),
                              gfx::core::Vector3f( -2, 2, -5 ),
                              1.5 );

    // scene_manager_.addAABB( model::Material( gfx::core::Color( 255, 8, 8 ), 0.5f ),
    // gfx::core::Vector3f( -2, 2, 5 ),
    // gfx::core::Vector3f( 1, 1, 1 ) );

    scene_manager_.addSphere( model::Material( gfx::core::Color( 8, 32, 8 ), 0.3f ),
                              gfx::core::Vector3f( 2, 0, -5 ),
                              1.5 );

    // scene_manager_.addPlane( model::Material( gfx::core::Color( 255, 8, 8 ), 0.5 ),
    //  gfx::core::Vector3f( 0, -4, 0 ),
    //  gfx::core::Vector3f( 0, 1, 0 ) );
}

bool
Zemax::onKeyEvent( const gfx::core::Event::KeyEvent& event, bool pressed )
{
    float move_factor   = pressed ? config::Zemax::MoveScale : 0;
    float rotate_factor = pressed ? config::Zemax::RotateScale : 0;

    switch ( event.code )
    {
        case gfx::core::Keyboard::A:
            cam_move_delta_.x = move_factor;
            break;
        case gfx::core::Keyboard::D:
            cam_move_delta_.x = -move_factor;
            break;
        case gfx::core::Keyboard::W:
            cam_move_delta_.z = move_factor;
            break;
        case gfx::core::Keyboard::S:
            cam_move_delta_.z = -move_factor;
            break;
        case gfx::core::Keyboard::Space:
            cam_move_delta_.y = move_factor;
            break;
        case gfx::core::Keyboard::LShift:
            cam_move_delta_.y = -move_factor;
            break;
        case gfx::core::Keyboard::Left:
            cam_rotate_delta_.x = rotate_factor;
            break;
        case gfx::core::Keyboard::Right:
            cam_rotate_delta_.x = -rotate_factor;
            break;
        case gfx::core::Keyboard::Up:
            cam_rotate_delta_.y = rotate_factor;
            break;
        case gfx::core::Keyboard::Down:
            cam_rotate_delta_.y = -rotate_factor;
            break;
        default:
            return false;
    }

    return true;
}

bool
Zemax::onKeyPressSelf( const gfx::core::Event::KeyEvent& event )
{
    return onKeyEvent( event, true );
}

bool
Zemax::onKeyReleaseSelf( const gfx::core::Event::KeyEvent& event )
{
    return onKeyEvent( event, false );
}

bool
Zemax::onIdleSelf( const gfx::core::Event::IdleEvent& event )
{
    camera_controller_.move( cam_move_delta_ );
    camera_controller_.rotate( cam_rotate_delta_ );

#pragma omp parallel for
    for ( uint row = 0; row < config::Zemax::WidgetSize.y; row++ )
    {
        for ( uint col = 0; col < config::Zemax::WidgetSize.x; col++ )
        {
            gfx::core::Vector2f pos = gfx::core::Vector2f( col, row );
            gfx::core::Color    color =
                scene_manager_.calcPixelColor( row, col, config::Zemax::BackgroundColor );

            pixels_[row * config::Zemax::WidgetSize.x + col] = gfx::core::Vertex( pos, color );
        }
    }

    return false;
}

void
Zemax::drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const
{
    window.draw( pixels_.data(), pixels_.size(), gfx::core::Points, transform );
}

} // namespace view
} // namespace zemax
