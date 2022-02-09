#pragma once

namespace sgl
{
namespace core
{

class Event
{
public:
    virtual ~Event();

    void SetConsumed();
    bool IsConsumed() const;

private:
    bool mConsumed = false;
};

inline void Event::SetConsumed() { mConsumed = true; }
inline bool Event::IsConsumed() const { return mConsumed; }

} // namespace core
} // namespace sgl
