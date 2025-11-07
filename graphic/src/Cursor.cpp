#include "sgl/graphic/Cursor.h"

#include "sgl/graphic/Camera.h"

#ifdef LINUX
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

namespace sgl
{
namespace graphic
{

Cursor::Cursor(Texture * tex, int hotX, int hotY)
    : TexturedRenderable(tex)
    , mHotX(hotX)
    , mHotY(hotY)
{
    SetCamera(Camera::GetDummyCamera());
}

void Cursor::Render()
{
    int x = 0;
    int y = 0;
    SDL_GetMouseState(&x, &y);

    SetPosition(x - mHotX, y - mHotY);

    TexturedRenderable::Render();
}

} // namespace graphic
} // namespace sgl
