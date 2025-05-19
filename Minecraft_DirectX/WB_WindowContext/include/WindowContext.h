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
        /*******************************************************************************************************************
         * Windows related
        /******************************************************************************************************************/

        HWND _hWnd = nullptr;
        HINSTANCE _hInstance = nullptr;
        HWND _hWndParent = nullptr;

        std::wstring _name = L"Window";
        UINT _posX = CW_USEDEFAULT;
        UINT _posY = CW_USEDEFAULT;

        UINT _width = 800;
        UINT _height = 600;

        UINT _clientWidth = 800;
        UINT _clientHeight = 600;

        bool _isFocus = false;
        bool _isMaximized = false;
        bool _isMinimized = false;

        /*******************************************************************************************************************
         * DirectX12 related
        /******************************************************************************************************************/

        Microsoft::WRL::ComPtr<IDXGISwapChain3> _swapChain = nullptr;
        static const UINT _frameCount = 2;
        int _frameIndex = 0;

        Microsoft::WRL::ComPtr<ID3D12Resource> _renderTargets[_frameCount] = { nullptr };
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> _commandAllocators[_frameCount] = { nullptr };
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _rtvHeap = nullptr;
        UINT _rtvDescriptorSize = 0;

        static const UINT _depthStencilCount = 1;
        Microsoft::WRL::ComPtr<ID3D12Resource> _depthStencil = nullptr;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _dsvHeap = nullptr;

        D3D12_VIEWPORT _viewport;
        D3D12_RECT _scissorRect;

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
        void Resize() override;

        bool& IsFocus() override { return _isFocus; }

        void Maximized() override;
        void Minimized() override;
        void Restored() override;

        void SetPos(int x, int y, int width, int height, UINT flags) override;

        void Maximize() override;
        void Minimize() override;
        void Restore() override;
    };
}