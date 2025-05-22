#include "WB_Utility/include/DXHelpers.h"

#include "WB_Utility/include/ErrorHandling.h"

using Microsoft::WRL::ComPtr;

#include "ExternalLibrary/DXHeaders/d3dx12.h"
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

UTILITY_API void WB::CreateDX12Factory(Microsoft::WRL::ComPtr<IDXGIFactory4>& factory)
{
    UINT dxgiFactoryFlags = 0;

#ifndef NDEBUG
    {
        ComPtr<ID3D12Debug> debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.GetAddressOf()))))
        {
            debugController->EnableDebugLayer();

            // Enable additional debug layers.
            dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;

            ComPtr<ID3D12Debug1> spDebugController1;
            debugController->QueryInterface(IID_PPV_ARGS(spDebugController1.GetAddressOf()));
            spDebugController1->SetEnableGPUBasedValidation(true);
        }
    }
#endif

    HRESULT hr = CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(factory.GetAddressOf()));
    if (FAILED(hr))
    {
        std::string err = WB::HrToString(hr);
        WB::MessageBoxError("CreateDX12Factory", err);
    }
}

UTILITY_API void WB::CreateDX12Device
(
    Microsoft::WRL::ComPtr<ID3D12Device4>& device, D3D_FEATURE_LEVEL& dstFeatureLevel,
    Microsoft::WRL::ComPtr<IDXGIFactory4> factory
){
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_12_2,
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    // Get Hardware Adapter and Create Device
    ComPtr<IDXGIAdapter1> adapter;

    ComPtr<IDXGIFactory6> factory6;
    HRESULT hr = E_FAIL;

    if (SUCCEEDED(factory->QueryInterface(IID_PPV_ARGS(factory6.GetAddressOf()))))
    {
        // Find a high spec adapter as it is compatible with Factory6.
        for (
            UINT adapterIndex = 0;
            SUCCEEDED(factory6->EnumAdapterByGpuPreference
            ( // Acquire adapters from factory one by one for GPU function rides
                adapterIndex,
                DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
                IID_PPV_ARGS(adapter.GetAddressOf())
            ));
            ++adapterIndex
        ){
            DXGI_ADAPTER_DESC1 desc;
            adapter->GetDesc1(&desc);

            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;

            hr = E_FAIL;

            for (UINT featureLevel = 0; featureLevel < numFeatureLevels; featureLevel++)
            {
                dstFeatureLevel = featureLevels[featureLevel];
                if (SUCCEEDED(hr = D3D12CreateDevice(adapter.Get(), dstFeatureLevel, _uuidof(ID3D12Device), &device)))
                {
                    break;
                }
            }

            if (SUCCEEDED(hr))
                break;
        }
    }

    if (device.Get() == nullptr)
    {
        // Find one that works with all adapters.
        for (UINT adapterIndex = 0; SUCCEEDED(factory->EnumAdapters1(adapterIndex, &adapter)); ++adapterIndex)
        {
            DXGI_ADAPTER_DESC1 desc;
            adapter->GetDesc1(&desc);

            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;

            hr = E_FAIL;

            for (UINT featureLevel = 0; featureLevel < numFeatureLevels; featureLevel++)
            {
                dstFeatureLevel = featureLevels[featureLevel];
                if (SUCCEEDED(hr = D3D12CreateDevice(adapter.Get(), dstFeatureLevel, _uuidof(ID3D12Device), &device)))
                {
                    break;
                }

            }

            if (SUCCEEDED(hr))
                break;
        }
    }

    if (FAILED(hr))
    {
        std::string err = WB::HrToString(hr);
        WB::MessageBoxError("CreateDX12Device", err);
    }
}

UTILITY_API void WB::CreateCommandQueue
(
    Microsoft::WRL::ComPtr<ID3D12CommandQueue>& commandQueue, Microsoft::WRL::ComPtr<ID3D12Device4> device
){
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    HRESULT hr = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(commandQueue.GetAddressOf()));

    if (FAILED(hr))
    {
        std::string err = WB::HrToString(hr);
        WB::MessageBoxError("CreateCommandQueue", err);
    }
}

