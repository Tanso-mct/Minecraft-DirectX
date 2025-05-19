#include "pch.h"

#include "Interface/WindowContext.h"

#include "WB_Utility/include/WindowsHelpers.h"
#pragma comment(lib, "WB_Utility.lib")

#include "WB_Utility_Test/WindowProc.h"

TEST(WindowsHelpers, CreateWindowNotApi)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = L"CreateWindowNotApi";

    HWND hWnd = nullptr;

    // Create a window
    WB::CreateWindowNotApi
    (
        hWnd,
        L"CreateWindowNotApi",
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        nullptr,
        wc
    );
    
}

TEST(WindowsHelpers, ShowWindowNotApi)
{
    WB::WindowState state;
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = L"ShowWindowNotApi";

    HWND hWnd = nullptr;

    // Create a window
    WB::CreateWindowNotApi
    (
        hWnd,
        L"ShowWindowNotApi",
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        nullptr,
        wc
    );

    // Show the window
    WB::ShowWindowNotApi(hWnd);
}