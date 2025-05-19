#include "WB_Device/include/DeviceInstance.h"

using Microsoft::WRL::ComPtr;

DEVICE_API ComPtr<IDXGIFactory4> &WB::DXGIFactory()
{
    static ComPtr<IDXGIFactory4> factory;
    return factory;
}

DEVICE_API ComPtr<ID3D12Device4> &WB::DX12Device()
{
    static ComPtr<ID3D12Device4> device;
    return device;
}

DEVICE_API D3D_FEATURE_LEVEL &WB::FeatureLevel()
{
    static D3D_FEATURE_LEVEL featureLevel;
    return featureLevel;
}

DEVICE_API ComPtr<ID3D12CommandQueue> &WB::CommandQueue()
{
    static ComPtr<ID3D12CommandQueue> commandQueue;
    return commandQueue;
}