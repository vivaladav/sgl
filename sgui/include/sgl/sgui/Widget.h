#pragma once

#include "sgl/sgui/WidgetContainer.h"

#include <chrono>
#include <functional>
#include <vector>

namespace sgl
{

namespace graphic
{
    class Camera;
    class Renderable;
}

namespace sgui
{

class Stage;

class Widget : public WidgetContainer
{
public:
    enum ResizePolicy : unsigned int
    {
        FIXED,          // size only changes when set with SetSize()
        GROW_ONLY,      // size grows dinamically, but it doesn't shrink
        DYNAMIC         // size grows and shrinks when adding/removing elements
    };

public:
    Widget(Widget * parent = nullptr);
    ~Widget();

    void SetResizePolicy(ResizePolicy policy);

    unsigned int GetWidgetId() const;

    Widget * GetParent() const;
    void SetParent(Widget * parent);

    void SetTooltip(Widget * t);
    int GetTooltipDelay() const;
    void SetTooltipDelay(int ms);
    int GetTooltipShowingTime() const;
    void SetTooltipShowingTime(int ms);
    void SetTooltipMargins(int horz, int vert);
    bool IsShowingTooltip() const;
    void SetFunctionOnShowingTooltip(const std::function<void()> & f);

    void SetEnabled(bool val);
    bool IsEnabled() const;

    void SetVisible(bool val) final;

    int GetX() const;
    int GetY() const;
    int GetScreenX() const;
    int GetScreenY() const;
    void SetPosition(int x, int y);
    void SetX(int x);
    void SetY(int y);

    bool IsMouseOver() const;
    int GetTimerOver() const;
    virtual bool IsScreenPointInside(int x, int y);

    int GetWidth() const;
    int GetHeight() const;

    unsigned char GetAlpha() const;
    void SetAlpha(unsigned char alpha);

    void SetCamera(graphic::Camera * cam);
    graphic::Camera * GetCamera() const;

    void SetVisibleArea(int x, int y, int w, int h);
    void ClearVisibleArea();
    bool IsInVisibleArea() const;
    bool IsWidgetInVisibleArea(const Widget * w) const;

    void DeleteLater();

protected:
    void SetSize(int w, int h);

    virtual void UpdateSize();

    virtual void HandleStateEnabled();
    virtual void HandleStateDisabled();

    virtual void HandleMouseButtonDown(core::MouseButtonEvent & event);
    virtual void HandleMouseButtonUp(core::MouseButtonEvent & event);
    virtual void HandleMouseMotion(core::MouseMotionEvent & event);
    virtual void HandleMouseWheel(core::MouseWheelEvent & event);

    virtual void HandleKeyDown(core::KeyboardEvent & event);
    virtual void HandleKeyUp(core::KeyboardEvent & event);

    virtual void HandleMouseOver();
    virtual void HandleMouseOut();

    void RegisterRenderable(graphic::Renderable * elem);
    void UnregisterRenderable(graphic::Renderable * elem);

    unsigned int MixColorAndAlpha(unsigned int color) const;
    unsigned char MixAlphaAndAlpha(unsigned char a) const;

    virtual void HandlePositionChanged();

    virtual void OnRender();
    virtual void OnUpdate(float delta);

private:
    void UpdateTimeOver();

    void ShowTooltip();
    void HideTooltip();

    void SetScreenPosition(int x, int y);

    void SetMouseOver();
    void SetMouseOut();

    void HandleParentPositionChanged(int dx, int dy);
    void PropagateParentPositionChanged(int dx, int dy);

    bool IsVisibleOnScreen() const;

    void UpdateVisibleAreaPoints();

private:
    std::vector<graphic::Renderable *> mRenderables;

    Stage * mStage = nullptr;
    Widget * mParent = nullptr;

    std::function<void()> mOnShowingTooltip = []{};
    Widget * mTooltip = nullptr;
    int mTooltipTimeDelayMs = 300;
    int mTooltipTimeShowingMs = 2500;
    int mTooltipMarginHoriz = 15;
    int mTooltipMarginVert = 15;
    bool mTooltipShowing = false;
    bool mTooltipShowed = false;

    graphic::Camera * mCamera = nullptr;

    ResizePolicy mResizePol = GROW_ONLY;

    unsigned int mId = 0;

    int mRelX = 0;
    int mRelY = 0;

