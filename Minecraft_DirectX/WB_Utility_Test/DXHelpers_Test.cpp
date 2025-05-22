#include "pch.h"

#include "WB_Utility_Test/WindowProc.h"

#include "WB_Utility/include/DXHelpers.h"
#pragma comment(lib, "WB_Utility.lib")

using Microsoft::WRL::ComPtr;

TEST(DXHelpers, CreateDX12Factory)
{
    ComPtr<IDXGIFactory4> factory;
    WB::CreateDX12Factory(factory);

    EXPECT_NE(factory.GetAddressOf(), nullptr);
}

TEST(DXHelpers, CreateDX12Device)
{
    ComPtr<IDXGIFactory4> factory;
    WB::CreateDX12Factory(factory);

    ComPtr<ID3D12Device4> device;
    D3D_FEATURE_LEVEL dstFeatureLevel;
    WB::CreateDX12Device(device, dstFeatureLevel, factory);

    EXPECT_NE(device.GetAddressOf(), nullptr);
}

TEST(DXHelpers, CreateCommandQueue)
{
    ComPtr<IDXGIFactory4> factory;
    WB::CreateDX12Factory(factory);

    ComPtr<ID3D12Device4> device;
    D3D_FEATURE_LEVEL dstFeatureLevel;
    WB::CreateDX12Device(device, dstFeatureLevel, factory);

    ComPtr<ID3D12CommandQueue> commandQueue;
    WB::CreateCommandQueue(commandQueue, device);

    EXPECT_NE(commandQueue.GetAddressOf(), nullptr);
}

TEST(DXHelpers, RelatedCreateWindow)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = L"RelatedCreateWindow";

    HWND hWnd = nullptr;

    // Register the window class
    if (!RegisterClassEx(&wc))
    {
        FAIL() << "Failed to register window class";
    }

    // Create a window
    hWnd = CreateWindow
    (
        wc.lpszClassName,
        L"RelatedCreateWindow",
        wc.style,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        nullptr,
        nullptr,
        wc.hInstance,
        nullptr
    );

    if (!hWnd)
    {
        FAIL() << "Failed to create window";
    }

    // Show the window
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    // Create a DX12 factory
    ComPtr<IDXGIFactory4> factory;
    WB::CreateDX12Factory(factory);
    EXPECT_NE(factory.GetAddressOf(), nullptr);

    // Create a DX12 device
    ComPtr<ID3D12Device4> device;
    D3D_FEATURE_LEVEL dstFeatureLevel;
    WB::CreateDX12Device(device, dstFeatureLevel, factory);
    EXPECT_NE(device.GetAddressOf(), nullptr);

    // Create a command queue
    ComPtr<ID3D12CommandQueue> commandQueue;
    WB::CreateCommandQueue(commandQueue, device);
    EXPECT_NE(commandQueue.GetAddressOf(), nullptr);

    // Get the client rect
    RECT rect;
    GetClientRect(hWnd, &rect);
    UINT clientWidth = rect.right - rect.left;
    UINT clientHeight = rect.bottom - rect.top;

    // Create a swap chain
    ComPtr<IDXGISwapChain3> swapChain;
    int frameIndex = 0;
    const UINT frameCount = 2;
    WB::CreateSwapChain(factory, commandQueue, frameCount, clientWidth, clientHeight, hWnd, swapChain, frameIndex);
    EXPECT_NE(swapChain.GetAddressOf(), nullptr);

    // Get the render targets from the swap chain
    ComPtr<ID3D12Resource> renderTargets[frameCount] = { nullptr };
    WB::GetRenderTargetsFromSwapChain(frameCount, swapChain, renderTargets);
    for (UINT i = 0; i < frameCount; ++i)
    {
        EXPECT_NE(renderTargets[i].GetAddressOf(), nullptr);
    }

    // Create a render target view heap
    ComPtr<ID3D12DescriptorHeap> rtvHeap;
    UINT rtvDescriptorSize = 0;
    WB::CreateRenderTargetViewHeap(device, 2, rtvHeap, rtvDescriptorSize);
    EXPECT_NE(rtvHeap.GetAddressOf(), nullptr);

    // Create render targets
    WB::CreateRenderTargetView(device, frameCount, renderTargets, rtvHeap, rtvDescriptorSize);

    // Create a command allocator
    ComPtr<ID3D12CommandAllocator> commandAllocators[frameCount] = { nullptr };
    WB::CreateCommandAllocator(device, frameCount, commandAllocators);
    for (UINT i = 0; i < frameCount; ++i)
    {
        EXPECT_NE(commandAllocators[i].GetAddressOf(), nullptr);
    }

    // Create a depth stencil
    ComPtr<ID3D12Resource> depthStencil;
    WB::CreateDepthStencil(device, clientWidth, clientHeight, depthStencil);
    EXPECT_NE(depthStencil.GetAddressOf(), nullptr);

    // Create a depth stencil view heap
    ComPtr<ID3D12DescriptorHeap> dsvHeap;
    const UINT depthStencilCount = 1;
    WB::CreateDepthStencilViewHeap(device, depthStencilCount, dsvHeap);
    EXPECT_NE(dsvHeap.GetAddressOf(), nullptr);

    // Create a depth stencil view
    WB::CreateDepthStencilView(device, depthStencil, dsvHeap);

    // Create a viewport
    D3D12_VIEWPORT viewport;
    WB::CreateViewport(viewport, clientWidth, clientHeight);

    // Create a scissor rect
    D3D12_RECT scissorRect;
    WB::CreateScissorRect(scissorRect, clientWidth, clientHeight);

    // Destroy the window
    DestroyWindow(hWnd);
}

