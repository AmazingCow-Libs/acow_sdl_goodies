//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Input.cpp                                                     //
//  Project   : Cooper                                                        //
//  Date      : Nov 17, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "include/Input/SimpleInput.h"
// std
#include <cstring> // memset(3), memcpy(3), memcmp(3)
// AmazingCow Libs
#include "CoreAssert/CoreAssert.h"

// Usings
using namespace acow;
using namespace sdl;


//----------------------------------------------------------------------------//
// Variables                                                                  //
//----------------------------------------------------------------------------//
namespace {
    // Housekeeping.
    bool m_initialized = false;

    // Keyboard.
    bool   m_hasKeyboardInput   = false;
    int    m_keyboardKeysCount  = 0;
    Uint8 *m_pPrevKeyboardState = nullptr; //This is handled by us.
    Uint8 *m_pCurrKeyboardState = nullptr; //This is handled by SDL - Weak Reference.

    // Mouse.
    bool             m_hasMouseInput     = false;
    acow::math::Vec2 m_prevMousePosition = acow::math::Vec2::Zero();
    acow::math::Vec2 m_currMousePosition = acow::math::Vec2::Zero();
    Uint32           m_prevMouseState    = 0;
    Uint32           m_currMouseState    = 0;
};


//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
acow_internal_function void
check_input_valid(u32 key)
{
    //--------------------------------------------------------------------------
    // Sanity Checks.
    COREASSERT_ASSERT(m_initialized, "Input isn't initialized.");

    COREASSERT_ASSERT(
        key != SimpleInput::Mouse_Input_Shift,
        "Mouse_Input_Shift is just for internal use."
    );

    COREASSERT_ASSERT(
        key != SimpleInput::Keyboard_Input_Shift,
        "Keyboard_Input_Shift is just for internal use."
    );
}


//----------------------------------------------------------------------------//
// Lifecycle Functions.                                                       //
//----------------------------------------------------------------------------//
void
SimpleInput::Init()
{
    COREASSERT_ASSERT(!m_initialized, "Input is already initialized.");

    //--------------------------------------------------------------------------
    // Query SDL about the current keyboard state.
    //   This will retrieve the number of keys of keyboard.
    //   Notice that this pointer is not owned by us, and we must not free it.
    m_pCurrKeyboardState = const_cast<Uint8*>(
        SDL_GetKeyboardState(&m_keyboardKeysCount)
    );

    //--------------------------------------------------------------------------
    // To compare the states we gonna need another array.
    //   So let's allocate it, but notice that this is actually owned by
    //   us, so we NEED free it on Shutdown.
    m_pPrevKeyboardState = new Uint8[m_keyboardKeysCount];
    memset(m_pPrevKeyboardState, 0, sizeof(Uint8) * m_keyboardKeysCount);

    //--------------------------------------------------------------------------
    // Query the current mouse state.
    int mouse_x, mouse_y;
    m_currMouseState = SDL_GetMouseState(
        &mouse_x,
        &mouse_y
    );
    m_currMousePosition.x = mouse_x;
    m_currMousePosition.y = mouse_y;

    //--------------------------------------------------------------------------
    // Complete initialization.
    m_initialized = true;
}

void
SimpleInput::Shutdown()
{
    COREASSERT_ASSERT(m_initialized, "Input isn't  initialized.");

    //--------------------------------------------------------------------------
    // Delete memory allocated by us.
    ACOW_SAFE_DELETE_ARR(m_pPrevKeyboardState);

    //--------------------------------------------------------------------------
    // Complete deinitialization.
    m_initialized = false;
}

bool
SimpleInput::IsInitialized() noexcept
{
    return m_initialized;
}

