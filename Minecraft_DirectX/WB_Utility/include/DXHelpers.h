#pragma once

#include "WB_Utility/include/Config.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>

namespace WB
{
    UTILITY_API void CreateDX12Factory(Microsoft::WRL::ComPtr<IDXGIFactory4> &factory);

    UTILITY_API void CreateDX12Device
    (
        Microsoft::WRL::ComPtr<ID3D12Device4> &device, D3D_FEATURE_LEVEL &dstFeatureLevel,
        Microsoft::WRL::ComPtr<IDXGIFactory4> factory
    );

    UTILITY_API void CreateCommandQueue
    (
        Microsoft::WRL::ComPtr<ID3D12CommandQueue> &commandQueue, Microsoft::WRL::ComPtr<ID3D12Device4> device
    );
} // namespace WB