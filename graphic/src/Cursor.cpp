#include "sgl/graphic/Cursor.h"

#include "sgl/core/event/MouseMotionEvent.h"
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
    // cursor rendering is not affected by the camera
    SetCamera(Camera::GetDummyCamera());
}

// NOTE
// OnMouseMotion is called by Stage if the Cursor is assigned to it,
// but in an application that doesn't use sgui you need to register
// the Cursor as mouse listener in the Application class
void Cursor::OnMouseMotion(core::MouseMotionEvent & event)
{
    SetPosition(event.GetX() - mHotX, event.GetY() - mHotY);
}

} // namespace graphic
} // namespace sgl
