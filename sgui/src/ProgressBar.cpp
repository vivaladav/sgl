#include "sgl/sgui/ProgressBar.h"

namespace sgl
{
namespace sgui
{

const float delta = 0.001f;

ProgressBar::ProgressBar(float min, float max, Widget * parent)
    : Widget(parent)
    , mValue(min)
    , mMin(min)
    , mMax(max)
{
}

void ProgressBar::SetMinMax(float min, float max)
{
    mMin = min;
    mMax = max;

    // clamp value
    if(min > mValue)
        mValue = min;
    if(max < mValue)
        mValue = max;

    // update value
    mCompleted = false;
    SetValue(mValue);
}

void ProgressBar::SetValue(float progress)
{
    if(progress < mMin)
        mValue = mMin;
    else if(progress > mMax)
    {
        Complete();
        return ;
    }
    else
        mValue = progress;

    if((mMax - mValue) < delta)
        Complete();
    else
        HandleProgressUpdate();
}

void ProgressBar::IncValue(float val)
{
    mValue += val;

    if(mValue > mMax || (mMax - mValue) < delta)
        Complete();
    else if(mValue < mMin)
    {
        mValue = mMin;
        HandleProgressUpdate();
    }
    else
        HandleProgressUpdate();
}

void ProgressBar::SetValuePerc(float perc)
{
    if(perc < 0.f)
        perc = 0.f;
    else if(perc > 100.f)
    {
        Complete();
        return ;
    }

    mValue = perc * (mMax - mMin) / 100.f;

    if((100.f - perc) < delta)
        Complete();
    else
        HandleProgressUpdate();
}

void ProgressBar::Reset()
{
    mCompleted = false;
    mValue = mMin;

    HandleProgressUpdate();
}

unsigned int ProgressBar::AddFunctionOnCompleted(const std::function<void()> & f)
{
    static unsigned int num = 0;

    int fId = ++num;
    mOnCompleted.emplace(fId, f);

    return fId;
}

void ProgressBar::RemoveFunctionOnCompleted(unsigned int fId)
{
    auto it = mOnCompleted.find(fId);

    if(it != mOnCompleted.end())
        mOnCompleted.erase(it);
}

void ProgressBar::Complete()
{
    mCompleted = true;
    mValue = mMax;

    HandleProgressUpdate();

    for(auto & it: mOnCompleted)
        it.second();
}

} // namespace sgui
} // namespace sgl
