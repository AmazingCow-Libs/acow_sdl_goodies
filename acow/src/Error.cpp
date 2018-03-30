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


//----------------------------------------------------------------------------//
// Functions                                                                  //
//----------------------------------------------------------------------------//
const char * const Error::Last() noexcept
{
    auto p_sdl_error = SDL_GetError();

    //--------------------------------------------------------------------------
    // No error occurred - Return the empty string that SDL returned itself.
    if(strlen(p_sdl_error) == 0)
        return p_sdl_error;

    //--------------------------------------------------------------------------
    // Error occurred - Prepare the message.
    acow_local_persist char error_buffer[2048] = {};
    sprintf(error_buffer, "SDLError: %s", p_sdl_error);

    return error_buffer;
}
