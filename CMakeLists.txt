cmake_minimum_required(VERSION 3.5.1)

project(sgl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ai)
add_subdirectory(core)
add_subdirectory(graphic)
add_subdirectory(media)
add_subdirectory(sgui)
add_subdirectory(utilities)
