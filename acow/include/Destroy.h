#pragma once


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
