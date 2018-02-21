//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Window.h                                                      //
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

namespace Window {
    //------------------------------------------------------------------------//
    // Functions                                                              //
    //   We need this here because the typedefs need :x
    //------------------------------------------------------------------------//
    void SafeDestroy(SDL_Window *pWindow) noexcept;


    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
    ACOW_SHARED_PTR_OF        (SDL_Window);
    ACOW_UNIQUE_PTR_DELETER_OF(SDL_Window, decltype(&SafeDestroy));


    //------------------------------------------------------------------------//
    // Functions                                                              //
    //------------------------------------------------------------------------//
    Window::SPtr CreateShared(
        const std::string &title,
        int x, int y,
        int w, int h,
        Uint32 flags) noexcept;

    Window::UPtr CreateUnique(
        const std::string &title,
        int x, int y,
        int w, int h,
        Uint32 flags) noexcept;

    SDL_Window* CreateRaw(
        const std::string &title,
        int x, int y,
        int w, int h,
        Uint32 flags) noexcept;

} // namespace Window

NS_ACOW_SDL_GOODIES_END
