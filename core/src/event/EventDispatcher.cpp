#include "EventDispatcher.h"

#include "sgl/core/event/ApplicationEvent.h"
#include "sgl/core/event/ApplicationEventListener.h"
#include "sgl/core/event/KeyboardEvent.h"
#include "sgl/core/event/KeyboardEventListener.h"
#include "sgl/core/event/MouseButtonEvent.h"
#include "sgl/core/event/MouseEventListener.h"
#include "sgl/core/event/MouseMotionEvent.h"

#include <SDL2/SDL.h>

#include <algorithm>
#include <cassert>

namespace sgl
{
namespace core
{

void EventDispatcher::AddApplicationListener(sgl::core::ApplicationEventListener * el)
{
    // do not add NULL
    if(!el)
        return ;

    auto it = std::find(mApplicationListeners.begin(), mApplicationListeners.end(), el);

    // listener not found -> add it
    if(mApplicationListeners.end() == it)
    {
        el->mDispatcher = this;
        mApplicationListeners.emplace_back(el);
    }
}

void EventDispatcher::AddKeyboardListener(sgl::core::KeyboardEventListener * el)
{
    // do not add NULL
    if(!el)
        return ;

    auto it = std::find(mKeyboardListeners.begin(), mKeyboardListeners.end(), el);

    // listener not found -> add it
    if(mKeyboardListeners.end() == it)
    {
        el->mDispatcher = this;
        mKeyboardListeners.emplace_back(el);
    }
}

void EventDispatcher::AddMouseListener(sgl::core::MouseEventListener * el)
{
    // do not add NULL
    if(!el)
        return ;

    auto it = std::find(mMouseListeners.begin(), mMouseListeners.end(), el);

    // listener not found -> add it
    if(mMouseListeners.end() == it)
    {
        el->mDispatcher = this;
        mMouseListeners.emplace_back(el);
    }
}

void EventDispatcher::RemoveApplicationListener(ApplicationEventListener * el)
{
    auto it = std::find(mApplicationListeners.begin(), mApplicationListeners.end(), el);

    // listener found -> remove it
    if(it != mApplicationListeners.end())
        mApplicationListeners.erase(it);
}

void EventDispatcher::RemoveKeyboardListener(KeyboardEventListener * el)
{
    auto it = std::find(mKeyboardListeners.begin(), mKeyboardListeners.end(), el);

    // listener found -> remove it
    if(it != mKeyboardListeners.end())
        mKeyboardListeners.erase(it);
}

void EventDispatcher::RemoveMouseListener(MouseEventListener * el)
{
    auto it = std::find(mMouseListeners.begin(), mMouseListeners.end(), el);

    // listener found -> remove it
    if(it != mMouseListeners.end())
        mMouseListeners.erase(it);
}

void EventDispatcher::Update()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_MOUSEMOTION:
            {
                const SDL_MouseMotionEvent & m = event.motion;

                MouseMotionEvent e(m.x, m.y, m.xrel, m.yrel, m.state);

                for(MouseEventListener * el : mMouseListeners)
                {
                    el->OnMouseMotion(e);

                    // stop propagation if event is consumed
                    if(e.IsConsumed())
                        break;
                }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            {
                const SDL_MouseButtonEvent & b = event.button;

                MouseButtonEvent e(b.x, b.y, b.button);

                for(MouseEventListener * el : mMouseListeners)
                {
                    el->OnMouseButtonDown(e);

                    // stop propagation if event is consumed
                    if(e.IsConsumed())
                        break;
                }
            }
            break;

            case SDL_MOUSEBUTTONUP:
            {
                const SDL_MouseButtonEvent & b = event.button;

                MouseButtonEvent e(b.x, b.y, b.button);

                for(MouseEventListener * el : mMouseListeners)
                {
                    el->OnMouseButtonUp(e);

                    // stop propagation if event is consumed
                    if(e.IsConsumed())
                        break;
                }
            }
            break;

            case SDL_KEYDOWN:
            {
                KeyboardEvent e(event.key.keysym.sym, event.key.keysym.mod);

                for(KeyboardEventListener * el : mKeyboardListeners)
                {
                    el->OnKeyDown(e);

                    // stop propagation if event is consumed
                    if(e.IsConsumed())
                        break;
                }
            }
            break;

            case SDL_KEYUP:
            {
                KeyboardEvent e(event.key.keysym.sym, event.key.keysym.mod);

                for(KeyboardEventListener * el : mKeyboardListeners)
                {
                    el->OnKeyUp(e);

                    // stop propagation if event is consumed
                    if(e.IsConsumed())
                        break;
                }
            }
            break;

            case SDL_QUIT:
            {
                ApplicationEvent e;

                for(ApplicationEventListener * el : mApplicationListeners)
                {
                    el->OnApplicationQuit(e);

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
}

} // namespace core
} // namespace sgl

