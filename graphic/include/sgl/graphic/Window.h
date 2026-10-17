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

    VideoMode GetVideoMode() const;
    void SetVideoMode(VideoMode vm);

    int GetNumDisplays() const;
    int GetNumDisplayModes(int display) const;
    DisplayMode GetCurrentDisplayMode();
    DisplayMode GetDisplayMode(int display, int index) const;
    bool SetDisplayMode(int display, int index);
    int GetCurrentDisplayIndex() const;
    int GetCurrentDisplayModeIndex() const;

    bool IsMouseGrabbed() const;
    void GrabMouse(bool enabled);

    void AddWindowListener(WindowEventListener * el);
    void RemoveWindowListener(WindowEventListener * el);
    void HandleEvent(const union SDL_Event & event) override;

#ifdef DEBUG
    void PrintWindowFlags() const;
    void PrintDisplayMode() const;
    void PrintVideoSize() const;
#endif

private:
    Window(const char * title, int w, int h, core::Application * app);
    ~Window();

    void UpdateDisplayModes();
    void UpdateDisplayModeIndex();

private:
    static Window * mInstance;
    void * mContextGL = nullptr;

    std::vector<WindowEventListener *> mWindowListeners;

    std::vector<std::vector<DisplayMode>> mDisplayModes;
    int mNumDisplays = 0;
    int mDisplayModeIndex = -1;

    int mW = 0;
    int mH = 0;

    VideoMode mVideoMode;

    SDL_Window * mSysWin = nullptr;
    unsigned int mSysWinId = 0;

    // Renderer needs to access the low level window
    friend class Renderer;
};

inline Window * Window::Instance() { return mInstance; }

inline int Window::GetWidth() const { return mW; }
inline int Window::GetHeight() const { return mH; }

inline Window::VideoMode Window::GetVideoMode() const { return mVideoMode; }

inline int Window::GetNumDisplays() const { return mDisplayModes.size(); }
inline int Window::GetNumDisplayModes(int display) const
{
    if(display < mDisplayModes.size())
        return mDisplayModes[display].size();
    else
        return 0;
}

inline int Window::GetCurrentDisplayModeIndex() const { return mDisplayModeIndex; }

} // namespace graphic
} // namespace sgl
