project(libMedia LANGUAGES CXX)

# SDL 2
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_library(
    media
    include/sgl/media/AudioManager.h
    include/sgl/media/AudioPlayer.h
    include/sgl/media/Music.h
    include/sgl/media/Sound.h
    src/AudioManager.cpp
    src/AudioPlayer.cpp
    src/Music.cpp
    src/Sound.cpp
)

target_include_directories(
    media
    PUBLIC include
)

target_link_libraries(
    media
    PRIVATE core
    PRIVATE SDL2::SDL2
    PRIVATE SDL2_mixer::SDL2_mixer
)
