//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Timer.h                                                       //
//  Project   : Cooper                                                        //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#pragma once

// AmazingCow Libs
#include "acow/cpp_goodies.h"
#include "acow/sdl_goodies.h"
#include "CoreAssert/CoreAssert.h"
// acow_sdl_goodies
#include "SDLGoodies_Utils.h"


NS_ACOW_SDL_GOODIES_BEGIN

class Timer
{
    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
     inline Timer() noexcept
        : m_startTime   (0)
        , m_frequency   (SDL_GetPerformanceFrequency()) // COWTODO(n2omatt): Should this be static?
        , m_deltaTime   (0)
        , m_totalTime   (0)
        , m_timeScale   (1)
        , m_initialized (false)
    {
        // Empty...
    }

    ~Timer() = default;


    //------------------------------------------------------------------------//
    // Control Functions                                                      //
    //------------------------------------------------------------------------//
public:
    inline void
    Reset() noexcept
    {
         m_startTime = SDL_GetPerformanceCounter();
        m_deltaTime = 0;
        m_totalTime = 0;

        m_initialized = true;
    }

    inline void
    Update() noexcept
    {
        COREASSERT_ASSERT(m_initialized, "Timer isn't initialized - Call Reset().");
        Restart();
    }

    inline float
    Restart() noexcept
    {
        auto current = SDL_GetPerformanceCounter();
        auto elapsed = current - m_startTime;
        m_startTime  = current;

        m_deltaTime  = float(elapsed) / float(m_frequency);
        m_totalTime += m_deltaTime;

        return m_deltaTime;
    }


    //------------------------------------------------------------------------//
    // Delta Time                                                             //
    //------------------------------------------------------------------------//
public:
    ACOW_CONSTEXPR_STRICT inline float
    GetDeltaTime() const noexcept
    {
        return m_deltaTime;
    }


    //------------------------------------------------------------------------//
    // Total Time                                                             //
    //------------------------------------------------------------------------//
public:
    ACOW_CONSTEXPR_STRICT inline float
    GetTotalTime() const noexcept
    {
        return m_totalTime;
    }


    //------------------------------------------------------------------------//
    // Time Scale                                                             //
    //------------------------------------------------------------------------//
public:
    // Setter.
    inline void
    SetTimeScale (float timeScale = 1.0f) noexcept
    {
        m_timeScale = timeScale;
    }

    // Getter.
    ACOW_CONSTEXPR_STRICT inline float
    GetTimeScale() const noexcept
    {
        return m_timeScale;
    }


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    f32 m_startTime;
    f32 m_frequency;

    f32 m_deltaTime;
    f32 m_totalTime;
    f32 m_timeScale;

    bool m_initialized;

}; // class Timer

NS_ACOW_SDL_GOODIES_END
