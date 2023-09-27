cmake_minimum_required(VERSION 3.24)
project(Renderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(SOURCE_FILES main.cpp Rect.hpp Rect3D.hpp Cube.hpp Renderer.hpp Object3D.hpp Util.hpp)
add_executable(Renderer ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Renderer system sfml-window sfml-graphics sfml-audio sfml-network)

