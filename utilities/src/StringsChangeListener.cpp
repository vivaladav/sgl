#include "sgl/utilities/StringsChangeListener.h"

#include "sgl/utilities/StringManager.h"

namespace sgl
{
namespace utilities
{

StringsChangeListener::~StringsChangeListener()
{
    auto sm = StringManager::Instance();

    if(sm != nullptr)
        sm->RemoveListener(this);
}

void StringsChangeListener::OnStringsChanged() {}

} // namespace utilities
} // namespace sgl
