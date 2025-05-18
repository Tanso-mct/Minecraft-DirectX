#pragma once

#include <Windows.h>

#include <string_view>

namespace WB
{
    struct WindowContextConfig
    {
        WNDCLASSEX _wcex = 
        {
            sizeof(WNDCLASSEX),
            CS_HREDRAW | CS_VREDRAW,
            nullptr,
            0,
            0,
            nullptr,
            LoadIcon(nullptr, IDI_APPLICATION),
            LoadCursor(nullptr, IDC_ARROW),
            (HBRUSH)(COLOR_WINDOW + 1),
            nullptr,
            L"Window",
            LoadIcon(nullptr, IDI_APPLICATION)
        };

        LPCWSTR name_ = L"Window";
        int initialPosX_ = CW_USEDEFAULT;
        int initialPosY_ = CW_USEDEFAULT;
        unsigned int width_ = 800;
        unsigned int height_ = 600;
        DWORD style_ = WS_OVERLAPPEDWINDOW;
        HWND hWndParent_ = NULL;
        HINSTANCE hInstance = nullptr;
    };

    class IWindowContext
    {
    public:
        virtual ~IWindowContext() = default;

        virtual void Initialize(WindowContextConfig& config) = 0;

        virtual HWND& GetHWnd() = 0;
        virtual HINSTANCE& GetHInstance() = 0;

        virtual std::string_view GetName();
        virtual int GetPosX() = 0;
        virtual int GetPosY() = 0;
        virtual int GetWidth() = 0;
        virtual int GetHeight() = 0;

        virtual void CreateWindowNotApi() = 0;

        virtual bool& IsFocus() = 0;
        virtual bool& IsMaximized() = 0;
        virtual bool& IsMinimized() = 0;

        virtual void CreateSwapChain() = 0;
        virtual void ResizeSwapChain(int width, int height) = 0;

        virtual void CreateRenderTarget() = 0;
        virtual void ResizeRenderTarget(int width, int height) = 0;

        virtual void CreateDepthStencil() = 0;
        virtual void ResizeDepthStencil(int width, int height) = 0;

        virtual void CreateViewport() = 0;
        virtual void ResizeViewport(int width, int height) = 0;

        virtual void CreateScissorRect() = 0;
        virtual void ResizeScissorRect(int width, int height) = 0;
    };
    
} // namespace MCT