#pragma once

#include "WB_Utility/include/Config.h"

#include  "Interface/WindowContext.h"

namespace WB
{
    UTILITY_API void CreateWindowNotApi
    (
        HWND& hWnd,
        LPCWSTR windowName, 
        const int& posX, const int& posY,
        const int& width, const int& height,
        HWND hWndParent,
        WNDCLASSEX& wc
    );

    UTILITY_API void ShowWindowNotApi(HWND& hWnd);
}