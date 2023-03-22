#pragma once

#include <string>

namespace sgl
{
namespace utilities
{

class IFilesystem
{
public:
    virtual ~IFilesystem();

    virtual std::string GetUserHomeDirectory() = 0;
};

inline IFilesystem::~IFilesystem() {}

} // namespace utilities
} // namespace sgl
