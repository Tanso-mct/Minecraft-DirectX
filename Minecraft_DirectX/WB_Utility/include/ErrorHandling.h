#pragma once

#include "WB_Utility/include/Config.h"

#include <Windows.h>
#include <string>

namespace WB
{
    UTILITY_API void MessageBoxError(const std::string& title, const std::string& message);

    inline std::string HrToString(HRESULT hr)
    {
        char* msgBuf = nullptr;
        DWORD size = FormatMessageA
        (
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            hr,
            MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
            (LPSTR)&msgBuf,
            0, nullptr
        );

        std::string msg = (size && msgBuf) ? msgBuf : "Unknown error";
        if (msgBuf) LocalFree(msgBuf);
        return msg;
    }
} // namespace WB