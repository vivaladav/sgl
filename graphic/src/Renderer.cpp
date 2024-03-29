#include "sgl/graphic/Renderer.h"

#include "sgl/graphic/Camera.h"
#include "sgl/graphic/TextureManager.h"
#include "sgl/graphic/Window.h"

#ifdef LINUX
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
#else
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#endif

#include <cassert>
#include <iostream>

namespace sgl
{
namespace graphic
{

Renderer * Renderer::mInstance = nullptr;

Renderer * Renderer::Create(Window * win, bool vsync)
{
    assert(win);

    if(!mInstance)
    {
        mInstance = new Renderer(win, vsync);

        // create dummy and default camera for all Renderables
        Camera::CreateDefaultCamera();
        Camera::CreateDummyCamera();
    }

    return mInstance;
}

void Renderer::Destroy()
{
    delete mInstance;
    mInstance = nullptr;

    Camera::DestroyDefaultCamera();
    Camera::DestroyDummyCamera();
}

Renderer::Renderer(Window * win, bool vsync)
{
    mW = win->GetWidth();
    mH = win->GetHeight();

    unsigned int flags = vsync ? SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                               : SDL_RENDERER_ACCELERATED;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    mSysRenderer = SDL_CreateRenderer(win->mSysWin, -1, flags);

    // -- init SDL_image --
    atexit(IMG_Quit);

    const int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;

    if(IMG_Init(imgFlags) != imgFlags)
    {
        std::cerr << "SDL_image init failed: " << IMG_GetError() << std::endl;
        exit(-1);
    }

    // -- init SDL_ttf --
    atexit(TTF_Quit);

    if(TTF_Init() == -1)
    {
        std::cerr << "SDL_ttf init failed: " << TTF_GetError() << std::endl;
        exit(-1);
    }

    // -- init TextureManager --
    // TODO decide if keeping this here or move it to a ModuleGraphic
    TextureManager::Create();
}

Renderer::~Renderer()
{
    TextureManager::Destroy();

    SDL_DestroyRenderer(mSysRenderer);
}

bool Renderer::SetLogicalSize(int w, int h)
{
    if(SDL_RenderSetLogicalSize(mSysRenderer, w, h) != 0)
    {
        std::cerr << "Renderer::SetLogicalSize - " << SDL_GetError() << std::endl;
        return false;
    }
    else
    {
        mW = w;
        mH = h;

        return true;
    }
}

void Renderer::SetRenderColor(unsigned char r, unsigned char g,
                              unsigned char b, unsigned char a)
{
    SDL_SetRenderDrawColor(mSysRenderer, r, g, b, a);
}
void Renderer::Clear()
{
    SDL_RenderClear(mSysRenderer);
}

void Renderer::Clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    SDL_SetRenderDrawColor(mSysRenderer, r, g, b, a);
    SDL_RenderClear(mSysRenderer);
}

void Renderer::Finalize()
{
    SDL_RenderPresent(mSysRenderer);
}

void Renderer::SetClipping(int x0, int y0, int w, int h)
{
    const SDL_Rect rect = { x0, y0, w, h };

    SDL_RenderSetClipRect(mSysRenderer, &rect);
}

void Renderer::ClearClipping()
{
    SDL_RenderSetClipRect(mSysRenderer, nullptr);
}

} // namespace graphic
} // namespace sgl
