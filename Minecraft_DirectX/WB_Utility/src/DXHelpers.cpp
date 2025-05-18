#include "WB_Utility/include/DXHelpers.h"

#include "WB_Utility/include/ErrorHandling.h"

using Microsoft::WRL::ComPtr;

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

    if (hr == E_FAIL)
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