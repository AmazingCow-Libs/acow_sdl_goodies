//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Destroy.h                                                     //
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

// acow_sdl_goodies
#include "./SDL.h"
#include "./TTF.h"


//----------------------------------------------------------------------------//
// Surface                                                                    //
//----------------------------------------------------------------------------//
#define ACOW_SDL_SAFE_DESTROY_FONT(_font_)  \
    do {                                    \
        if(_font_) {                        \
            TTF_CloseFont(_font_);          \
            _font_ = nullptr;               \
        }                                   \
    } while(0)


//----------------------------------------------------------------------------//
// Surface                                                                    //
//----------------------------------------------------------------------------//
#define ACOW_SDL_SAFE_DESTROY_SURFACE(_surface_) \
    do {                                         \
        if(_surface_) {                          \
            SDL_FreeSurface(_surface_);          \
            _surface_ = nullptr;                 \
        }                                        \
    } while(0)


//----------------------------------------------------------------------------//
// Texture                                                                    //
//----------------------------------------------------------------------------//
#define ACOW_SDL_SAFE_DESTROY_TEXTURE(_texture_) \
    do {                                         \
        if(_texture_) {                          \
            SDL_DestroyTexture(_texture_);       \
            _texture_ = nullptr;                 \
        }                                        \
    } while(0)


//----------------------------------------------------------------------------//
// Window                                                                     //
//----------------------------------------------------------------------------//
#define ACOW_SDL_SAFE_DESTROY_WINDOW(_window_) \
    do {                                       \
        if(_window_) {                         \
            SDL_DestroyWindow(_window_);       \
            _window_ = nullptr;                \
        }                                      \
    } while(0)


//----------------------------------------------------------------------------//
// Renderer                                                                   //
//----------------------------------------------------------------------------//
#define ACOW_SDL_SAFE_DESTROY_RENDERER(_renderer_) \
    do {                                           \
        if(_renderer_) {                           \
            SDL_DestroyRenderer(_renderer_);       \
            _renderer_ = nullptr;                  \
        }                                          \
    } while(0)
