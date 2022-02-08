project(libAI LANGUAGES CXX)

add_library(
    ai
    include/sgl/ai/IPathMap.h
    include/sgl/ai/Pathfinder.h
    src/Pathfinder.cpp
    src/PathNode.h
)

target_include_directories(
    ai
    PUBLIC include
)
