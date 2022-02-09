#pragma once

namespace sgl
{
namespace ai
{

class IPathMap
{
public:
    virtual ~IPathMap();

    virtual bool IsCellWalkable(unsigned int r, unsigned int c) const = 0;
};

inline IPathMap::~IPathMap() { }

} // namespace ai
} // namespace sgl
