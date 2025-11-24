#pragma once

namespace sgl
{
namespace ai
{

class IPathMap
{
public:
    virtual ~IPathMap() = default;

    virtual bool IsCellWalkable(unsigned int r, unsigned int c) const = 0;

    virtual unsigned int GetNumRows() const = 0;
    virtual unsigned int GetNumCols() const = 0;
};

} // namespace ai
} // namespace sgl
