#pragma once

#if defined(LINUX)
    #include "sgl/utilities/linux/Filesystem.h"
#elif defined(WINDOWS)
    #include "sgl/utilities/windows/Filesystem.h"
#else
    #error Platform not supported
#endif
