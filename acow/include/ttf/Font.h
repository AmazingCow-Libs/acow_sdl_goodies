#pragma once

// acow_sdl_goodies
#include "acow/include/SDLGoodies_Utils.h"
#include "acow/include/Color.h"
#include "acow/include/Destroy.h"
#include "acow/include/Error.h"
#include "acow/include/TTF.h"
#include "acow/include/Surface.h"
#include "acow/include/Texture.h"

namespace acow { namespace sdl { namespace ttf {

namespace Font
{
    //------------------------------------------------------------------------//
    // Functions                                                              //
    //   We need this here because the typedefs need :x                       //
    //------------------------------------------------------------------------//
    inline void
    SafeDestroy(TTF_Font *pFont) noexcept
    {
        ACOW_SDL_SAFE_DESTROY_FONT(pFont);
    }


    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
    ACOW_SHARED_PTR_OF        (TTF_Font);
    ACOW_UNIQUE_PTR_DELETER_OF(TTF_Font, decltype(&SafeDestroy));

    enum class RenderMode { Solid, Shaded, Blended };


    //------------------------------------------------------------------------//
    // Load                                                                   //
    //------------------------------------------------------------------------//
    inline TTF_Font*
    LoadRaw(
        const std::string &path,
        u32                size,
        u32                index = 0) noexcept
    {
        ACOW_ASSERT_NOT_STR_EMPTY_OR_WHITESPACE(path.c_str());
        COREASSERT_ASSERT(size != 0, "size can't be 0.");

        auto p_font = TTF_OpenFontIndex(path.c_str(), size, index);

        COREASSERT_ASSERT(
            p_font,
            "Failed to load font - Path: (%s) - %s",
            path.c_str(),
            Error::Last()
        );

        return p_font;
    }

    inline Font::UPtr
    LoadUnique(
        const std::string &path,
        u32                size,
        u32                index = 0) noexcept
    {
        return Font::UPtr(LoadRaw(path, size, index), Font::SafeDestroy);
    }

    inline Font::SPtr
    LoadShared(
        const std::string &path,
        u32                size,
        u32                index = 0) noexcept
    {
        return Font::SPtr(LoadRaw(path, size, index), Font::SafeDestroy);
    }


    //------------------------------------------------------------------------//
    // Render                                                                 //
    //------------------------------------------------------------------------//
    inline SDL_Surface*
    RenderToSurfaceRaw(
        TTF_Font          *pFont,
        const std::string &text,
        RenderMode         renderMode,
        Color              foreground = Color::Black      (),
        Color              background = Color::Transparent()) noexcept
    {
        COREASSERT_ASSERT_NOT_NULL(pFont);
        // COWTODO(n2omatt): What we should do about the text empty???

        SDL_Surface *p_surface = nullptr;
        switch(renderMode) {
            case RenderMode::Solid : {
                p_surface = TTF_RenderText_Solid(
                    pFont,
                    text.c_str(),
                    (SDL_Color)(foreground)
                );
            } break;

            case RenderMode::Shaded : {
                p_surface = TTF_RenderText_Shaded(
                    pFont,
                    text.c_str(),
                    (SDL_Color)(foreground),
                    (SDL_Color)(background)
                );
            } break;

            case RenderMode::Blended : {
                p_surface = TTF_RenderText_Blended(
                    pFont,
                    text.c_str(),
                    (SDL_Color)(foreground)
                );
            } break;
        }

        COREASSERT_ASSERT(
            p_surface,
            "Can't render text to surface - Text: (%s) - RenderMode: (%d) - Foreground: (%s) - Background: (%s)",
            text.c_str(),
            renderMode,
            foreground.GetHex(),
            background.GetHex()
        );

        return p_surface;
    }

    inline Surface::UPtr
    RenderToSurfaceUnique(
        TTF_Font          *pFont,
        const std::string &text,
        RenderMode         renderMode,
        Color              foreground = Color::Black      (),
        Color              background = Color::Transparent()) noexcept
    {
        auto p_surface = RenderToSurfaceRaw(
            pFont,
            text,
            renderMode,
            foreground,
            background
        );

        return Surface::UPtr(p_surface, Surface::SafeDestroy);
    }

    inline Surface::SPtr
    RenderToSurfaceShared(
        TTF_Font          *pFont,
        const std::string &text,
        RenderMode         renderMode,
        Color              foreground = Color::Black      (),
        Color              background = Color::Transparent()) noexcept
    {
        auto p_surface = RenderToSurfaceRaw(
            pFont,
            text,
            renderMode,
            foreground,
            background
        );

        return Surface::SPtr(p_surface, Surface::SafeDestroy);
    }

} // namespace Font
} // namespace ttf
} // namespace sdl
} // namespace acow
