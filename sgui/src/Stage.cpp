#include "sgl/sgui/Stage.h"

#include "sgl/core/event/MouseButtonEvent.h"
#include "sgl/core/event/MouseMotionEvent.h"
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

void Stage::Update(float delta)
{
    // delete widget scheduled for destruction
    for(Widget * w : mWidgetsToDelete)
        delete w;

    mWidgetsToDelete.clear();

    // TODO propagate update to all children
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
    PropagateMouseMotion(event);
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
