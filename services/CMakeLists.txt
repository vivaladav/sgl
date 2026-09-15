project(libServices LANGUAGES CXX)

add_compile_definitions($<$<BOOL:${STEAM_SDK}>:USE_STEAM=1>
                        )

set(STEAM_SDK_INCLUDE "${STEAM_SDK}/public/")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(STEAM_SDK_LIB "${STEAM_SDK}/redistributable_bin/linux64/libsteam_api.so")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(STEAM_SDK_LIB "${STEAM_SDK}/redistributable_bin/win64/steam_api64.lib")
endif()

add_library(
    services
    include/sgl/services/Steam.h
    src/Steam.cpp
)

target_link_libraries(
    services
    PUBLIC core
    PRIVATE $<$<BOOL:${STEAM_SDK}>:${STEAM_SDK_LIB}>
)
target_include_directories(
    services
    PUBLIC include
    PRIVATE
    PRIVATE $<$<BOOL:${STEAM_SDK}>:${STEAM_SDK_INCLUDE}>
)
