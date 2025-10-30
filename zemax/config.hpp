#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/vector3.hpp"
#include <sys/types.h>

namespace zemax {

struct Config
{
    struct Common
    {
        struct Font
        {
            static constexpr const char* const   Name  = "assets/JetBrainsMono-Regular.ttf";
            static inline const gfx::core::Color Color = gfx::core::Color::White;
        };
    };

    struct Window
    {
        static constexpr size_t            Width           = 1750.0f;
        static constexpr size_t            Height          = 900.0f;
        static constexpr const char* const Title           = "Zemax";
        static constexpr gfx::core::Color  BackgroundColor = { 100, 100, 100 };
    };

    struct ControlPanel
    {
        static constexpr gfx::core::Vector2f Position        = { 50.0f, 50.0f };
        static constexpr gfx::core::Vector2f Size            = { 380.0f, 798.0f };
        static constexpr gfx::core::Color    BackgroundColor = { 32, 32, 32 };
        static constexpr gfx::core::Color    BorderColor     = { 255, 0, 0 };
        static constexpr float               BorderThickness = 2.0f;

        struct Button
        {
            static constexpr gfx::core::Vector2f Size = { 100.0f, 50.0f };

            static constexpr gfx::core::Color DefaultColor = { 64, 64, 64 };
            static constexpr gfx::core::Color HoveredColor = { 96, 96, 96 };
            static constexpr gfx::core::Color PressedColor = { 128, 128, 128 };

            static constexpr const char*            FontName  = "assets/JetBrainsMono-Regular.ttf";
            static constexpr const gfx::core::Color FontColor = gfx::core::Color::White;
            static constexpr const size_t           FontSize  = 12;

            struct MvL
            {
                static constexpr gfx::core::Vector2f Position = { 30.0f, 50.0f };
                static constexpr const char*         Title    = "Move left";
            };

            struct MvR
            {
                static constexpr gfx::core::Vector2f Position = { 30.0f, 110.0f };
                static constexpr const char*         Title    = "Move right";
            };

            struct MvU
            {
                static constexpr gfx::core::Vector2f Position = { 140.0f, 50.0f };
                static constexpr const char*         Title    = "Move up";
            };

            struct MvD
            {
                static constexpr gfx::core::Vector2f Position = { 140.0f, 110.0f };
                static constexpr const char*         Title    = "Move down";
            };

            struct MvF
            {
                static constexpr gfx::core::Vector2f Position = { 250.0f, 50.0f };
                static constexpr const char*         Title    = "Move forward";
            };

            struct MvB
            {
                static constexpr gfx::core::Vector2f Position = { 250.0f, 110.0f };
                static constexpr const char*         Title    = "Move Backward";
            };

            struct RtL
            {
                static constexpr gfx::core::Vector2f Position = { 30.0f, 200.0f };
                static constexpr const char*         Title    = "Rotate left";
            };

            struct RtR
            {
                static constexpr gfx::core::Vector2f Position = { 30.0f, 260.0f };
                static constexpr const char*         Title    = "Rotate rigth";
            };

            struct RtU
            {
                static constexpr gfx::core::Vector2f Position = { 140.0f, 200.0f };
                static constexpr const char*         Title    = "Rotate up";
            };

            struct RtD
            {
                static constexpr gfx::core::Vector2f Position = { 140.0f, 260.0f };
                static constexpr const char*         Title    = "Rotate down";
            };

            struct ScaleUp
            {
                static constexpr gfx::core::Vector2f Position = { 250.0f, 200.0f };
                static constexpr const char*         Title    = "Scale up";
            };

            struct ScaleDown
            {
                static constexpr gfx::core::Vector2f Position = { 250.0f, 260.0f };
                static constexpr const char*         Title    = "Scale down";
            };

            struct MoveObjLeft
            {
                static constexpr gfx::core::Vector2f Position = { 30.0f, 350.0f };
                static constexpr const char*         Title    = "Move obj left";
            };

