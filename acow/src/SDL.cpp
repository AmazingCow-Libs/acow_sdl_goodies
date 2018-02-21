//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : SDL.cpp                                                       //
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
#include "../include/SDL.h"
// AmazingCow Libs
#include "CoreAssert/CoreAssert.h"
// acow_sdl_goodies
#include "../include/Error.h"

// Usings
using namespace acow;


//----------------------------------------------------------------------------//
// Lifecycle Functions                                                        //
//----------------------------------------------------------------------------//
void sdl::Init(Uint32 flags) noexcept
{
    COREASSERT_ASSERT(
        SDL_Init(flags) == 0,
        "Failed to initialize SDL - %s",
        sdl::Error::Last()
    );
}

void sdl::Quit() noexcept
{
    SDL_Quit();
}
