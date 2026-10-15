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
    static void PrintVideoInfo();

    // -- display --
    static int GetNumDisplays();
    static int GetNumDisplayModes(int display);
    // NOTE use -1 to ignore a value
    static bool IsDisplayModeSupported(int display, int w, int h, int refresh);
    // NOTE use -1 to ignore a value
    static int GetDisplayModeIndex(int display, int w, int h, int refresh);
    static void GetDisplayBounds(int display, int & x, int & y, int & w, int & h);
    static void PrintDisplayModes(int display);

    // -- cursor --
    static void HideSystemCursor();
    static void ShowSystemCursor();
};

} // namespace graphic
} // namespace sgl