    int mScreenX = 0;
    int mScreenY = 0;

    int mWidth = 0;
    int mHeight = 0;

    int mVisX = 0;
    int mVisY = 0;
    int mVisW = 0;
    int mVisH = 0;
    int mVisX1 = 0;
    int mVisY1 = 0;
    int mVisX2 = 0;
    int mVisY2 = 0;

    unsigned char mA = 255;

    std::chrono::time_point<std::chrono::high_resolution_clock> mTOver0;
    int mTimeOverMs = 0;

    bool mEnabled = true;
    bool mMouseOver = false;
    bool mVisibleAreaSet = false;

    // access private methods for events and rendering
    friend class WidgetContainer;
};

inline void Widget::SetResizePolicy(ResizePolicy policy) { mResizePol = policy; }

inline unsigned int Widget::GetWidgetId() const { return mId; }

inline Widget * Widget::GetParent() const { return mParent; }

inline int Widget::GetTooltipDelay() const { return mTooltipTimeDelayMs; }
inline void Widget::SetTooltipDelay(int ms) { mTooltipTimeDelayMs = ms; }
inline int Widget::GetTooltipShowingTime() const { return mTooltipTimeShowingMs; }
inline void Widget::SetTooltipShowingTime(int ms) { mTooltipTimeShowingMs = ms; }
inline void Widget::SetTooltipMargins(int horz, int vert)
{
    mTooltipMarginHoriz = horz;
    mTooltipMarginVert = vert;
}
inline bool Widget::IsShowingTooltip() const { return mTooltipShowing; }
inline void Widget::SetFunctionOnShowingTooltip(const std::function<void()> & f) { mOnShowingTooltip = f; }

inline bool Widget::IsEnabled() const { return mEnabled; }

inline int Widget::GetX() const { return mRelX; }
inline int Widget::GetY() const { return mRelY; }
inline int Widget::GetScreenX() const { return mScreenX; }
inline int Widget::GetScreenY() const { return mScreenY; }

inline bool Widget::IsMouseOver() const { return mMouseOver; }
inline int Widget::GetTimerOver() const { return mTimeOverMs; }

inline int Widget::GetWidth() const { return mWidth; }
inline int Widget::GetHeight() const { return mHeight; }

inline unsigned char Widget::GetAlpha() const { return mA; }

inline graphic::Camera * Widget::GetCamera() const { return mCamera; }

inline void Widget::SetVisibleArea(int x, int y, int w, int h)
{
    mVisX = x;
    mVisY = y;
    mVisW = w;
    mVisH = h;
    mVisibleAreaSet = true;

    UpdateVisibleAreaPoints();
}

inline void Widget::ClearVisibleArea()
{
    mVisX = mVisY = mVisW =  mVisH = 0;
    mVisX1 = mVisY1 = mVisX2 = mVisY2 = 0;
    mVisibleAreaSet = false;
}

inline bool Widget::IsInVisibleArea() const
{
    return nullptr == mParent || mParent->IsWidgetInVisibleArea(this);
}

inline bool Widget::IsWidgetInVisibleArea(const Widget * w) const
{
    if(!mVisibleAreaSet)
        return true;

    const int wX1 = w->GetScreenX();
    const int wY1 = w->GetScreenY();
    const int wX2 = wX1 + w->GetWidth();
    const int wY2 = wY1 + w->GetHeight();

    return !mVisibleAreaSet || (wX1 < mVisX2 && wX2 > mVisX1 && wY1 < mVisY2 && wY2 > mVisY1);
}

inline unsigned int Widget::MixColorAndAlpha(unsigned int color) const
{
    const unsigned char maxA = 255;
    const unsigned int maskA = 0x000000FF;
    const unsigned int maskRGB = 0xFFFFFF00;
    const unsigned char a = (maskA & color) * mA / maxA;

    return (maskRGB & color) + a;
}

inline unsigned char Widget::MixAlphaAndAlpha(unsigned char a) const
{
    const unsigned char maxA = 255;

    return a * mA / maxA;
}

inline void Widget::UpdateVisibleAreaPoints()
{
    mVisX1 = mScreenX + mVisX;
    mVisY1 = mScreenY + mVisY;
    mVisX2 = mVisX1 + mVisW;
    mVisY2 = mVisY1 + mVisH;
}

} // namespace sgui
} // namespace sgl
