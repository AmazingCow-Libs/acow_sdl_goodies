//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : IMG.cpp                                                       //
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
#include "../include/IMG.h"
// AmazingCow Libs
#include "CoreAssert/CoreAssert.h"
// acow_sdl_goodies
#include "../include/Error.h"

// Usings
using namespace acow;
using namespace sdl;


//----------------------------------------------------------------------------//
// Lifecycle Functions                                                        //
//----------------------------------------------------------------------------//
void img::Init(int flags) noexcept
{
    COREASSERT_ASSERT(
        IMG_Init(flags) == flags,
        "Failed to initialize SDL_image - %s",
        Error::Last()
    );
}

void img::Quit() noexcept
{
    IMG_Quit();
}
