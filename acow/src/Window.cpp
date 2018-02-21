//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Window.cpp                                                    //
//  Project   : acow_sdl_goodies                                              //
//  Date      : Feb 21, 2018                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2018                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "../include/Window.h"
// AmazingCow Libs
#include "CoreAssert/CoreAssert.h"
// acow_sdl_goodies
#include "../include/Error.h"

// Usings
using namespace acow;
using namespace sdl;


//----------------------------------------------------------------------------//
// Functions                                                                  //
//----------------------------------------------------------------------------//
void Window::SafeDestroy(SDL_Window *pWindow) noexcept
{
    if(pWindow)
        SDL_DestroyWindow(pWindow);
}

Window::SPtr Window::CreateShared(
    const std::string &title,
    int x, int y,
    int w, int h,
    Uint32 flags) noexcept
{
    // CreateRaw assures that it'll be a successful call or abort.
    auto p_raw = Window::CreateRaw(title, x, y, w, h, flags);

    return Window::SPtr(
        p_raw,
        [](SDL_Window *pWindow){
            Window::SafeDestroy(pWindow);
        }
    );
}

Window::UPtr Window::CreateUnique(
    const std::string &title,
    int x, int y,
    int w, int h,
    Uint32 flags) noexcept
{
    // CreateRaw assures that it'll be a successful call or abort.
    auto p_raw = Window::CreateRaw(title, x, y, w, h, flags);

    return Window::UPtr(
        p_raw,
        Window::SafeDestroy
    );
}

SDL_Window* Window::CreateRaw(
    const std::string &title,
    int x, int y,
    int w, int h,
    Uint32 flags) noexcept
{
    COREASSERT_ASSERT(w >= 0 && h >= 0, "Window can't have negative size.");

    auto p_window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    COREASSERT_ASSERT(p_window, "Failed to create window - %s", Error::Last());

    return p_window;
}