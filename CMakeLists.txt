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
set(PROJECT_NAME acow_sdl_goodies)
project(${PROJECT_NAME})


##------------------------------------------------------------------------------
## Sources.
include_directories(acow)

add_library(${PROJECT_NAME}
    acow/src/SDL.cpp
    acow/src/IMG.cpp
    acow/src/TTF.cpp

    acow/src/Error.cpp

    acow/src/Window.cpp
    acow/src/Renderer.cpp

    acow/src/Input/SimpleInput.cpp
)


##------------------------------------------------------------------------------
## Modules
##   Find packages scripts was taken from:
##     https://github.com/tcbrindle/sdl2-cmake-scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_find")


##------------------------------------------------------------------------------
## SDL
find_package(SDL2       REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf   REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR}       )
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_TTF_INCLUDE_DIRS}  )


##------------------------------------------------------------------------------
## Include directories.
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


##------------------------------------------------------------------------------
## Dependencies.
## SDL
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${SDL2_LIBRARY}        )
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${SDL2_TTF_LIBRARIES}  )
## AmazingCow Libs
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC acow_c_goodies   )
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC acow_cpp_goodies )
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC acow_math_goodies)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC CoreAssert       )
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC CoreString       )
