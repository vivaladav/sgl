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

    void SetVisible(bool val);
    bool IsVisible() const;

    // temporary code
    graphic::Font * GetDefaultFont();
    void SetDefaultFont(graphic::Font * font);

    void Render();

private:
    Stage() = default;
    ~Stage() = default;

    void OnMouseButtonDown(core::MouseButtonEvent & event) override;
    void OnMouseButtonUp(core::MouseButtonEvent & event) override;
    void OnMouseMotion(core::MouseMotionEvent & event) override;

    void OnKeyDown(core::KeyboardEvent & event) override;
    void OnKeyUp(core::KeyboardEvent & event) override;

private:
    static Stage * mInstance;

    graphic::Font * mDefaultFont = nullptr;

    bool mVisible = true;

    // access private methods to notify changes
    friend class Widget;
};

inline Stage * Stage::Instance() { return mInstance; }

inline void Stage::SetVisible(bool val) { mVisible = val; }
inline bool Stage::IsVisible() const { return mVisible; }

inline graphic::Font * Stage::GetDefaultFont() { return mDefaultFont; }
inline void Stage::SetDefaultFont(graphic::Font * font) { mDefaultFont = font; }

inline void Stage::Render()
{
    if(mVisible)
        PropagateRender();
}

} // namespace sgui
} // namespace sgl
