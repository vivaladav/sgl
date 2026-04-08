#pragma once

namespace sgl
{
namespace utilities
{

class StringManager;

class StringsChangeListener
{
public:
    StringsChangeListener();
    virtual ~StringsChangeListener();

private:
    virtual void OnStringsChanged();

    // only StringManager can notify events
    friend class StringManager;
};

} // namespace utilities
} // namespace sgl
