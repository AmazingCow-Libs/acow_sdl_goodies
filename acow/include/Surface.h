//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Surface.h                                                     //
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

namespace Surface
{
    //------------------------------------------------------------------------//
    // Functions                                                              //
    //   We need this here because the typedefs need :x                       //
    //------------------------------------------------------------------------//
    inline void
    SafeDestroy(SDL_Surface *pSurface) noexcept
    {
        ACOW_SDL_SAFE_DESTROY_SURFACE(pSurface);
    }


    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
    ACOW_SHARED_PTR_OF        (SDL_Surface);
    ACOW_UNIQUE_PTR_DELETER_OF(SDL_Surface, decltype(&SafeDestroy));


    //------------------------------------------------------------------------//
    // Create                                                                 //
    //------------------------------------------------------------------------//
    inline SDL_Surface*
    CreateRaw(
        void  *pPixels,
        int    width,
        int    height,
        int    depth,
        int    pitch,
        Uint32 format) noexcept
    {
        COREASSERT_ASSERT(pPixels, "pPixels can't be null");

        auto p_surface = SDL_CreateRGBSurfaceWithFormatFrom(
            pPixels,
            width,
            height,
            depth,
            pitch,
            format
        );
        COREASSERT_ASSERT(
            p_surface,
            "Failed to create surface - %s",
            Error::Last()
        );

        return p_surface;
    }

    inline Surface::UPtr
    CreateUnique(
        void  *pPixels,
        int    width,
        int    height,
        int    depth,
        int    pitch,
        Uint32 format) noexcept
    {
        return Surface::UPtr(
            CreateRaw(pPixels, width, height, depth, pitch, format),
            Surface::SafeDestroy
        );
    }

    inline Surface::SPtr
    CreateShared(
        void  *pPixels,
        int    width,
        int    height,
        int    depth,
        int    pitch,
        Uint32 format) noexcept
    {
        return Surface::SPtr(
            CreateRaw(pPixels, width, height, depth, pitch, format),
            [](SDL_Surface *pSurface){
                Surface::SafeDestroy(pSurface);
            }
        );
    }

    //------------------------------------------------------------------------//
    // Save                                                                   //
    //------------------------------------------------------------------------//
    inline void
    Save(const std::string &path, SDL_Surface *pSurface) noexcept
    {
        COREASSERT_ASSERT(pSurface,      "pSurface can't be null");
        COREASSERT_ASSERT(!path.empty(), "path can't be empty");

        auto result = IMG_SavePNG(pSurface, path.c_str());

        COREASSERT_ASSERT(
           (result == 0),
            "Failed to save surface - Path: (%s) - %s",
            path.c_str(),
            Error::Last()
        );
    }

} // namespace Surface

NS_ACOW_SDL_GOODIES_END
