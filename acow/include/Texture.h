#pragma once

// std
#include <string>
// AmazingCow Libs
#include "CoreAssert/CoreAssert.h"
#include "acow/math_goodies.h"
// acow_sdl_goodies
#include "SDLGoodies_Utils.h"
#include "IMG.h"
#include "Error.h"
#include "Destroy.h"

NS_ACOW_SDL_GOODIES_BEGIN

namespace Texture
{
    //------------------------------------------------------------------------//
    // Functions                                                              //
    //   We need this here because the typedefs need :x                       //
    //------------------------------------------------------------------------//
    inline void SafeDestroy(SDL_Texture *pTexture) noexcept
    {
        ACOW_SDL_SAFE_DESTROY_TEXTURE(pTexture);
    }


    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
    ACOW_SHARED_PTR_OF        (SDL_Texture);
    ACOW_UNIQUE_PTR_DELETER_OF(SDL_Texture, decltype(&SafeDestroy));


    //------------------------------------------------------------------------//
    // Load / Create                                                          //
    //------------------------------------------------------------------------//
    inline SDL_Texture* CreateRaw(
        SDL_Renderer *pRenderer,
        Uint32        format,
        int           access,
        int           w,
        int           h) noexcept
    {
        COREASSERT_ASSERT(pRenderer, "pRenderer can't be null");
        auto p_texture = SDL_CreateTexture(pRenderer, format, access, w, h);

        COREASSERT_ASSERT(
            p_texture,
            "Failed to create texture - %s",
            Error::Last()
        );

        return p_texture;
    }

    inline Texture::UPtr CreateUnique(
        SDL_Renderer *pRenderer,
        Uint32        format,
        int           access,
        int           w,
        int           h) noexcept
    {
        return Texture::UPtr(
            CreateRaw(pRenderer, format, access, w, h),
            Texture::SafeDestroy
        );
    }

    inline Texture::SPtr CreateShared(
        SDL_Renderer *pRenderer,
        Uint32        format,
        int           access,
        int           w,
        int           h) noexcept
    {
        return Texture::SPtr(
            CreateRaw(pRenderer, format, access, w, h),
            [](SDL_Texture *pTexture){
                Texture::SafeDestroy(pTexture);
            }
        );
    }

    inline SDL_Texture* LoadFromFile(
        const std::string &path,
        SDL_Renderer      *pRenderer) noexcept
    {
        COREASSERT_ASSERT(pRenderer, "pRenderer can't be null");
        auto p_texture = IMG_LoadTexture(pRenderer, path.c_str());

        COREASSERT_ASSERT(
            p_texture,
            "Failed to load texture - Path: (%s) - %s",
            Error::Last()
        );

        return p_texture;
    }


    //------------------------------------------------------------------------//
    // Query                                                                  //
    //------------------------------------------------------------------------//
    inline acow::math::Size QuerySize(SDL_Texture *pTexture) noexcept
    {
        COREASSERT_ASSERT(pTexture, "pTexture can't be null");

        int w,h;
        SDL_QueryTexture(pTexture, nullptr, nullptr, &w, &h);
        return acow::math::Size(w, h);
    }

} // namespace Texture

NS_ACOW_SDL_GOODIES_END
