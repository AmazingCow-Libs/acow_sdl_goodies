//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : IMG.h                                                         //
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

// SDL
#include "SDL_image.h"
// AmazingCow Libs
#include "acow/cpp_goodies.h"
// acow_sdl_goodies
#include "SDLGoodies_Utils.h"


NS_ACOW_SDL_GOODIES_BEGIN

namespace img
{
    //------------------------------------------------------------------------//
    // Lifecycle Functions                                                                       //
    //------------------------------------------------------------------------//
    void Init(int flags) noexcept;
    void Quit() noexcept;

} // namespace img

NS_ACOW_SDL_GOODIES_END