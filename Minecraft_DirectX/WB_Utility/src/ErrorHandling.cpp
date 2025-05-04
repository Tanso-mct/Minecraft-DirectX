#include "WB_Utility/include/ErrorHandling.h"

#include <windows.h>

UTILITY_API void WB::MessageBoxError(const std::string &title, const std::string &message)
{
    MessageBoxA
    (
        nullptr,
        message.c_str(),
        title.c_str(),
        MB_OK | MB_ICONERROR | MB_TASKMODAL | MB_SETFOREGROUND | MB_TOPMOST
    );
}