            struct MoveObjRight
            {
                static constexpr gfx::core::Vector2f Position = { 30.0f, 410.0f };
                static constexpr const char*         Title    = "Move obj right";
            };

            struct MoveObjUp
            {
                static constexpr gfx::core::Vector2f Position = { 140.0f, 350.0f };
                static constexpr const char*         Title    = "Move obj up";
            };

            struct MoveObjDown
            {
                static constexpr gfx::core::Vector2f Position = { 140.0f, 410.0f };
                static constexpr const char*         Title    = "Move obj down";
            };

            struct MoveObjForwrd
            {
                static constexpr gfx::core::Vector2f Position = { 250.0f, 350.0f };
                static constexpr const char*         Title    = "Move obj fwd";
            };

            struct MoveObjBackward
            {
                static constexpr gfx::core::Vector2f Position = { 250.0f, 410.0f };
                static constexpr const char*         Title    = "Move obj bwd";
            };

            struct AddObj
            {
                static constexpr gfx::core::Vector2f Position = { 30.0f, 500.0f };
                static constexpr const char*         Title    = "Add obj";
            };

            struct CopyObj
            {
                static constexpr gfx::core::Vector2f Position = { 140.0f, 500.0f };
                static constexpr const char*         Title    = "Copy obj";
            };

            struct DeleteObj
            {
                static constexpr gfx::core::Vector2f Position = { 250.0f, 500.0f };
                static constexpr const char*         Title    = "Delete obj";
            };
        };

        struct TextField
        {
            static constexpr gfx::core::Vector2f Size = { 40.0f, 20.0f };

            struct X
            {
                static constexpr gfx::core::Vector2f Position = { 135.0f, 570.0f };
                static constexpr const char*         Title    = "X";
            };

            struct Y
            {
                static constexpr gfx::core::Vector2f Position = { 135.0f, 600.0f };
                static constexpr const char*         Title    = "Y";
            };

            struct Z
            {
                static constexpr gfx::core::Vector2f Position = { 135.0f, 630.0f };
                static constexpr const char*         Title    = "Z";
            };

            struct Size
            {
                static constexpr gfx::core::Vector2f Position = { 135.0f, 660.0f };
                static constexpr const char*         Title    = "S";
            };

            struct R
            {
                static constexpr gfx::core::Vector2f Position = { 195.0f, 570.0f };
                static constexpr const char*         Title    = "R";
            };

            struct G
            {
                static constexpr gfx::core::Vector2f Position = { 195.0f, 600.0f };
                static constexpr const char*         Title    = "G";
            };

            struct B
            {
                static constexpr gfx::core::Vector2f Position = { 195.0f, 630.0f };
                static constexpr const char*         Title    = "B";
            };

            struct RefFactor
            {
                static constexpr gfx::core::Vector2f Position = { 195.0f, 660.0f };
                static constexpr const char*         Title    = "F";
            };
        };

        struct ScrollBar
        {
            static constexpr gfx::core::Vector2f Position = { 30.0f, 570.0f };
            static constexpr gfx::core::Vector2f Size     = { 90.0f, 110.0f };

            struct Button
            {
                static constexpr gfx::core::Vector2f Position = { 15.0f, 0.0f };
                static constexpr gfx::core::Vector2f Size     = { 75.0f, 110.0f };
            };
        };
    };

    struct Scene
    {
        static constexpr gfx::core::Vector2f Position        = { 500.0f, 50.0f };
        static constexpr gfx::core::Vector2f Size            = { 1200.0f, 800.0f };
        static constexpr gfx::core::Color    BackgroundColor = { 16, 16, 16 };
    };

    struct Camera
    {
        static constexpr gfx::core::Vector3f Position = { 0.0f, 0.0f, 0.0f };

        static constexpr float MoveFactor    = 0.1f;
        static constexpr float ObjMoveFactor = 0.1f;
        static constexpr float RotateFactor  = 0.03f;
        static constexpr float ScaleFactor   = 0.03f;
    };
};

} // namespace zemax
