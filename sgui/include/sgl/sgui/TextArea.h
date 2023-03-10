#pragma once

#include "sgl/sgui/Widget.h"

#include <string>
#include <vector>

namespace sgl
{

namespace graphic
{
    class Font;
    class Renderable;
}

namespace sgui
{

class TextArea : public Widget
{
public:
    enum Alignment : unsigned int
    {
        // HORIZONTAL ALIGNMENT
        ALIGN_H_LEFT,
        ALIGN_H_CENTER,
        ALIGN_H_RIGHT,
        // VERTICAL ALIGNMENT
        ALIGN_V_TOP,
        ALIGN_V_CENTER,
        ALIGN_V_BOTTOM,
    };

public:
    TextArea(int w, int h, graphic::Font * font, bool autoAdapt, Widget * parent);
    TextArea(int w, int h, const char * txt, graphic::Font * font, bool autoAdapt, Widget * parent);

    void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    void SetColor(unsigned int color);

    void setTextAlignment(Alignment horiz, Alignment vert);
    void setTextAlignmentHorizontal(Alignment horiz);
    void setTextAlignmentVertical(Alignment vert);

    void ClearText();
    const std::string & GetText() const;
    void SetText(const char * txt);

    int GetTextWidth() const;
    int GetTextHeight() const;
    void AdaptHeightToContent();

private:
    void CreateText();

    void AddTextLine(const char * txt);
    void AddEmptyLine(int h);

    void HandlePositionChanged() override;

private:    
    std::vector<graphic::Renderable *> mTxtLines;

    std::string mStr;

    graphic::Font * mFont = nullptr;

    Alignment mAlignH = ALIGN_H_LEFT;
    Alignment mAlignV = ALIGN_V_TOP;

    int mTextW = 0;
    int mTextH = 0;

    unsigned char mTxtR = 255;
    unsigned char mTxtG = 255;
    unsigned char mTxtB = 255;
    unsigned char mTxtA = 255;

    bool mAutoAdaptH = false;
};

inline void TextArea::setTextAlignment(Alignment horiz, Alignment vert)
{
    if(mAlignH == horiz && mAlignV == vert)
        return ;

    mAlignH = horiz;
    mAlignV = vert;

    HandlePositionChanged();
}

inline void TextArea::setTextAlignmentHorizontal(Alignment horiz)
{
    if(mAlignH == horiz)
        return ;

    mAlignH = horiz;

    HandlePositionChanged();
}

inline void TextArea::setTextAlignmentVertical(Alignment vert)
{
    if(mAlignV == vert)
        return ;

    mAlignV = vert;

    HandlePositionChanged();
}

inline const std::string & TextArea::GetText() const { return mStr; }

inline int TextArea::GetTextWidth() const { return mTextW; }
inline int TextArea::GetTextHeight() const { return mTextH; }

inline void TextArea::AdaptHeightToContent()
{
    if(mTextH > 0)
        SetSize(GetWidth(), mTextH);
}

} // namespace sgui
} // namespace sgl
