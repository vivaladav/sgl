project(libUtilities LANGUAGES CXX)

# SDL 2
find_package(SDL2 REQUIRED)

add_library(
    utilities
    include/sgl/utilities/ISystem.h
    include/sgl/utilities/LoadedDie.h
    include/sgl/utilities/State.h
    include/sgl/utilities/StateManager.h
    include/sgl/utilities/System.h
    $<$<PLATFORM_ID:Linux>:include/sgl/utilities/linux/System.h>
    $<$<PLATFORM_ID:Windows>:include/sgl/utilities/windows/System.h>
    include/sgl/utilities/UniformDistribution.h
    src/LoadedDie.cpp
    src/State.cpp
    src/StateManager.cpp
    $<$<PLATFORM_ID:Linux>:src/linux/System.cpp>
    $<$<PLATFORM_ID:Windows>:src/windows/System.cpp>
    src/UniformDistribution.cpp
)

target_include_directories(
    utilities
    PUBLIC include
)
