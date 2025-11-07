#pragma once

namespace sgl
{
namespace graphic
{

class ModuleGraphic
{
public:
    // -- module info --
    static void PrintBuildLibs();
    static void PrintRuntimeLibs();

    // -- cursor --
    static void HideSystemCursor();
    static void ShowSystemCursor();
};

} // namespace graphic
} // namespace sgl
