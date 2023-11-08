cmake_minimum_required(VERSION 3.26)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
FIND_PACKAGE(SDL_IMAGE REQUIRED)
INCLUDE_DIRECTORIES( ${SDL2_IMAGE_INCLUDE_DIR})


add_executable(untitled1 main.cpp Engine.cpp Engine.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY}${SDL2_IMAGE_LIBRARY} -lmingw32 -mwindows)
add_definitions(-DSDL_MAIN_HANDLED)
