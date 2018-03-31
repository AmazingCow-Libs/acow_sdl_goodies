//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Texture.h                                                     //
//  Project   : acow_sdl_goodies                                              //
//  Date      : Mar 06, 2018                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2018                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

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
    inline void
    SafeDestroy(SDL_Texture *pTexture) noexcept
    {
        ACOW_SDL_SAFE_DESTROY_TEXTURE(pTexture);
    }


    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
    ACOW_SHARED_PTR_OF        (SDL_Texture);
    ACOW_UNIQUE_PTR_DELETER_OF(SDL_Texture, decltype(&SafeDestroy));


    //------------------------------------------------------------------------//
    // Create                                                                 //
    //------------------------------------------------------------------------//
    inline SDL_Texture*
    CreateRaw(
        SDL_Renderer *pRenderer,
        Uint32        format,
        int           access,
        int           w,
        int           h) noexcept
    {
        COREASSERT_ASSERT_NOT_NULL(pRenderer);
        auto p_texture = SDL_CreateTexture(pRenderer, format, access, w, h);

        COREASSERT_ASSERT(
            p_texture,
            "Failed to create texture - %s",
            Error::Last()
        );

        return p_texture;
    }

    inline Texture::UPtr
    CreateUnique(
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

    inline Texture::SPtr
    CreateShared(
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

    //------------------------------------------------------------------------//
    // From Surface                                                           //
    //------------------------------------------------------------------------//
    inline SDL_Texture*
    FromSurfaceRaw(SDL_Surface *pSurface, SDL_Renderer *pRenderer) noexcept
    {
        ACOW_ASSERT_NOT_NULL(pSurface);
        ACOW_ASSERT_NOT_NULL(pRenderer);

        auto p_texture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
        COREASSERT_ASSERT(
            p_texture,
            "Can't create texture from surface - %s",
            Error::Last()
        );

        return p_texture;
    }

    inline Texture::UPtr
    FromSurfaceUnique(SDL_Surface *pSurface, SDL_Renderer *pRenderer) noexcept
    {
        return Texture::UPtr(
            FromSurfaceRaw(pSurface, pRenderer),
            Texture::SafeDestroy
        );
    }

    inline Texture::SPtr
    FromSurfaceShared(SDL_Surface *pSurface, SDL_Renderer *pRenderer) noexcept
    {
        return Texture::SPtr(
            FromSurfaceRaw(pSurface, pRenderer),
            Texture::SafeDestroy
        );
    }


    //------------------------------------------------------------------------//
    // Load                                                                   //
    //------------------------------------------------------------------------//
    inline SDL_Texture*
    LoadRaw(
        const std::string &path,
        SDL_Renderer      *pRenderer) noexcept
    {
        ACOW_ASSERT_NOT_STR_EMPTY_OR_WHITESPACE(path.c_str());
        COREASSERT_ASSERT_NOT_NULL(pRenderer);

        auto p_texture = IMG_LoadTexture(pRenderer, path.c_str());

        COREASSERT_ASSERT(
            p_texture,
            "Failed to load texture - Path: (%s) - %s",
            path.c_str(),
            Error::Last()
        );

        return p_texture;
    }

    inline Texture::UPtr
    LoadUnique(
        const std::string &path,
        SDL_Renderer      *pRenderer) noexcept
    {
        return Texture::UPtr(LoadRaw(path, pRenderer), Texture::SafeDestroy);
    }

    inline Texture::SPtr
    LoadShared(
        const std::string &path,
        SDL_Renderer      *pRenderer) noexcept
    {
        return Texture::SPtr(
            LoadRaw(path, pRenderer),
            Texture::SafeDestroy
        );
    }


    //------------------------------------------------------------------------//
    // Query                                                                  //
    //------------------------------------------------------------------------//
    inline acow::math::Size
    QuerySize(SDL_Texture *pTexture) noexcept
    {
        COREASSERT_ASSERT_NOT_NULL(pTexture);

        int w,h;
        SDL_QueryTexture(pTexture, nullptr, nullptr, &w, &h);

        return acow::math::Size(w, h);
    }

} // namespace Texture

NS_ACOW_SDL_GOODIES_END