TEST(DXHelpers, RelatedResizeWindows)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = L"RelatedResizeWindows";

    HWND hWnd = nullptr;

    // Register the window class
    if (!RegisterClassEx(&wc))
    {
        FAIL() << "Failed to register window class";
    }

    // Create a window
    hWnd = CreateWindow
    (
        wc.lpszClassName,
        L"RelatedResizeWindows",
        wc.style,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        nullptr,
        nullptr,
        wc.hInstance,
        nullptr
    );

    if (!hWnd)
    {
        FAIL() << "Failed to create window";
    }

    // Show the window
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    // Create a DX12 factory
    ComPtr<IDXGIFactory4> factory;
    WB::CreateDX12Factory(factory);
    EXPECT_NE(factory.GetAddressOf(), nullptr);

    // Create a DX12 device
    ComPtr<ID3D12Device4> device;
    D3D_FEATURE_LEVEL dstFeatureLevel;
    WB::CreateDX12Device(device, dstFeatureLevel, factory);
    EXPECT_NE(device.GetAddressOf(), nullptr);

    // Create a command queue
    ComPtr<ID3D12CommandQueue> commandQueue;
    WB::CreateCommandQueue(commandQueue, device);
    EXPECT_NE(commandQueue.GetAddressOf(), nullptr);

    // Get the client rect
    RECT rect;
    GetClientRect(hWnd, &rect);
    UINT clientWidth = rect.right - rect.left;
    UINT clientHeight = rect.bottom - rect.top;

    // Create a swap chain
    ComPtr<IDXGISwapChain3> swapChain;
    int frameIndex = 0;
    const UINT frameCount = 2;
    WB::CreateSwapChain(factory, commandQueue, frameCount, clientWidth, clientHeight, hWnd, swapChain, frameIndex);
    EXPECT_NE(swapChain.GetAddressOf(), nullptr);

    // Get the render targets from the swap chain
    ComPtr<ID3D12Resource> renderTargets[frameCount] = { nullptr };
    WB::GetRenderTargetsFromSwapChain(frameCount, swapChain, renderTargets);
    for (UINT i = 0; i < frameCount; ++i)
    {
        EXPECT_NE(renderTargets[i].GetAddressOf(), nullptr);
    }

    // Create a render target view heap
    ComPtr<ID3D12DescriptorHeap> rtvHeap;
    UINT rtvDescriptorSize = 0;
    WB::CreateRenderTargetViewHeap(device, 2, rtvHeap, rtvDescriptorSize);
    EXPECT_NE(rtvHeap.GetAddressOf(), nullptr);

    // Create render targets
    WB::CreateRenderTargetView(device, frameCount, renderTargets, rtvHeap, rtvDescriptorSize);

    // Create a command allocator
    ComPtr<ID3D12CommandAllocator> commandAllocators[frameCount] = { nullptr };
    WB::CreateCommandAllocator(device, frameCount, commandAllocators);
    for (UINT i = 0; i < frameCount; ++i)
    {
        EXPECT_NE(commandAllocators[i].GetAddressOf(), nullptr);
    }

    // Create a depth stencil
    ComPtr<ID3D12Resource> depthStencil;
    WB::CreateDepthStencil(device, clientWidth, clientHeight, depthStencil);
    EXPECT_NE(depthStencil.GetAddressOf(), nullptr);

    // Create a depth stencil view heap
    ComPtr<ID3D12DescriptorHeap> dsvHeap;
    const UINT depthStencilCount = 1;
    WB::CreateDepthStencilViewHeap(device, depthStencilCount, dsvHeap);
    EXPECT_NE(dsvHeap.GetAddressOf(), nullptr);

    // Create a depth stencil view
    WB::CreateDepthStencilView(device, depthStencil, dsvHeap);

    // Create a viewport
    D3D12_VIEWPORT viewport;
    WB::CreateViewport(viewport, clientWidth, clientHeight);

    // Create a scissor rect
    D3D12_RECT scissorRect;
    WB::CreateScissorRect(scissorRect, clientWidth, clientHeight);

    // Resize the window
    SetWindowPos(hWnd, nullptr, 0, 0, 100, 100, SWP_NOZORDER | SWP_NOMOVE);

    // Get the new client rect
    GetClientRect(hWnd, &rect);
    clientWidth = rect.right - rect.left;
    clientHeight = rect.bottom - rect.top;

    // Clear the render targets and depth stencil
    for (UINT i = 0; i < frameCount; i++)
    {
        if (renderTargets[i].GetAddressOf() != nullptr)
        {
            renderTargets[i].Reset();
            renderTargets[i] = nullptr;
        }
    }

    if (depthStencil.GetAddressOf() != nullptr)
    {
        depthStencil.Reset();
        depthStencil = nullptr;
    }

    // Resize the swap chain
    WB::ResizeSwapChain(frameCount, clientWidth, clientHeight, swapChain, frameIndex);
    EXPECT_NE(swapChain.GetAddressOf(), nullptr);

    // Get the render targets from the swap chain
    WB::GetRenderTargetsFromSwapChain(frameCount, swapChain, renderTargets);
    for (UINT i = 0; i < frameCount; ++i)
    {
        EXPECT_NE(renderTargets[i].GetAddressOf(), nullptr);
    }

    // Create render target views
    WB::CreateRenderTargetView(device, frameCount, renderTargets, rtvHeap, rtvDescriptorSize);

    // Create the depth stencil
    WB::CreateDepthStencil(device, clientWidth, clientHeight, depthStencil);
    EXPECT_NE(depthStencil.GetAddressOf(), nullptr);

    // Create the depth stencil view
    WB::CreateDepthStencilView(device, depthStencil, dsvHeap);

    // Create the viewport
    WB::CreateViewport(viewport, clientWidth, clientHeight);

    // Create the scissor rect
    WB::CreateScissorRect(scissorRect, clientWidth, clientHeight);

    // Destroy the window
    DestroyWindow(hWnd);
}