UTILITY_API void WB::CreateSwapChain
(
    Microsoft::WRL::ComPtr<IDXGIFactory4> factory, Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue,
    const UINT &frameCount, 
    const UINT &clientWidth, const UINT &clientHeight, HWND hWnd, 
    Microsoft::WRL::ComPtr<IDXGISwapChain3> &swapChain, int &frameIndex
){
    HRESULT hr = E_FAIL;

    DXGI_SWAP_CHAIN_DESC1 desc = {};
    desc.BufferCount = frameCount;
    desc.Width = clientWidth;
    desc.Height = clientHeight;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.SampleDesc.Count = 1;

    ComPtr<IDXGISwapChain1> swapChain1;

    hr = factory->CreateSwapChainForHwnd
    (
        commandQueue.Get(),
        hWnd,
        &desc,
        nullptr,
        nullptr,
        &swapChain1
    );
    if (FAILED(hr))
    {
        std::string err = "CreateSwapChain : Failed to create swap chain";
        err += WB::HrToString(hr);
        WB::MessageBoxError("DXHelpers", err);
    }

    hr = swapChain1.As(&(swapChain));
    if (FAILED(hr))
    {
        std::string err = "CreateSwapChain : Failed to create swap chain";
        err += WB::HrToString(hr);
        WB::MessageBoxError("DXHelpers", err);
    }

    // Get the current back buffer index
    frameIndex = swapChain->GetCurrentBackBufferIndex();
}

UTILITY_API void WB::ResizeSwapChain
(
    const UINT &frameCount, const UINT &clientWidth, const UINT &clientHeight, 
    Microsoft::WRL::ComPtr<IDXGISwapChain3> swapChain, int &frameIndex
){
    HRESULT hr = swapChain->ResizeBuffers
    (
        frameCount, clientWidth, clientHeight,
        DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
    );
    if (FAILED(hr))
    {
        std::string err = "ResizeSwapChain : Failed to resize swap chain";
        err += WB::HrToString(hr);
        WB::MessageBoxError("DXHelpers", err);
    }

    // Get the current back buffer index
    frameIndex = swapChain->GetCurrentBackBufferIndex();
}

UTILITY_API void WB::GetRenderTargetsFromSwapChain
(
    const UINT &frameCount, 
    Microsoft::WRL::ComPtr<IDXGISwapChain3> swapChain, Microsoft::WRL::ComPtr<ID3D12Resource> *renderTargets
){
    HRESULT hr = E_FAIL;

    for (UINT i = 0; i < frameCount; i++)
    {
        hr = swapChain->GetBuffer(i, IID_PPV_ARGS(renderTargets[i].GetAddressOf()));
        if (FAILED(hr))
        {
            std::string err = "GetRenderTargetsFromSwapChain : Failed to get back buffer";
            err += WB::HrToString(hr);
            WB::MessageBoxError("DXHelpers", err);
        }

        std::wstring name = L"RenderTarget:" + std::to_wstring(i);
        hr = renderTargets[i]->SetName(name.c_str());
        if (FAILED(hr))
        {
            std::string err = "GetRenderTargetsFromSwapChain : Failed to set render target name";
            err += WB::HrToString(hr);
            WB::MessageBoxError("DXHelpers", err);
        }
    }
}

UTILITY_API void WB::CreateRenderTargetViewHeap
(
    Microsoft::WRL::ComPtr<ID3D12Device4> device, 
    const UINT &frameCount, 
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& rtvHeap, UINT &rtvDescriptorSize
){
    HRESULT hr = E_FAIL;

    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.NumDescriptors = frameCount;
    heapDesc.NodeMask = 0;
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    
    hr = device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(rtvHeap.GetAddressOf()));
    if (FAILED(hr))
    {
        std::string err = "CreateRenderTargetViewHeap : Failed to create render target view heap";
        err += WB::HrToString(hr);
        WB::MessageBoxError("DXHelpers", err);
    }

    // Get the render target view descriptor size
    rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
}

