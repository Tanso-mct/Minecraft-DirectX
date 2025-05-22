#include "WB_WindowContext/include/WindowContext.h"

#include "WB_WindowContext/include/Log.h"

#include "WB_Utility/include/WindowsHelpers.h"
#include "WB_Utility/include/DXHelpers.h"
#include "WB_Utility/include/ErrorHandling.h"
#pragma comment(lib, "WB_Utility.lib")

#include "WB_GpuContext/include/GpuContext.h"
#pragma comment(lib, "WB_GpuContext.lib")

using Microsoft::WRL::ComPtr;

#include "ExternalLibrary/DXHeaders/d3dx12.h"
#pragma comment(lib, "d3d12.lib")

WB::WindowContext::WindowContext()
{
#ifndef NDEBUG
    WBWindowContext::ConsoleLog()->Log({"WindowContext Constructor : Created window context"});
#endif
}

WB::WindowContext::~WindowContext()
{
    // Destroy window
    if (_hWnd != nullptr)
    {
        DestroyWindow(_hWnd);
        _hWnd = nullptr;
    }

#ifndef NDEBUG
    WBWindowContext::ConsoleLog()->Log({"WindowContext Destructor : Destroyed window context"});
#endif
}

void WB::WindowContext::Initialize(const WindowDesc &desc)
{
    _hInstance = desc.hInstance;
    _hWndParent = desc.hWndParent;

    _name = desc.name;
    _posX = desc.posX;
    _posY = desc.posY;
    _width = desc.width;
    _height = desc.height;

#ifndef NDEBUG
    WBWindowContext::ConsoleLog()->Log({"WindowContext Initialize : Initialized window context"});
#endif

}

void WB::WindowContext::Create(WNDCLASSEX &wc)
{
    HRESULT hr = E_FAIL;

    if (_isCreated)
    {
        WBWindowContext::ConsoleLog()->LogWrn({"WindowContext Create : Window already created"});
        return;
    }

    /*******************************************************************************************************************
     * Create and show the window
    /******************************************************************************************************************/

    WB::CreateWindowNotApi
    (
        _hWnd,
        _name.c_str(),
        _posX, _posY,
        _width, _height,
        _hWndParent,
        wc
    );

    WB::ShowWindowNotApi(_hWnd);

    
    /*******************************************************************************************************************
     * Get the client rect
    /******************************************************************************************************************/
    {
        RECT rect;
        GetClientRect(_hWnd, &rect);
        _clientWidth = rect.right - rect.left;
        _clientHeight = rect.bottom - rect.top;
    }

    /*******************************************************************************************************************
     * Check if the GpuContext is created
    /******************************************************************************************************************/
    WB::GpuContext::ThrowIfNotCreated();

    /*******************************************************************************************************************
     * Create the swap chain
    /******************************************************************************************************************/
    WB::CreateSwapChain
    (
        WB::GpuContext::DXGIFactory(), WB::GpuContext::CommandQueue(), _frameCount,
        _clientWidth, _clientHeight, _hWnd,
        _swapChain, _frameIndex
    );

    /*******************************************************************************************************************
     * Get the render targets from the swap chain
    /******************************************************************************************************************/
    WB::GetRenderTargetsFromSwapChain
    (
        _frameCount, _swapChain, _renderTargets
    );

    /*******************************************************************************************************************
     * Create the render target view heap
    /******************************************************************************************************************/
    WB::CreateRenderTargetViewHeap
    (
        WB::GpuContext::DX12Device(), _frameCount,
        _rtvHeap, _rtvDescriptorSize
    );

    /*******************************************************************************************************************
     * Create the render target views
    /******************************************************************************************************************/
    WB::CreateRenderTargetView
    (
        WB::GpuContext::DX12Device(), _frameCount,
        _renderTargets, _rtvHeap, _rtvDescriptorSize
    );

    /*******************************************************************************************************************
     * Create the command allocators
    /******************************************************************************************************************/
    WB::CreateCommandAllocator(WB::GpuContext::DX12Device(), _frameCount, _commandAllocators);

    /*******************************************************************************************************************
     * Create the depth stencil
    /******************************************************************************************************************/
    WB::CreateDepthStencil(WB::GpuContext::DX12Device(), _clientWidth, _clientHeight, _depthStencil);
    
    /*******************************************************************************************************************
     * Create the descriptor heap
    /******************************************************************************************************************/
    WB::CreateDepthStencilViewHeap(WB::GpuContext::DX12Device(), _depthStencilCount, _dsvHeap);

    /*******************************************************************************************************************
     * Create the depth stencil view
    /******************************************************************************************************************/
    WB::CreateDepthStencilView(WB::GpuContext::DX12Device(), _depthStencil, _dsvHeap);

    /*******************************************************************************************************************
     * Create the viewport
    /******************************************************************************************************************/
    WB::CreateViewport(_viewport, _clientWidth, _clientHeight);

    /*******************************************************************************************************************
     * Create the scissor rect
    /******************************************************************************************************************/
    WB::CreateScissorRect(_scissorRect, _clientWidth, _clientHeight);


    _isCreated = true;

#ifndef NDEBUG
    WBWindowContext::ConsoleLog()->Log({"WindowContext Create : Created window"});
#endif
}