void
SimpleInput::Update()
{
    //--------------------------------------------------------------------------
    // Keyboard.
    m_pCurrKeyboardState = const_cast<Uint8*>(
        SDL_GetKeyboardState(&m_keyboardKeysCount)
    );

    m_hasKeyboardInput = memcmp(
        m_pCurrKeyboardState,
        m_pPrevKeyboardState,
        sizeof(Uint8) * m_keyboardKeysCount
    ) != 0;


    //--------------------------------------------------------------------------
    // Mouse.
    int mouse_x, mouse_y;
    m_currMouseState = SDL_GetMouseState(
        &mouse_x,
        &mouse_y
    );
    m_currMousePosition.x = mouse_x;
    m_currMousePosition.y = mouse_y;

    m_hasMouseInput = (
        m_currMouseState      != m_prevMouseState       ||
        m_currMousePosition.x != m_prevMousePosition.x  ||
        m_currMousePosition.y != m_prevMousePosition.y
    );
}

void
SimpleInput::PostUpdate()
{
    //--------------------------------------------------------------------------
    // Keyboard.
    m_hasKeyboardInput = false;
    memcpy(m_pPrevKeyboardState, m_pCurrKeyboardState, m_keyboardKeysCount);

    //--------------------------------------------------------------------------
    // Mouse.
    m_hasMouseInput  = false;
    m_prevMousePosition   = m_currMousePosition;
    m_prevMouseState = m_currMouseState;
}


//----------------------------------------------------------------------------//
// Keyboard Functions                                                         //
//----------------------------------------------------------------------------//
bool
SimpleInput::HasKeyboardInput()
{
    COREASSERT_ASSERT(m_initialized, "Input isn't initialized.");

    return m_hasKeyboardInput;
}

bool
SimpleInput::IsKeyDown(u32 rawKey)
{
    check_input_valid(rawKey);

    // Handling Mouse.
    if(rawKey < Keyboard_Input_Shift)
    {
        auto button = (rawKey - Mouse_Input_Shift);
        auto value  = m_currMouseState && SDL_BUTTON(button);

        return value;
    }

    // Handling Keyboard
    if(rawKey > Keyboard_Input_Shift)
    {
        auto key   = (rawKey - Keyboard_Input_Shift);
        auto value = m_pCurrKeyboardState[key];

        return value;
    }

    return false;
}

bool
SimpleInput::IsKeyPress(u32 rawKey)
{
    check_input_valid(rawKey);

    // Handling Mouse.
    if(rawKey < Keyboard_Input_Shift)
    {
        auto button = (rawKey - Mouse_Input_Shift);
        auto value  = !(m_prevMouseState & SDL_BUTTON(button)) &&
                       (m_currMouseState & SDL_BUTTON(button));

        return value;
    }

    // Handling Keyboard
    if(rawKey > Keyboard_Input_Shift)
    {
        auto key   = (rawKey - Keyboard_Input_Shift);
        auto value = !m_pPrevKeyboardState[key] &&
                      m_pCurrKeyboardState[key];

        return value;
    }

    return false;
}

bool
SimpleInput::IsKeyRelease(u32 rawKey)
{

     check_input_valid(rawKey);

    // Handling Mouse.
    if(rawKey < Keyboard_Input_Shift)
    {
        auto button = (rawKey - Mouse_Input_Shift);
        auto value  =  (m_prevMouseState & SDL_BUTTON(button)) &&
                      !(m_currMouseState & SDL_BUTTON(button));

        return value;
    }

    // Handling Keyboard
    if(rawKey > Keyboard_Input_Shift)
    {
        auto key   = (rawKey - Keyboard_Input_Shift);
        auto value =  m_pPrevKeyboardState[key] &&
                     !m_pCurrKeyboardState[key];

        return value;
    }

    return false;
}


//----------------------------------------------------------------------------//
// Mouse Functions                                                            //
//----------------------------------------------------------------------------//
bool
SimpleInput::HasMouseInput()
{
    COREASSERT_ASSERT(m_initialized, "Input isn't initialized.");
    return m_hasMouseInput;
}

const acow::math::Vec2&
SimpleInput::GetMousePosition()
{
    COREASSERT_ASSERT(m_initialized, "Input isn't initialized.");

    static auto s_mouse_pos = acow::math::Vec2(m_currMousePosition);

    s_mouse_pos.x = m_currMousePosition.x;
    s_mouse_pos.y = m_currMousePosition.y;


    return s_mouse_pos;
}
