#include "sgl/core/Application.h"

#include "TimerManager.h"
#include "event/EventDispatcher.h"

#ifdef LINUX
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_mixer.h>
    #include <SDL2/SDL_ttf.h>
#else
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_mixer.h>
    #include <SDL_ttf.h>
#endif

#include <cmath>
#include <chrono>
#include <iostream>

namespace sgl
{
namespace core
{

Application::Application(int argc, char * argv[])
    : mArgc(argc)
    , mEventDispatcher(new EventDispatcher)
{
    // -- STORE ARGUMENTS --
    for(int i = 0; i < argc; ++i)
        mArgv.emplace_back(argv[i]);

    // -- INIT SDL 2 --
    atexit(SDL_Quit);

    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        std::cerr << "SDL init failed: " << SDL_GetError() << std::endl;
        exit(-1);
    }

    mTimerManager = TimerManager::Create();
}

Application::~Application()
{
    delete mEventDispatcher;

    TimerManager::Destroy();
}

// ===== libraries =====
void Application::PrintBuildLibs() const
{
    SDL_version sdlVer;
    SDL_version sdlImgVer;
    SDL_version sdlMixVer;
    SDL_version sdlTtfVer;

    SDL_VERSION(&sdlVer);
    SDL_IMAGE_VERSION(&sdlImgVer);
    SDL_MIXER_VERSION(&sdlMixVer);
    SDL_TTF_VERSION(&sdlTtfVer);

    std::cout << "====== BUILD LIBRARIES ======" << std::endl;
    std::cout << "SDL version: "
              << static_cast<int>(sdlVer.major) << "."
              << static_cast<int>(sdlVer.minor) << "."
              << static_cast<int>(sdlVer.patch) << std::endl;
    std::cout << "SDL_image version: "
              << static_cast<int>(sdlImgVer.major) << "."
              << static_cast<int>(sdlImgVer.minor) << "."
              << static_cast<int>(sdlImgVer.patch) << std::endl;
    std::cout << "SDL_mixer version: "
              << static_cast<int>(sdlMixVer.major) << "."
              << static_cast<int>(sdlMixVer.minor) << "."
              << static_cast<int>(sdlMixVer.patch) << std::endl;
    std::cout << "SDL_ttf version: "
              << static_cast<int>(sdlTtfVer.major) << "."
              << static_cast<int>(sdlTtfVer.minor) << "."
              << static_cast<int>(sdlTtfVer.patch) << std::endl;
    std::cout << "====== BUILD LIBRARIES ======\n" << std::endl;
}

void Application::PrintRuntimeLibs() const
{
    SDL_version sdlVer;
    SDL_GetVersion(&sdlVer);

    const SDL_version * sdlImgVer = IMG_Linked_Version();
    const SDL_version * sdlMixVer = Mix_Linked_Version();
    const SDL_version * sdlTtfVer = TTF_Linked_Version();

    std::cout << "====== RUNTIME LIBRARIES ======" << std::endl;
    std::cout << "SDL version: "
              << static_cast<int>(sdlVer.major) << "."
              << static_cast<int>(sdlVer.minor) << "."
              << static_cast<int>(sdlVer.patch) << std::endl;
    std::cout << "SDL_image version: "
              << static_cast<int>(sdlImgVer->major) << "."
              << static_cast<int>(sdlImgVer->minor) << "."
              << static_cast<int>(sdlImgVer->patch) << std::endl;
    std::cout << "SDL_mixer version: "
              << static_cast<int>(sdlMixVer->major) << "."
              << static_cast<int>(sdlMixVer->minor) << "."
              << static_cast<int>(sdlMixVer->patch) << std::endl;
    std::cout << "SDL_ttf version: "
              << static_cast<int>(sdlTtfVer->major) << "."
              << static_cast<int>(sdlTtfVer->minor) << "."
              << static_cast<int>(sdlTtfVer->patch) << std::endl;
    std::cout << "====== RUNTIME LIBRARIES ======\n" << std::endl;
}

// ===== command line arguments =====
void Application::ProcessArguments()
{
}

// ===== events =====
void Application::AddApplicationListener(ApplicationEventListener * listener)
{
    mEventDispatcher->AddApplicationListener(listener);
}

void Application::AddKeyboardListener(KeyboardEventListener * listener)
{
    mEventDispatcher->AddKeyboardListener(listener);
}

void Application::AddMouseListener(MouseEventListener * listener)
{
    mEventDispatcher->AddMouseListener(listener);
}

void Application::RemoveApplicationListener(ApplicationEventListener * listener)
{
    mEventDispatcher->RemoveApplicationListener(listener);
}

void Application::RemoveKeyboardListener(KeyboardEventListener * listener)
{
    mEventDispatcher->RemoveKeyboardListener(listener);
}

void Application::RemoveMouseListener(MouseEventListener * listener)
{
    mEventDispatcher->RemoveMouseListener(listener);
}

void Application::SetWindowEventHandler(WindowEventHandler * handler)
{
    mEventDispatcher->SetWindowEventHandler(handler);
}

// ===== execution =====
void Application::Run()
{
    mRunning = true;

    const float targetFrameTime = 1.f / 60.f;

    float delta = targetFrameTime;

    while(mRunning)
    {
        auto t0 = std::chrono::high_resolution_clock::now();

        mEventDispatcher->Update();

        mTimerManager->Update();

        Update(delta);

        auto t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> diff = t1 - t0;

        const float frameTime = diff.count();
        const float delayTime = targetFrameTime - frameTime;

        if(delayTime > 0.f)
        {
            SDL_Delay(static_cast<int>(roundf(delayTime * 1000.f)));

            t1 = std::chrono::high_resolution_clock::now();
            diff = t1 - t0;
            delta = diff.count();
        }
        else
            delta = frameTime;
    }
}

void Application::Exit()
{
    mRunning = false;
}

} // namespace core
} // namespace sgl
