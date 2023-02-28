#pragma once

#include "sgl/core/event/WindowEventHandler.h"

#include <vector>

struct SDL_Window;

namespace sgl
{

namespace core { class Application; }

namespace graphic
{

class Renderer;
class WindowEventListener;

struct DisplayMode
{
    DisplayMode() {};
    DisplayMode(int d, int w, int h, int r) : display(d), width(w), height(h), refresh(r) {}

    int display = 0;
    int width = 0;
    int height = 0;
    int refresh = 0;
};

class Window : public core::WindowEventHandler
{
public:
    enum VideoMode : int
    {
        VM_BORDERLESS = 0,
        VM_FULLSCREEN,
        VM_WINDOW
    };

public:
    static Window * Create(const char * title, int w, int h, core::Application * app);
    static Window * Instance();
    static void Destroy();

    int GetWidth() const;
    int GetHeight() const;
    void SetSize(int w, int h);

    bool IsFullscreen() const;
    void SetFullscreen(bool f);
    void SwitchFullscreen();

    VideoMode GetVideoMode() const;
    void SetVideoMode(VideoMode vm);

    int GetNumDisplays() const;
    int GetNumDisplayModes(unsigned int display) const;
    DisplayMode GetCurrentDisplayMode();
    DisplayMode GetDisplayMode(unsigned int display, unsigned int index) const;
    bool SetDisplayMode(unsigned int display, unsigned int index, bool updateWindowSize = true);

    void AddWindowListener(WindowEventListener * el);
    void RemoveWindowListener(WindowEventListener * el);
    void HandleEvent(const union SDL_Event & event) override;

private:
    Window(const char * title, int w, int h, core::Application * app);
    ~Window();

    void UpdateDisplayModes();

private:
    static Window * mInstance;
    void * mContextGL = nullptr;

    std::vector<WindowEventListener *> mWindowListeners;

    std::vector<std::vector<DisplayMode>> mDisplayModes;
    int mNumDisplays = 0;

    int mW = 0;
    int mH = 0;

    VideoMode mVideoMode;

    SDL_Window * mSysWin = nullptr;
    unsigned int mSysWinId = 0;


    bool mFullscreen = false;

    // Renderer needs to access the low level window
    friend class Renderer;
};

inline Window * Window::Instance() { return mInstance; }

inline bool Window::IsFullscreen() const { return mFullscreen; }
inline void Window::SwitchFullscreen()
{
    SetFullscreen(!mFullscreen);
}

inline int Window::GetWidth() const { return mW; }
inline int Window::GetHeight() const { return mH; }

inline Window::VideoMode Window::GetVideoMode() const { return mVideoMode; }

inline int Window::GetNumDisplays() const { return mDisplayModes.size(); }
inline int Window::GetNumDisplayModes(unsigned int display) const
{
    if(display < mDisplayModes.size())
        return mDisplayModes[display].size();
    else
        return 0;
}

} // namespace graphic
} // namespace sgl
