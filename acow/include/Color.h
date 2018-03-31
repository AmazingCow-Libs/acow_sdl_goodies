#pragma once

// AmazingCow Libs
#include "acow/cpp_goodies.h"
// acow_sdl_goodies
#include "SDLGoodies_Utils.h"


NS_ACOW_SDL_GOODIES_BEGIN

class Color
{

    //------------------------------------------------------------------------//
    // Colors                                                                 //
    //------------------------------------------------------------------------//
public:
    #define DEFINE_COLOR(_name_, _r_, _g_, _b_, _a_) \
        ACOW_CONSTEXPR_STRICT inline static Color    \
        _name_() noexcept                            \
        {                                            \
            return Color(_r_, _g_, _b_, _a_);        \
        }

    //--------------------------------------------------------------------------
    // BW / Transparent.
    DEFINE_COLOR(White,       255, 255, 255, 255)
    DEFINE_COLOR(Black,         0,   0,   0, 255)
    DEFINE_COLOR(Transparent,   0,   0,   0,   0)

    //--------------------------------------------------------------------------
    // Primary Colors.
    DEFINE_COLOR(Red,  255,   0,   0, 255)
    DEFINE_COLOR(Green,  0, 255,   0, 255)
    DEFINE_COLOR(Blue,   0,   0, 255, 255)

    //------------------------------------------------------------------------------
    // Secondary Colors.
    DEFINE_COLOR(Cyan,      0, 255, 255, 255);
    DEFINE_COLOR(Magenta, 255,   0, 255, 255);
    DEFINE_COLOR(Yellow,  255, 255,   0, 255);

    #undef DEFINE_COLOR


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    ACOW_CONSTEXPR_STRICT inline
    Color(f32 r = 0.0f, f32 g = 0.0f, f32 b = 0.0f, f32 a = 1.0f) noexcept
        : r(r), g(g), b(b), a(a)
    {
        // Empty...
    }

    ACOW_CONSTEXPR_STRICT inline
    Color(i32 r, i32 g, i32 b, i32 a = 255) noexcept
        : Color(u8(r), u8(g), u8(b), u8(a))
    {
        // Empty...
    }

    ACOW_CONSTEXPR_STRICT inline
    Color(u32 r, u32 g, u32 b, u32 a = 255) noexcept
        : Color(u8(r), u8(g), u8(b), u8(a))
    {
        // Empty...
    }

    ACOW_CONSTEXPR_STRICT inline
    Color(u8 r, u8 g, u8 b, u8 a = 255 ) noexcept
        : Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f)
    {
        // Empty...
    }

    ACOW_CONSTEXPR_STRICT inline
    Color(const SDL_Color &sdlColor) noexcept
        : Color(sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a)
    {
        // Empty...
    }

    //------------------------------------------------------------------------//
    // Operators                                                              //
    //------------------------------------------------------------------------//
public:
    //--------------------------------------------------------------------------
    // Equality.
    friend ACOW_CONSTEXPR_STRICT inline
    bool operator ==(const Color &lhs, const Color &rhs) noexcept;

    friend ACOW_CONSTEXPR_STRICT inline
    bool operator !=(const Color &lhs, const Color &rhs) noexcept;

    //--------------------------------------------------------------------------
    // Conversion.
    ACOW_CONSTEXPR_STRICT inline explicit operator SDL_Color() noexcept
    {
        return SDL_Color {
            u8(r * 255),
            u8(g * 255),
            u8(b * 255),
            u8(a * 255)
        };
    }

    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
public:
    f32 r, g, b, a;

}; // class Color


//----------------------------------------------------------------------------//
// Operators                                                                  //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Equality.
ACOW_CONSTEXPR_STRICT inline
bool operator ==(const Color &lhs, const Color &rhs) noexcept
{
    return (lhs.r == rhs.r)
        && (lhs.g == rhs.g)
        && (lhs.b == rhs.b)
        && (lhs.a == rhs.a);
}

ACOW_CONSTEXPR_STRICT inline
bool operator !=(const Color &lhs, const Color &rhs) noexcept
{
    return !(lhs == rhs);
}


NS_ACOW_SDL_GOODIES_END
