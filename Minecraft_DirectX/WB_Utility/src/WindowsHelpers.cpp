#include "WB_Utility/include/WindowsHelpers.h"

#include "WB_Utility/include/ErrorHandling.h"

UTILITY_API void WB::CreateWindowNotApi
(
    HWND& hWnd,
    LPCWSTR windowName, 
    const int& posX, const int& posY,
    const int& width, const int& height,
    HWND hWndParent,
    WNDCLASSEX& wc
){
    if (!RegisterClassEx(&wc))
    {
        WB::MessageBoxError
        (
            "WB_Utility",
            "WindowContext CreateWindowNotApi : Failed to register window class"
        );
    }

    hWnd = CreateWindow
    (
        wc.lpszClassName,
        windowName,
        wc.style,
        posX,
        posY,
        width,
        height,
        hWndParent,
        nullptr,
        wc.hInstance,
        nullptr
    );

    if (!hWnd)
    {
        WB::MessageBoxError
        (
            "WB_Utility",
            "WindowContext CreateWindowNotApi : Failed to create window"
        );
    }
}

UTILITY_API void WB::ShowWindowNotApi(HWND& hWnd)
{
    if (!hWnd)
    {
        WB::MessageBoxError
        (
            "WB_Utility",
            "WindowContext ShowWindowNotApi : Window handle is null"
        );
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
}