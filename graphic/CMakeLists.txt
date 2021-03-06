project(libGraphic LANGUAGES CXX)

# SDL 2
find_package(SDL2 REQUIRED)

add_library(
    graphic
    include/sgl/graphic/Camera.h
    include/sgl/graphic/DummyRenderable.h
    include/sgl/graphic/Font.h
    include/sgl/graphic/FontManager.h
    include/sgl/graphic/GraphicConstants.h
    include/sgl/graphic/Image.h
    include/sgl/graphic/Particle.h
    include/sgl/graphic/ParticleData.h
    include/sgl/graphic/ParticlesManager.h
    include/sgl/graphic/ParticlesUpdater.h
    include/sgl/graphic/Renderable.h
    include/sgl/graphic/Renderer.h
    include/sgl/graphic/Text.h
    include/sgl/graphic/TexturedRenderable.h
    include/sgl/graphic/Texture.h
    include/sgl/graphic/TextureData.h
    include/sgl/graphic/TextureManager.h
    include/sgl/graphic/Window.h
    src/Camera.cpp
    src/DummyRenderable.cpp
    src/Font.cpp
    src/FontManager.cpp
    src/Image.cpp
    src/ParticlesManager.cpp
    src/ParticlesUpdater.cpp
    src/Renderable.cpp
    src/Renderer.cpp
    src/Text.cpp
    src/Texture.cpp
    src/TextureData.cpp
    src/TexturedRenderable.cpp
    src/TextureManager.cpp
    src/Window.cpp
)

target_include_directories(
    graphic
    PUBLIC include
)

target_link_libraries(
    graphic
    PRIVATE SDL2
    PRIVATE SDL2_image
    PRIVATE SDL2_ttf
    PUBLIC core
)
