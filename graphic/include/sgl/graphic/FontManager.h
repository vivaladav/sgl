#pragma once

#include <string>
#include <unordered_map>

struct SDL_RWops;

namespace sgl
{

namespace core { class DataPackage; }

namespace graphic
{

class Font;

class FontManager
{
public:
    static FontManager * Create();
    static FontManager * Instance();
    static void Destroy();

    void RegisterFont(const core::DataPackage & package, const char * file);
    Font * GetFont(const char * file, int size, int style);

    void ClearFonts();

private:
    FontManager();
    ~FontManager();

private:
    static FontManager * mInstance;

    std::unordered_map<std::string, SDL_RWops *> mFontsData;
    std::unordered_map<std::string, Font *> mFonts;
};

inline FontManager * FontManager::Instance() { return mInstance; }

inline FontManager::FontManager() { }
inline FontManager::~FontManager() { ClearFonts(); }

} // namespace graphic
} // namespace sgl
