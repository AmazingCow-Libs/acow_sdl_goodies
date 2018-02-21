//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Renderer.cpp                                                  //
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
#include "../include/Renderer.h"
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
void Renderer::SafeDestroy(SDL_Renderer *pRenderer) noexcept
{
    if(pRenderer)
        SDL_DestroyRenderer(pRenderer);
}

Renderer::SPtr Renderer::CreateShared(
    SDL_Window *pWindow,
    int         index,
    Uint32      flags) noexcept
{
    // CreateRaw assures that it'll be a successful call or abort.
    auto p_raw = Renderer::CreateRaw(pWindow, index, flags);

    return Renderer::SPtr(
        p_raw,
        [](SDL_Renderer *pRenderer){
            Renderer::SafeDestroy(pRenderer);
        }
    );
}

Renderer::UPtr Renderer::CreateUnique(
    SDL_Window *pWindow,
    int         index,
    Uint32      flags) noexcept
{
    // CreateRaw assures that it'll be a successful call or abort.
    auto p_raw = Renderer::CreateRaw(pWindow, index, flags);

    return Renderer::UPtr(
        p_raw,
        Renderer::SafeDestroy
    );
}

SDL_Renderer* Renderer::CreateRaw(
    SDL_Window *pWindow,
    int         index,
    Uint32      flags) noexcept
{
    COREASSERT_ASSERT(pWindow != nullptr, "pWindow can't be null");

    auto p_Renderer = SDL_CreateRenderer(pWindow, index, flags);
    COREASSERT_ASSERT(p_Renderer, "Failed to create Renderer - %s", Error::Last());

    return p_Renderer;
}