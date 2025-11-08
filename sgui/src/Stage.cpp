#include "sgl/sgui/Stage.h"

#include "sgl/core/event/MouseButtonEvent.h"
#include "sgl/core/event/MouseMotionEvent.h"
#include "sgl/graphic/Cursor.h"
#include "sgl/graphic/ModuleGraphic.h"
#include "sgl/sgui/Widget.h"

#include <algorithm>

namespace sgl
{
namespace sgui
{

Stage * Stage::mInstance = nullptr;

Stage * Stage::Create()
{
    if(!mInstance)
        mInstance = new Stage;

    return mInstance;
}

void Stage::Destroy()
{
    delete mInstance;
    mInstance = nullptr;
}

// -- cursor --
void Stage::SetCursor(graphic::Cursor * cursor)
{
    sgl::graphic::ModuleGraphic::HideSystemCursor();

    mCursor = cursor;
}

void Stage::ClearCursor()
{
    sgl::graphic::ModuleGraphic::ShowSystemCursor();

    mCursor = nullptr;
}

void Stage::CancelDeleteLater(Widget * w)
{
    auto it = std::find(mWidgetsToDelete.begin(), mWidgetsToDelete.end(), w);

    if(it != mWidgetsToDelete.end())
        mWidgetsToDelete.erase(it);
}

void Stage::DeleteLater(Widget * w)
{
    auto it = std::find(mWidgetsToDelete.begin(), mWidgetsToDelete.end(), w);

    // add only if not already added
    if(it == mWidgetsToDelete.end())
        mWidgetsToDelete.push_back(w);
}

void Stage::Render()
{
    if(IsVisible())
        PropagateRender();

    if(mCursor)
        mCursor->Render();
}

void Stage::Update(float delta)
{
    // delete widget scheduled for destruction
    for(Widget * w : mWidgetsToDelete)
        delete w;

    mWidgetsToDelete.clear();

    // propagate update
    PropagateUpdate(delta);
}

void Stage::OnMouseButtonDown(core::MouseButtonEvent & event)
{
    PropagateMouseButtonDown(event);
}

void Stage::OnMouseButtonUp(core::MouseButtonEvent & event)
{
    PropagateMouseButtonUp(event);
}

void Stage::OnMouseMotion(core::MouseMotionEvent & event)
{
    mMouseX = event.GetX();
    mMouseY = event.GetY();

    PropagateMouseMotion(event);

    if(mCursor != nullptr)
        mCursor->OnMouseMotion(event);
}

void Stage::OnMouseWheel(core::MouseWheelEvent & event)
{
    PropagateMouseWheel(event);
}

void Stage::OnKeyDown(core::KeyboardEvent & event)
{
    PropagateKeyDown(event);
}

void Stage::OnKeyUp(core::KeyboardEvent & event)
{
    PropagateKeyUp(event);
}

} // namespace sgui
} // namespace sgl
