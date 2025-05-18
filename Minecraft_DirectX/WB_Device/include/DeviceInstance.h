#pragma once

#include "WB_Device/include/Config.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>

namespace WB
{
    DEVICE_API Microsoft::WRL::ComPtr<IDXGIFactory4>& DXGIFactory();
    DEVICE_API Microsoft::WRL::ComPtr<ID3D12Device4>& DX12Device();
    DEVICE_API D3D_FEATURE_LEVEL& FeatureLevel();
    DEVICE_API Microsoft::WRL::ComPtr<ID3D12CommandQueue>& CommandQueue();
}