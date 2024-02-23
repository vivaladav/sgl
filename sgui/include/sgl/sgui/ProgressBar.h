#pragma once

#include "sgl/sgui/Widget.h"

#include <functional>
#include <map>

namespace sgl
{
namespace sgui
{

class ProgressBar : public Widget
{
public:
    ProgressBar(float min, float max, Widget * parent = nullptr);

    void SetMinMax(float min, float max);
    float GetMin() const;
    float GetMax() const;

    float GetValue() const;
    void SetValue(float progress);
    void IncValue(float val);
    float GetValuePerc() const;
    void SetValuePerc(float perc);

    bool IsCompleted() const;

    void Reset();

    unsigned int AddFunctionOnCompleted(const std::function<void()> & f);
    void RemoveFunctionOnCompleted(unsigned int key);
    void ClearFunctionsOnCompleted();

protected:
    virtual void HandleProgressUpdate() = 0;

private:
    void Complete();

private:
    std::map<unsigned int, std::function<void()>> mOnCompleted;

    float mValue = 0;
    float mMin = 0;
    float mMax = 100;

    bool mCompleted = false;
};

inline float ProgressBar::GetMin() const { return mMin; }
inline float ProgressBar::GetMax() const { return mMax; }

inline float ProgressBar::GetValue() const { return mValue; }

inline float ProgressBar::GetValuePerc() const
{
    return mValue * 100.f / (mMax - mMin);
}

inline bool ProgressBar::IsCompleted() const { return mCompleted; }

inline void ProgressBar::ClearFunctionsOnCompleted() { mOnCompleted.clear(); }

} // namespace sgui
} // namespace sgl
