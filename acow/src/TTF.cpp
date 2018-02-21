//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : TTF.cpp                                                       //
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
#include "../include/TTF.h"
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
void ttf::Init() noexcept
{
    COREASSERT_ASSERT(
        TTF_Init() == 0,
        "Failed to initialize SDL_ttf - %s",
        Error::Last()
    );
}

void ttf::Quit() noexcept
{
    TTF_Quit();
}
