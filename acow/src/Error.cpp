//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Error.cpp                                                     //
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
#include "../include/Error.h"
// Amazing Cow Libs
#include "CoreString/CoreString.h"

// Usings
using namespace acow;
using namespace sdl;

std::string gErrorMsg;


//----------------------------------------------------------------------------//
// Functions                                                                  //
//----------------------------------------------------------------------------//
const char * const Error::Last() noexcept
{
    auto p_sdl_error = SDL_GetError();

    //--------------------------------------------------------------------------
    // No error ocurred - Return the empty string that SDL returned itself.
    if(strlen(p_sdl_error) == 0)
        return p_sdl_error;

    //--------------------------------------------------------------------------
    // Error ocurred - Prepare the message.
    gErrorMsg = CoreString::Format("SDLError: %s", p_sdl_error);
    return gErrorMsg.c_str();
}
