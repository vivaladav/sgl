#pragma once

#include <string>

namespace sgl
{
namespace utilities
{

class ISystem
{
public:
    virtual ~ISystem();

    virtual bool OpenUrlInBrowser(const std::string & url) = 0;
};

inline ISystem::~ISystem() {}

} // namespace utilities
} // namespace sgl
