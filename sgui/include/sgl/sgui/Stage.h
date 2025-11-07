#pragma once

#include "sgl/core/event/KeyboardEventListener.h"
#include "sgl/core/event/MouseEventListener.h"
#include "sgl/sgui/WidgetContainer.h"

namespace sgl
{

namespace graphic
{
    class Cursor;
    class Font;
}

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

    // -- cursor --
    // cursor is only used, it is not owned (deleted) by Stage
    void SetCursor(graphic::Cursor * cursor);
    void ClearCursor();
    void HideCursor();
    void ShowCursor();

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

    graphic::Cursor * mCursor = nullptr;
    graphic::Cursor * mHiddenCursor = nullptr;

    int mMouseX = -1;
    int mMouseY = -1;

    // access private methods to notify changes
    friend class Widget;
};

inline Stage * Stage::Instance() { return mInstance; }

inline int Stage::GetMouseX() const { return mMouseX; }
inline int Stage::GetMouseY() const { return mMouseY; }

// -- cursor --
inline void Stage::HideCursor()
{
    mHiddenCursor = mCursor;
    mCursor = nullptr;
}
inline void Stage::ShowCursor()
{
    mCursor = mHiddenCursor;
    mHiddenCursor = nullptr;
}

inline graphic::Font * Stage::GetDefaultFont() { return mDefaultFont; }
inline void Stage::SetDefaultFont(graphic::Font * font) { mDefaultFont = font; }

} // namespace sgui
} // namespace sgl
