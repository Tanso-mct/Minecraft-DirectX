#pragma once

#include "WB_WindowContext/include/Config.h"
#include "Interface/WindowContext.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl/client.h>

namespace WB
{
    class WINDOW_CONTEXT_API WindowContext : public IWindowContext
    {
    private:
        HWND _hWnd = nullptr;
        HINSTANCE _hInstance = nullptr;
        HWND _hWndParent = nullptr;

        std::wstring _name = L"Window";
        int _posX = CW_USEDEFAULT;
        int _posY = CW_USEDEFAULT;
        int _width = 800;
        int _height = 600;

        bool _isFocus = false;
        bool _isMaximized = false;
        bool _isMinimized = false;

        Microsoft::WRL::ComPtr<IDXGISwapChain3> _swapChain = nullptr;
        int _frameIndex = 0;

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
        /**************************************************************************************************************/

        WindowContext();
        ~WindowContext() override;

        /***************************************************************************************************************
         * IWindowContext interface implementation
        /**************************************************************************************************************/

        void Initialize(const WindowDesc& desc) override;

        void Create(WNDCLASSEX& wc) override;
        void Release() override;

        void Resize(int width, int height) override;

        void Show() override;
        void Hide() override;
    };
}