#pragma once

#include "sgl/core/event/KeyboardEventListener.h"
#include "sgl/core/event/MouseEventListener.h"
#include "sgl/sgui/WidgetContainer.h"

namespace sgl
{

namespace graphic { class Font; }

namespace sgui
{

class Widget;

class Stage : public WidgetContainer, public core::KeyboardEventListener, public core::MouseEventListener
{
public:
    static Stage * Create();
    static Stage * Instance();
    static void Destroy();

    int GetMouseX() const;
    int GetMouseY() const;

    // temporary code
    graphic::Font * GetDefaultFont();
    void SetDefaultFont(graphic::Font * font);

    void CancelDeleteLater(Widget * w);
    void DeleteLater(Widget * w);

    void Render();
    void Update(float delta);

private:
    Stage() = default;
    ~Stage() = default;

    void OnMouseButtonDown(core::MouseButtonEvent & event) override;
    void OnMouseButtonUp(core::MouseButtonEvent & event) override;
    void OnMouseMotion(core::MouseMotionEvent & event) override;
    void OnMouseWheel(core::MouseWheelEvent & event) override;

    void OnKeyDown(core::KeyboardEvent & event) override;
    void OnKeyUp(core::KeyboardEvent & event) override;

private:
    static Stage * mInstance;

    std::vector<Widget *> mWidgetsToDelete;

    graphic::Font * mDefaultFont = nullptr;

    int mMouseX = -1;
    int mMouseY = -1;

    // access private methods to notify changes
    friend class Widget;
};

inline Stage * Stage::Instance() { return mInstance; }

inline int Stage::GetMouseX() const { return mMouseX; }
inline int Stage::GetMouseY() const { return mMouseY; }

inline graphic::Font * Stage::GetDefaultFont() { return mDefaultFont; }
inline void Stage::SetDefaultFont(graphic::Font * font) { mDefaultFont = font; }

inline void Stage::DeleteLater(Widget * w) { mWidgetsToDelete.push_back(w); }

inline void Stage::Render()
{
    if(IsVisible())
        PropagateRender();
}

} // namespace sgui
} // namespace sgl
