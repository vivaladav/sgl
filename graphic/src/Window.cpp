#include "sgl/graphic/Window.h"

#include "sgl/core/Application.h"
#include "sgl/graphic/event/WindowEvent.h"
#include "sgl/graphic/event/WindowEventListener.h"

#ifdef LINUX
    #include <SDL2/SDL.h>
#else
    #include <SDL.h>
#endif

#include <algorithm>
#include <iostream>

namespace sgl
{
namespace graphic
{

Window * Window::mInstance = nullptr;

Window * Window::Create(const char * title, int w, int h, core::Application * app)
{
    if(!mInstance)
        mInstance = new Window(title, w, h, app);

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

void Window::AddWindowListener(WindowEventListener * el)
{
    // do not add NULL
    if(!el)
        return ;

    auto it = std::find(mWindowListeners.begin(), mWindowListeners.end(), el);

    // listener not found -> add it
    if(mWindowListeners.end() == it)
    {
        el->mWindow = this;
        mWindowListeners.emplace_back(el);
    }
}

void Window::RemoveWindowListener(WindowEventListener * el)
{
    auto it = std::find(mWindowListeners.begin(), mWindowListeners.end(), el);

    // listener found -> remove it
    if(it != mWindowListeners.end())
        mWindowListeners.erase(it);
}

void Window::HandleEvent(const union SDL_Event & event)
{
    // event for another window -> exit
    if (event.window.windowID != mSysWinId)
        return ;

    switch(event.window.event)
    {
        // window minimized to task bar
        case SDL_WINDOWEVENT_MINIMIZED:
        {
            WindowEvent e;

            for(WindowEventListener * el : mWindowListeners)
            {
                el->OnWindowMinimized(e);

                // stop propagation if event is consumed
                if(e.IsConsumed())
                    break;
            }
        }
        break;

        // window maximized
        case SDL_WINDOWEVENT_MAXIMIZED:
        {
            WindowEvent e;

            for(WindowEventListener * el : mWindowListeners)
            {
                el->OnWindowMaximized(e);

                // stop propagation if event is consumed
                if(e.IsConsumed())
                    break;
            }
        }
        break;

        // window comes up on screen, after opening it from taskbar or ALT-TAB
        case SDL_WINDOWEVENT_EXPOSED:
        {
            WindowEvent e;

            for(WindowEventListener * el : mWindowListeners)
            {
                el->OnWindowExposed(e);

                // stop propagation if event is consumed
                if(e.IsConsumed())
                    break;
            }
        }
        break;

        // window minimized
        case SDL_WINDOWEVENT_HIDDEN:
        {
            WindowEvent e;

            for(WindowEventListener * el : mWindowListeners)
            {
                el->OnWindowHidden(e);

                // stop propagation if event is consumed
                if(e.IsConsumed())
                    break;
            }
        }
        break;

        // mouse enters the window
        case SDL_WINDOWEVENT_ENTER:
        {
            WindowEvent e;

            for(WindowEventListener * el : mWindowListeners)
            {
                el->OnWindowMouseEntered(e);

                // stop propagation if event is consumed
                if(e.IsConsumed())
                    break;
            }
        }
        break;

        // mouse leaves the window
        case SDL_WINDOWEVENT_LEAVE:
        {
            WindowEvent e;

            for(WindowEventListener * el : mWindowListeners)
            {
                el->OnWindowMouseLeft(e);

                // stop propagation if event is consumed
                if(e.IsConsumed())
                    break;
            }
        }
        break;

        // keyboard focus regained, after opened from taskabr or with ALT-TAB
        case SDL_WINDOWEVENT_FOCUS_GAINED:
        {
            WindowEvent e;

            for(WindowEventListener * el : mWindowListeners)
            {
                el->OnWindowKeyboardFocusGained(e);

                // stop propagation if event is consumed
                if(e.IsConsumed())
                    break;
            }
        }
        break;

        // keyboard focus lost because minimized or clicked on another window
        case SDL_WINDOWEVENT_FOCUS_LOST:
        {
            WindowEvent e;

            for(WindowEventListener * el : mWindowListeners)
            {
                el->OnWindowKeyboardFocusLost(e);

                // stop propagation if event is consumed
                if(e.IsConsumed())
                    break;
            }
        }
        break;

        default:
        break;
    }
}

Window::Window(const char * title, int w, int h, core::Application * app)
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

    mSysWinId = SDL_GetWindowID(mSysWin);

    app->SetWindowEventHandler(this);
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
