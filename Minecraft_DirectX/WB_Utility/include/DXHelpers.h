#pragma once

#include "WB_Utility/include/Config.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>

namespace WB
{
    /*******************************************************************************************************************
     * Device Instance
    /******************************************************************************************************************/

    UTILITY_API void CreateDX12Factory(Microsoft::WRL::ComPtr<IDXGIFactory4>& factory);

    UTILITY_API void CreateDX12Device
    (
        Microsoft::WRL::ComPtr<ID3D12Device4>& device, D3D_FEATURE_LEVEL& dstFeatureLevel,
        Microsoft::WRL::ComPtr<IDXGIFactory4> factory
    );

    UTILITY_API void CreateCommandQueue
    (
        Microsoft::WRL::ComPtr<ID3D12CommandQueue>& commandQueue, Microsoft::WRL::ComPtr<ID3D12Device4> device
    );

    /*******************************************************************************************************************
     * Swap Chain
    /******************************************************************************************************************/

    UTILITY_API void CreateSwapChain
    (
        Microsoft::WRL::ComPtr<IDXGIFactory4> factory, Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue,
        const UINT& frameCount,
        const UINT& clientWidth, const UINT& clientHeight, HWND hWnd,
        Microsoft::WRL::ComPtr<IDXGISwapChain3>& swapChain, int& frameIndex
    );

    UTILITY_API void ResizeSwapChain
    (
        const UINT& frameCount, const UINT& clientWidth, const UINT& clientHeight,
        Microsoft::WRL::ComPtr<IDXGISwapChain3> swapChain, int& frameIndex
    );

    /*******************************************************************************************************************
     * Render Target
    /******************************************************************************************************************/

    UTILITY_API void CreateRenderTargetViewHeap
    (
        Microsoft::WRL::ComPtr<ID3D12Device4> device, const UINT& frameCount,
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& rtvHeap, UINT& rtvDescriptorSize
    );

    UTILITY_API void CreateRenderTargetView
    (
        Microsoft::WRL::ComPtr<ID3D12Device4> device, 
        const UINT& frameCount, Microsoft::WRL::ComPtr<IDXGISwapChain3> swapChain,
        Microsoft::WRL::ComPtr<ID3D12Resource>* renderTargets,
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap, UINT rtvDescriptorSize
    );

    /*******************************************************************************************************************
     * Command Allocator
    /******************************************************************************************************************/

    UTILITY_API void CreateCommandAllocator
    (
        Microsoft::WRL::ComPtr<ID3D12Device4> device, const UINT& frameCount,
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator>* commandAllocator
    );

    /*******************************************************************************************************************
     * Depth Stencil
    /******************************************************************************************************************/

    UTILITY_API void CreateDepthStencil
    (
        Microsoft::WRL::ComPtr<ID3D12Device4> device, const UINT& clientWidth, const UINT& clientHeight,
        Microsoft::WRL::ComPtr<ID3D12Resource>& depthStencil
    );

    UTILITY_API void CreateDepthStencilViewHeap
    (
        Microsoft::WRL::ComPtr<ID3D12Device4> device, const UINT& depthStencilCount,
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& dsvHeap
    );

    UTILITY_API void CreateDepthStencilView
    (
        Microsoft::WRL::ComPtr<ID3D12Device4> device,
        Microsoft::WRL::ComPtr<ID3D12Resource> depthStencil, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap
    );

    /*******************************************************************************************************************
     * Viewport and Scissor Rect
    /******************************************************************************************************************/

    UTILITY_API void CreateViewport
    (
        D3D12_VIEWPORT& viewport, const UINT& clientWidth, const UINT& clientHeight
    );

    UTILITY_API void CreateScissorRect
    (
        D3D12_RECT& scissorRect, const UINT& clientWidth, const UINT& clientHeight
    );

} // namespace WB