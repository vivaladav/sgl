#pragma once

#include <list>
#include <string>
#include <unordered_map>

namespace sgl
{

namespace core { class DataPackage; }

namespace utilities
{

class StringsChangeListener;

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
    const char * GetCString(const std::string & sid) const;

    // LISTENERS
    void AddListener(StringsChangeListener * l);
    void RemoveListener(StringsChangeListener * l);

private:
    StringManager() = default;
    ~StringManager();

    void LoadStringsData(const char * data, unsigned int size);

    void NotifyListeners();

private:
    static StringManager *  mInstance;

private:
    std::unordered_map<std::string, std::string> mStrings;

    std::list<StringsChangeListener *> mListeners;

    core::DataPackage * mPackage = nullptr;
};

inline StringManager * StringManager::Instance() { return mInstance; }

inline const char * StringManager::GetCString(const std::string & sid) const
{
    return GetString(sid).c_str();
}

} // namespace utilities
} // namespace sgl
