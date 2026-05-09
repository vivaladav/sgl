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

    // upate the window size if not in FULLSCREEN mode
    if(mVideoMode == VM_WINDOW)
        SDL_SetWindowSize(mSysWin, w, h);
}

void Window::SetVideoMode(VideoMode vm)
{
#ifdef DEBUG
    std::cout << "Window::SetVideoMode - CURRENT video mode: " << mVideoMode
              << " NEW video mode: " << vm << std::endl;
#endif

    if(vm == mVideoMode)
        return ;

    mVideoMode = vm;

    const unsigned int flags[] =
    {
        SDL_WINDOW_FULLSCREEN_DESKTOP,
        SDL_WINDOW_FULLSCREEN,
        0
    };
    const unsigned int flag = flags[vm];

    SDL_SetWindowFullscreen(mSysWin, flag);

#ifdef DEBUG
    PrintDisplayMode();
    PrintVideoSize();
    PrintWindowFlags();
    std::cout << "----------------------------------------\n" << std::endl;
#endif
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

bool Window::SetDisplayMode(unsigned int display, unsigned int index)
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

#ifdef DEBUG
    std::cout << "Window::SetDisplayMode - SET DISPLAY " << mode.w << "x" << mode.h
              << " @ " << mode.refresh_rate << "Hz." << std::endl;
    std::cout <<  std::endl;
#endif

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

#ifdef DEBUG
void Window::PrintWindowFlags() const
{
    if(mSysWin == nullptr)
        return ;

    const unsigned int wf = SDL_GetWindowFlags(mSysWin);

    std::cout << "Window::PrintWindowFlags - WINDOW FLAGS:"
              << ((SDL_WINDOW_FULLSCREEN & wf) ? " FULLSCREEN |" : "")
              << ((SDL_WINDOW_OPENGL & wf) ? " OPENGL |" : "")
              << ((SDL_WINDOW_SHOWN & wf) ? " SHOWN |" : "")
              << ((SDL_WINDOW_HIDDEN & wf) ? " HIDDEN |" : "")
              << ((SDL_WINDOW_BORDERLESS & wf) ? " BORDERLESS |" : "")
              << ((SDL_WINDOW_RESIZABLE & wf) ? " RESIZABLE |" : "")
              << ((SDL_WINDOW_MINIMIZED & wf) ? " MINIMIZED |" : "")
              << ((SDL_WINDOW_MAXIMIZED & wf) ? " MAXIMIZED |" : "")
              << ((SDL_WINDOW_MOUSE_GRABBED  & wf) ? " MOUSE GRABBED |" : "")
              << ((SDL_WINDOW_INPUT_FOCUS  & wf) ? " INPUT FOREIGN |" : "")
              << ((SDL_WINDOW_ALLOW_HIGHDPI & wf) ? " ALLOW HIGHDPI |" : "")
              << ((SDL_WINDOW_MOUSE_CAPTURE & wf) ? " MOUSE CAPTURE |" : "")
              << ((SDL_WINDOW_ALWAYS_ON_TOP & wf) ? " ALWAYS ON TOP |" : "")
              << ((SDL_WINDOW_SKIP_TASKBAR & wf) ? " SKIP TASKBAR |" : "")
              << ((SDL_WINDOW_UTILITY & wf) ? " UTILITY |" : "")
              << ((SDL_WINDOW_TOOLTIP & wf) ? " TOOLTIP |" : "")
              << ((SDL_WINDOW_POPUP_MENU & wf) ? " POPUP MENU |" : "")
              << ((SDL_WINDOW_KEYBOARD_GRABBED & wf) ? " KEYBOARD GRABBED |" : "")
              << ((SDL_WINDOW_VULKAN & wf) ? " VULKAN |" : "")
              << ((SDL_WINDOW_METAL & wf) ? " METAL |" : "")
              << std::endl;
}

void Window::PrintDisplayMode() const
{
    if(mSysWin == nullptr)
        return ;

    SDL_DisplayMode m;
    SDL_GetWindowDisplayMode(mSysWin, &m);

    std::cout << "Window::PrintDisplayMode - display mode: " << m.w << "x" << m.h
              << " @ " << m.refresh_rate << " Hz." <<  std::endl;
}

void Window::PrintVideoSize() const
{
    if(mSysWin == nullptr)
        return ;

    int winW = 0;
    int winH = 0;
    SDL_GetWindowSize(mSysWin, &winW, &winH);
    std::cout << "Window::PrintVideoSize - Window size: " << winW << "x" << winH << std::endl;

    SDL_GL_GetDrawableSize(mSysWin, &winW, &winH);
    std::cout << "Window::PrintVideoSize - Drawable size: " << winW << "x" << winH << std::endl;
}

#endif

Window::Window(const char * title, int w, int h, core::Application * app)
    : mW(w)
    , mH(h)
    , mVideoMode(VM_BORDERLESS)
{
    UpdateDisplayModes();

    // requested desktop size
    if(0 == w || 0 == h)
    {
        SDL_DisplayMode dm;
        SDL_GetDesktopDisplayMode(0, &dm);

        mW = dm.w;
        mH = dm.h;
    }

    const int posX = SDL_WINDOWPOS_CENTERED;
    const int posY = SDL_WINDOWPOS_CENTERED;
    const int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_FULLSCREEN_DESKTOP;

    mSysWin = SDL_CreateWindow(title, posX, posY, mW, mH, flags);

    mSysWinId = SDL_GetWindowID(mSysWin);
    mContextGL = SDL_GL_CreateContext(mSysWin);

    app->SetWindowEventHandler(this);

#ifdef DEBUG
    std::cout << "---------------- Window ----------------" << std::endl;
    PrintDisplayMode();
    PrintVideoSize();
    PrintWindowFlags();
    std::cout << "----------------------------------------\n" << std::endl;
#endif
}

Window::~Window()
{
    SDL_GL_DeleteContext(mContextGL);
    SDL_DestroyWindow(mSysWin);
}

void Window::UpdateDisplayModes()
{
    mNumDisplays = SDL_GetNumVideoDisplays();

    mDisplayModes.clear();
    mDisplayModes.resize(mNumDisplays);

    for(int d = 0; d < mNumDisplays; ++d)
    {
        const int numModes = SDL_GetNumDisplayModes(d);
        mDisplayModes[d].reserve(numModes + 1);

        for(int m = 0; m < numModes; ++m)
        {
            SDL_DisplayMode dm;
            SDL_GetDisplayMode(d, m, &dm);

            mDisplayModes[d].emplace_back(d, dm.w, dm.h, dm.refresh_rate);
        }

        // check if desktop display is present
        // NOTE this is done to prevent missing modes in Windows when scaling is enabled
        SDL_DisplayMode ddm;
        SDL_GetDesktopDisplayMode(d, &ddm);

        bool found = false;

        for(const DisplayMode & mode : mDisplayModes[d])
        {
            if(mode.width == ddm.w && mode.height == ddm.h && mode.refresh == ddm.refresh_rate)
            {
                found = true;
                break;
            }
        }

        // add desktop display mode if not found
        if(!found)
            mDisplayModes[d].emplace_back(d, ddm.w, ddm.h, ddm.refresh_rate);
    }
}

} // namespace graphic
} // namespace sgl
