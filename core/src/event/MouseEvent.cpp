#include "sgl/core/event/MouseEvent.h"

#ifdef LINUX
    #include <SDL2/SDL.h>
#else
    #include <SDL.h>
#endif

namespace sgl
{
namespace core
{

const int MouseEvent::BUTTON_LEFT   = SDL_BUTTON_LEFT;
const int MouseEvent::BUTTON_MIDDLE = SDL_BUTTON_MIDDLE;
const int MouseEvent::BUTTON_RIGHT  = SDL_BUTTON_RIGHT;
const int MouseEvent::BUTTON_X1     = SDL_BUTTON_X1;
const int MouseEvent::BUTTON_X2     = SDL_BUTTON_X2;

} // namespace core
} // namespace sgl
