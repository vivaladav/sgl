#pragma once

namespace sgl
{
namespace utilities
{

class StringManager;

class StringsChangeListener
{
public:
    virtual ~StringsChangeListener();

private:
    virtual void OnStringsChanged();

    // only StringManager can notify events
    friend class StringManager;
};

} // namespace utilities
} // namespace sgl