UTILITY_API void WB::CreateRenderTargetView
(
    Microsoft::WRL::ComPtr<ID3D12Device4> device, 
    const UINT &frameCount, Microsoft::WRL::ComPtr<ID3D12Resource> *renderTargets, 
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap, UINT rtvDescriptorSize
){
    HRESULT hr = E_FAIL;

    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart());

    for (UINT i = 0; i < frameCount; i++)
    {
        device->CreateRenderTargetView(renderTargets[i].Get(), nullptr, rtvHandle);
        rtvHandle.Offset(1, rtvDescriptorSize);
    }
}

UTILITY_API void WB::CreateCommandAllocator
(
    Microsoft::WRL::ComPtr<ID3D12Device4> device, const UINT &frameCount, 
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator>* commandAllocators
){
    HRESULT hr = E_FAIL;
    
    for (UINT i = 0; i < frameCount; i++)
    {
        hr = device->CreateCommandAllocator
        (
            D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(commandAllocators[i].GetAddressOf())
        );
        if (FAILED(hr))
        {
            std::string err = "CreateCommandAllocator : Failed to create command allocator";
            err += WB::HrToString(hr);
            WB::MessageBoxError("DXHelpers", err);
        }
    }
}

UTILITY_API void WB::CreateDepthStencilViewHeap
(
    Microsoft::WRL::ComPtr<ID3D12Device4> device, 
    const UINT &depthStencilCount, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& dsvHeap
){
    HRESULT hr = E_FAIL;

    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.NumDescriptors = depthStencilCount;
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    hr = device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(dsvHeap.GetAddressOf()));
    if (FAILED(hr))
    {
        std::string err = "CreateDepthStencilViewHeap : Failed to create depth stencil view heap";
        err += WB::HrToString(hr);
        WB::MessageBoxError("DXHelpers", err);
    }
}

UTILITY_API void WB::CreateDepthStencil
(
    Microsoft::WRL::ComPtr<ID3D12Device4> device, const UINT &clientWidth, const UINT &clientHeight, 
    Microsoft::WRL::ComPtr<ID3D12Resource> &depthStencil
){
    HRESULT hr = E_FAIL;

    D3D12_CLEAR_VALUE clearValue = {};
    clearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    clearValue.DepthStencil.Depth = 1.0f;
    clearValue.DepthStencil.Stencil = 0;

    const CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_DEFAULT);
    const CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Tex2D
    (
        DXGI_FORMAT_D24_UNORM_S8_UINT,
        clientWidth, clientHeight,
        1, 0, 1, 0,
        D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
    );

    hr = device->CreateCommittedResource
    (
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_DEPTH_WRITE,
        &clearValue,
        IID_PPV_ARGS(depthStencil.GetAddressOf())
    );
    if (FAILED(hr))
    {
        std::string err = "CreateDepthStencil : Failed to create depth stencil view";
        err += WB::HrToString(hr);
        WB::MessageBoxError("DXHelpers", err);
    }

    std::wstring name = L"DepthStencil";
    hr = depthStencil->SetName(name.c_str());
    if (FAILED(hr))
    {
        std::string err = "CreateDepthStencil : Failed to set depth stencil name";
        err += WB::HrToString(hr);
        WB::MessageBoxError("DXHelpers", err);
    }
}

UTILITY_API void WB::CreateDepthStencilView
(
    Microsoft::WRL::ComPtr<ID3D12Device4> device, 
    Microsoft::WRL::ComPtr<ID3D12Resource> depthStencil, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap
){
    D3D12_DEPTH_STENCIL_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
    desc.Flags = D3D12_DSV_FLAG_NONE;

    device->CreateDepthStencilView
    (
        depthStencil.Get(), &desc, 
        dsvHeap->GetCPUDescriptorHandleForHeapStart()
    );
}

UTILITY_API void WB::CreateViewport(D3D12_VIEWPORT &viewport, const UINT &clientWidth, const UINT &clientHeight)
{
    viewport.Width = static_cast<float>(clientWidth);
    viewport.Height = static_cast<float>(clientHeight);
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;
}

UTILITY_API void WB::CreateScissorRect(D3D12_RECT &scissorRect, const UINT &clientWidth, const UINT &clientHeight)
{
    scissorRect.top = 0;
    scissorRect.bottom = clientHeight;
    scissorRect.left = 0;
    scissorRect.right = clientWidth;
}