//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Renderer.h                                                    //
//  Project   : acow_sdl_goodies                                              //
//  Date      : Feb 21, 2018                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2018                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#pragma once

// AmazingCow Libs
#include "acow/cpp_goodies.h"
// acow_sdl_goodies
#include "SDLGoodies_Utils.h"


NS_ACOW_SDL_GOODIES_BEGIN

namespace Renderer {
    //------------------------------------------------------------------------//
    // Functions                                                              //
    //   We need this here because the typedefs need :x
    //------------------------------------------------------------------------//
    void SafeDestroy(SDL_Renderer *pRenderer) noexcept;


    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
    ACOW_SHARED_PTR_OF        (SDL_Renderer);
    ACOW_UNIQUE_PTR_DELETER_OF(SDL_Renderer, decltype(&SafeDestroy));


    //------------------------------------------------------------------------//
    // Functions                                                              //
    //------------------------------------------------------------------------//
    Renderer::SPtr CreateShared(
        SDL_Window *pWindow,
        int         index,
        Uint32      flags) noexcept;

    Renderer::UPtr CreateUnique(
        SDL_Window *pWindow,
        int         index,
        Uint32      flags) noexcept;

    SDL_Renderer* CreateRaw(
        SDL_Window *pWindow,
        int         index,
        Uint32      flags) noexcept;

} // namespace Renderer

NS_ACOW_SDL_GOODIES_END
