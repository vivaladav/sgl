#pragma once

#if defined(LINUX)
    #include "sgl/utilities/linux/System.h"
#elif defined(WINDOWS)
    #include "sgl/utilities/windows/System.h"
#else
    #error Platform not supported
#endif
