#pragma once

#include <Windows.h>

#include <string>
#include <string_view>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl/client.h>

namespace WB
{
    struct WindowDesc
    {
        HINSTANCE hInstance = nullptr;
        HWND hWndParent = nullptr;

        std::wstring name = L"Window";
        UINT posX = CW_USEDEFAULT;
        UINT posY = CW_USEDEFAULT;
        UINT width = 800;
        UINT height = 600;
    };

    class IWindowContext
    {
    public:
        virtual ~IWindowContext() = default;

        virtual void Initialize(const WindowDesc& desc) = 0;

        virtual void Create(WNDCLASSEX& wc) = 0;
        virtual void Resize() = 0;

        virtual bool& IsFocus() = 0;

        virtual void Maximized() = 0;
        virtual void Minimized() = 0;
        virtual void Restored() = 0;

        virtual void SetPos(int x, int y, int width, int height, UINT flags) = 0;

        virtual void Maximize() = 0;
        virtual void Minimize() = 0;
        virtual void Restore() = 0;
    };
    
} // namespace MCT