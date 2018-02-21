##~---------------------------------------------------------------------------##
##                     _______  _______  _______  _     _                     ##
##                    |   _   ||       ||       || | _ | |                    ##
##                    |  |_|  ||       ||   _   || || || |                    ##
##                    |       ||       ||  | |  ||       |                    ##
##                    |       ||      _||  |_|  ||       |                    ##
##                    |   _   ||     |_ |       ||   _   |                    ##
##                    |__| |__||_______||_______||__| |__|                    ##
##                             www.amazingcow.com                             ##
##  File      : CMakeLists.txt                                                ##
##  Project   : acow_sdl_goodies                                              ##
##  Date      : Feb 20, 2018                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : n2omatt <n2omatt@amazingcow.com>                              ##
##  Copyright : AmazingCow - 2018                                             ##
##                                                                            ##
##  Description :                                                             ##
##                                                                            ##
##---------------------------------------------------------------------------~##

cmake_minimum_required(VERSION 3.5)

##------------------------------------------------------------------------------
## Project Settings.
project(acow_sdl_goodies)


##------------------------------------------------------------------------------
## Sources.
add_library(acow_sdl_goodies
    acow/src/SDL.cpp
    acow/src/IMG.cpp
    acow/src/TTF.cpp

    acow/src/Error.cpp

    acow/src/Window.cpp
    acow/src/Renderer.cpp
)


##------------------------------------------------------------------------------
## Include directories.
target_include_directories(acow_sdl_goodies PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


##------------------------------------------------------------------------------
## Dependencies.
target_link_libraries(acow_sdl_goodies LINK_PUBLIC acow_cpp_goodies)
target_link_libraries(acow_sdl_goodies LINK_PUBLIC CoreAssert      )
target_link_libraries(acow_sdl_goodies LINK_PUBLIC CoreString      )