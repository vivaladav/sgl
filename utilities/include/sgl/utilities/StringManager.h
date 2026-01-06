#pragma once

#include <string>
#include <unordered_map>

namespace sgl
{

namespace core { class DataPackage; }

namespace utilities
{

class StringManager
{
public:
    static StringManager * Create();
    static StringManager * Instance();
    static void Destroy();

public:
    bool RegisterPackage(const char * file);

    bool LoadStringsFromFile(const char * file);
    bool LoadStringsFromPackage(const char * file);

    const std::string & GetString(const std::string & sid) const;

private:
    StringManager() = default;
    ~StringManager();

    void LoadStringsData(const char * data, unsigned int size);

private:
    static StringManager *  mInstance;

private:
    std::unordered_map<std::string, std::string> mStrings;

    core::DataPackage * mPackage = nullptr;
};

inline StringManager * StringManager::Instance() { return mInstance; }

} // namespace utilities
} // namespace sgl
