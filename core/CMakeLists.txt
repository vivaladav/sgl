project(libCore LANGUAGES CXX)

# SDL 2
find_package(SDL2 REQUIRED)

add_library(
    core
    include/sgl/core/Application.h
    include/sgl/core/Point.h
    include/sgl/core/Rect.h
    include/sgl/core/Size.h
    include/sgl/core/event/ApplicationEvent.h
    include/sgl/core/event/ApplicationEventListener.h
    include/sgl/core/event/Event.h
    include/sgl/core/event/KeyboardEvent.h
    include/sgl/core/event/KeyboardEventListener.h
    include/sgl/core/event/MouseButtonEvent.h
    include/sgl/core/event/MouseEvent.h
    include/sgl/core/event/MouseEventListener.h
    include/sgl/core/event/MouseMotionEvent.h
    src/Application.cpp
    src/event/ApplicationEventListener.cpp
    src/event/Event.cpp
    src/event/EventDispatcher.h
    src/event/EventDispatcher.cpp
    src/event/KeyboardEvent.cpp
    src/event/KeyboardEventListener.cpp
    src/event/MouseButtonEvent.cpp
    src/event/MouseEvent.cpp
    src/event/MouseEventListener.cpp
    src/event/MouseMotionEvent.cpp
)

target_include_directories(
    core
    PUBLIC include
    PRIVATE src
)

target_link_libraries(
    core
    PRIVATE SDL2
)
