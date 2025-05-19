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
        int posX = CW_USEDEFAULT;
        int posY = CW_USEDEFAULT;
        int width = 800;
        int height = 600;
    };

    class IWindowContext
    {
    public:
        virtual ~IWindowContext() = default;

        virtual void Initialize(const WindowDesc& desc) = 0;

        virtual void Create(WNDCLASSEX& wc) = 0;
        virtual void Release() = 0;

        virtual void Resize(int width, int height) = 0;

        virtual void Show() = 0;
        virtual void Hide() = 0;
    };
    
} // namespace MCT