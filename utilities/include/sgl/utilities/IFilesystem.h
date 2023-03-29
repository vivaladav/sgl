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

    virtual std::string GetUserHomeDirectory() const = 0;

    virtual bool CreateDirectory(const std::string & path) const = 0;
    virtual bool CreateDirectories(const std::string & path) const = 0;
    virtual bool DoesDirectoryExist(const std::string & path) const = 0;
};

inline IFilesystem::~IFilesystem() {}

} // namespace utilities
} // namespace sgl
