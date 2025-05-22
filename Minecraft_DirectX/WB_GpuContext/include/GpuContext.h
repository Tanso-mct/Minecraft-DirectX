#pragma once

#include "WB_GpuContext/include/Config.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>

namespace WB
{
    class GPU_CONTEXT_API GpuContext
    {
    public:
        /***************************************************************************************************************
         * Constructor & Destructor
        /**************************************************************************************************************/

        GpuContext() = default;
        ~GpuContext() = default;

        /***************************************************************************************************************
         * DirectX12 related
        /**************************************************************************************************************/

        static void Create();
        static void ThrowIfNotCreated();

        static Microsoft::WRL::ComPtr<IDXGIFactory4>& DXGIFactory();
        static Microsoft::WRL::ComPtr<ID3D12Device4>& DX12Device();
        static D3D_FEATURE_LEVEL& FeatureLevel();
        static Microsoft::WRL::ComPtr<ID3D12CommandQueue>& CommandQueue();
    };
}