void WB::WindowContext::Resize()
{
    HRESULT hr = E_FAIL;

    if (!_isCreated)
    {
        std::string err = WBWindowContext::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"Resize : Window context not created"}
        );
        WB::MessageBoxError(WBWindowContext::ConsoleLog()->GetName(), err);
        return;
    }

    /*******************************************************************************************************************
     * Get the client rect
    /******************************************************************************************************************/
    {
        RECT rect;
        GetClientRect(_hWnd, &rect);
        _clientWidth = rect.right - rect.left;
        _clientHeight = rect.bottom - rect.top;
    }

    /*******************************************************************************************************************
     * Clear the render targets and depth stencil
    /******************************************************************************************************************/

    {
        for (UINT i = 0; i < _frameCount; i++)
        {
            if (_renderTargets[i].GetAddressOf() != nullptr)
            {
                _renderTargets[i].Reset();
                _renderTargets[i] = nullptr;
            }
        }

        if (_depthStencil.GetAddressOf() != nullptr)
        {
            _depthStencil.Reset();
            _depthStencil = nullptr;
        }
    }

    /*******************************************************************************************************************
     * Resize the swap chain
    /******************************************************************************************************************/
    WB::ResizeSwapChain(_frameCount, _clientWidth, _clientHeight, _swapChain, _frameIndex);

    /*******************************************************************************************************************
     * Get the render targets from the swap chain
    /******************************************************************************************************************/
    WB::GetRenderTargetsFromSwapChain
    (
        _frameCount, _swapChain, _renderTargets
    );

    /*******************************************************************************************************************
     * Create the render target views
    /******************************************************************************************************************/
    WB::CreateRenderTargetView
    (
        WB::GpuContext::DX12Device(), _frameCount,
        _renderTargets, _rtvHeap, _rtvDescriptorSize
    );

    /*******************************************************************************************************************
     * Create the depth stencil
    /******************************************************************************************************************/
    WB::CreateDepthStencil(WB::GpuContext::DX12Device(), _clientWidth, _clientHeight, _depthStencil);

    /*******************************************************************************************************************
     * Create the depth stencil view
    /******************************************************************************************************************/
    WB::CreateDepthStencilView(WB::GpuContext::DX12Device(), _depthStencil, _dsvHeap);

    /*******************************************************************************************************************
     * Create the viewport
    /******************************************************************************************************************/
    WB::CreateViewport(_viewport, _clientWidth, _clientHeight);

    /*******************************************************************************************************************
     * Create the scissor rect
    /******************************************************************************************************************/
    WB::CreateScissorRect(_scissorRect, _clientWidth, _clientHeight);

    
#ifndef NDEBUG
    WBWindowContext::ConsoleLog()->Log({"WindowContext Resize : Resized window"});
#endif
}

void WB::WindowContext::Maximized()
{
    _isMaximized = true;
    _isMinimized = false;
    Resize();

#ifndef NDEBUG
    WBWindowContext::ConsoleLog()->Log({"WindowContext Maximized : Window maximized"});
#endif
}

void WB::WindowContext::Minimized()
{
    _isMaximized = false;
    _isMinimized = true;

#ifndef NDEBUG
    WBWindowContext::ConsoleLog()->Log({"WindowContext Minimized : Window minimized"});
#endif
}

void WB::WindowContext::Restored()
{
    _isMaximized = false;
    _isMinimized = false;
    Resize();

#ifndef NDEBUG
    WBWindowContext::ConsoleLog()->Log({"WindowContext Restored : Window restored"});
#endif
}

void WB::WindowContext::SetPos(int x, int y, int width, int height, UINT flags)
{
    if (!SetWindowPos(_hWnd, nullptr, x, y, width, height, flags))
    {
        std::string err = WBWindowContext::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"SetPos : Failed to set window position"}
        );
        WB::MessageBoxError(WBWindowContext::ConsoleLog()->GetName(), err);
    }

    if (!(flags & SWP_NOMOVE))
    {
        _posX = x;
        _posY = y;
    }

    if (!(flags & SWP_NOSIZE))
    {
        _width = width;
        _height = height;
    }

#ifndef NDEBUG
    WBWindowContext::ConsoleLog()->Log({"WindowContext SetPos : Set window position"});
#endif
}

void WB::WindowContext::Maximize()
{
    if (!ShowWindow(_hWnd, SW_MAXIMIZE))
    {
        std::string err = WBWindowContext::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"Maximize : Failed to maximize window"}
        );
        WB::MessageBoxError(WBWindowContext::ConsoleLog()->GetName(), err);
    }
}

void WB::WindowContext::Minimize()
{
    if (!ShowWindow(_hWnd, SW_MINIMIZE))
    {
        std::string err = WBWindowContext::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"Minimize : Failed to minimize window"}
        );
        WB::MessageBoxError(WBWindowContext::ConsoleLog()->GetName(), err);
    }
}

void WB::WindowContext::Restore()
{
    if (!ShowWindow(_hWnd, SW_RESTORE))
    {
        std::string err = WBWindowContext::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"Restore : Failed to restore window"}
        );
        WB::MessageBoxError(WBWindowContext::ConsoleLog()->GetName(), err);
    }
}