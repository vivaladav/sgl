project(libUtilities LANGUAGES CXX)

# SDL 2
find_package(SDL2 REQUIRED)

add_library(
    utilities
    include/sgl/utilities/IFilesystem.h
    include/sgl/utilities/ISystem.h
    include/sgl/utilities/Filesystem.h
    include/sgl/utilities/FilesystemBase.h
    include/sgl/utilities/LoadedDie.h
    include/sgl/utilities/State.h
    include/sgl/utilities/StateManager.h
    include/sgl/utilities/System.h
    $<$<PLATFORM_ID:Linux>:include/sgl/utilities/linux/Filesystem.h>
    $<$<PLATFORM_ID:Linux>:include/sgl/utilities/linux/System.h>
    $<$<PLATFORM_ID:Windows>:include/sgl/utilities/windows/Filesystem.h>
    $<$<PLATFORM_ID:Windows>:include/sgl/utilities/windows/System.h>
    include/sgl/utilities/UniformDistribution.h
    src/FilesystemBase.cpp
    src/LoadedDie.cpp
    src/State.cpp
    src/StateManager.cpp
    $<$<PLATFORM_ID:Linux>:src/linux/Filesystem.cpp>
    $<$<PLATFORM_ID:Linux>:src/linux/System.cpp>
    $<$<PLATFORM_ID:Windows>:src/windows/Filesystem.cpp>
    $<$<PLATFORM_ID:Windows>:src/windows/System.cpp>
    src/UniformDistribution.cpp
)

target_include_directories(
    utilities
    PUBLIC include
)
