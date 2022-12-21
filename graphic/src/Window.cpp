#include "sgl/graphic/Window.h"

#include <SDL2/SDL.h>

#include <iostream>

namespace sgl
{
namespace graphic
{

Window * Window::mInstance = nullptr;

Window * Window::Create(const char * title, int w, int h)
{
    if(!mInstance)
        mInstance = new Window(title, w, h);

    return mInstance;
}

void Window::Destroy()
{
    delete mInstance;
    mInstance = nullptr;
}

void Window::SetSize(int w, int h)
{
    mW = w;
    mH = h;

    SDL_SetWindowSize(mSysWin, w, h);
}

void Window::SetFullscreen(bool f)
{
    if(mFullscreen == f)
        return ;

    mFullscreen = f;

    const unsigned int flag = mFullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    SDL_SetWindowFullscreen(mSysWin, flag);
}

DisplayMode Window::GetCurrentDisplayMode()
{
    DisplayMode mode;

    if(nullptr == mSysWin)
        return mode;

    SDL_DisplayMode m;
    const int res = SDL_GetWindowDisplayMode(mSysWin, &m);

    if(0 == res)
    {
        mode.width = m.w;
        mode.height = m.h;
        mode.refresh = m.refresh_rate;
    }

    return mode;
}

DisplayMode Window::GetDisplayMode(unsigned int display, unsigned int index) const
{
    if(display < mDisplayModes.size() && index < mDisplayModes[display].size())
        return mDisplayModes[display][index];
    else
        return {};
}

bool Window::SetDisplayMode(unsigned int display, unsigned int index, bool updateWindowSize)
{
    SDL_DisplayMode mode;

    int res = SDL_GetDisplayMode(display, index, &mode);

    if(res != 0)
    {
        std::cout << "ERROR - Window::SetDisplayMode - getting display mode: " << SDL_GetError() << std::endl;
        return false;
    }

    res = SDL_SetWindowDisplayMode(mSysWin, &mode);

    if(res != 0)
    {
        std::cout << "ERROR - Window::SetDisplayMode - setting display mode: " << SDL_GetError() << std::endl;
        return false;
    }

    std::cout << "Window::SetDisplayMode - set display " << mode.w << "x" << mode.h
              << " @ " << mode.refresh_rate << std::endl;

    if(updateWindowSize)
        SetSize(mode.w, mode.h);

    return true;
}

Window::Window(const char * title, int w, int h)
    : mW(w)
    , mH(h)
{
    UpdateDisplayModes();

    // requested default size
    if(0 == w || 0 == h)
    {
        const DisplayMode dm = GetDisplayMode(0, 0);
        mW = dm.width;
        mH = dm.height;
    }

    const int posX = SDL_WINDOWPOS_CENTERED;
    const int posY = SDL_WINDOWPOS_CENTERED;
    const int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS;

    mSysWin = SDL_CreateWindow(title, posX, posY, mW, mH, flags);
}

Window::~Window()
{
    SDL_DestroyWindow(mSysWin);
}

void Window::UpdateDisplayModes()
{
    mNumDisplays = SDL_GetNumVideoDisplays();

    mDisplayModes.resize(mNumDisplays);

    for(int d = 0; d < mNumDisplays; ++d)
    {
        const int numModes = SDL_GetNumDisplayModes(d);

        for(int m = 0; m < numModes; ++m)
        {
            SDL_DisplayMode dm;

            SDL_GetDisplayMode(d, m, &dm);

            mDisplayModes[d].emplace_back(d, dm.w, dm.h, dm.refresh_rate);
        }
    }
}

} // namespace graphic
} // namespace sgl
