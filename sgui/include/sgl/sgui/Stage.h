#pragma once

#include "sgl/core/event/KeyboardEventListener.h"
#include "sgl/core/event/MouseEventListener.h"
#include "sgl/sgui/WidgetContainer.h"

#include <vector>

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
    void SetCursor(graphic::Cursor * cursor, bool show = true);
    void ClearCursor();
    void HideCursor();
    void ShowCursor();
    void ToggleCursorVisibility();
    void AutoHideInactiveCursor(bool enabled, float timeSec = 2.f);
    bool IsShowingCursor() const;
    bool IsAutoHidingCursor() const;

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

    void UpdateDelete();

private:
    static Stage * mInstance;

    std::list<Widget *> mWidgetsToDelete;

    graphic::Font * mDefaultFont = nullptr;

    graphic::Cursor * mCursor = nullptr;
    float mTimerAutohideCursor = 0.f;
    float mTimeAutohideCursor = 2.f;
    bool mAutohideCursor = false;
    bool mShowCursor = false;
    bool mRenderCursor = false;


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
    mShowCursor = false;
    mRenderCursor = false;
}
inline void Stage::ShowCursor()
{
    mShowCursor = true;

    if(mCursor != nullptr)
    {
        mRenderCursor = true;

        mTimerAutohideCursor = mTimeAutohideCursor;
    }
}
inline void Stage::ToggleCursorVisibility()
{
    if(mShowCursor)
        HideCursor();
    else
        ShowCursor();
}

inline void Stage::AutoHideInactiveCursor(bool enabled, float timeSec)
{
    mAutohideCursor = enabled;

    mTimeAutohideCursor = timeSec;
    mTimerAutohideCursor = mTimeAutohideCursor;
}

inline bool Stage::IsShowingCursor() const { return mShowCursor; }
inline bool Stage::IsAutoHidingCursor() const { return mAutohideCursor; }

inline graphic::Font * Stage::GetDefaultFont() { return mDefaultFont; }
inline void Stage::SetDefaultFont(graphic::Font * font) { mDefaultFont = font; }

} // namespace sgui
} // namespace sgl
