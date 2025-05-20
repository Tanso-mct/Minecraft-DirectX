#include "WB_Render/include/Render.h"

Microsoft::WRL::ComPtr<IDXGIFactory4> &WB::Render::DXGIFactory()
{
    static Microsoft::WRL::ComPtr<IDXGIFactory4> factory = nullptr;
    return factory;
}

Microsoft::WRL::ComPtr<ID3D12Device4> &WB::Render::DX12Device()
{
    static Microsoft::WRL::ComPtr<ID3D12Device4> device = nullptr;
    return device;
}

D3D_FEATURE_LEVEL &WB::Render::FeatureLevel()
{
    static D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_12_1;
    return featureLevel;
}

Microsoft::WRL::ComPtr<ID3D12CommandQueue> &WB::Render::CommandQueue()
{
    static Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue = nullptr;
    return commandQueue;
}