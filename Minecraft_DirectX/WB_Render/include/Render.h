#pragma once

#include "WB_Render/include/Config.h"

#include "Interface/Render.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>

namespace WB
{
    class RENDER_API Render : public IRender
    {
    public:
        /***************************************************************************************************************
         * Constructor & Destructor
        /**************************************************************************************************************/

        Render() = default;
        ~Render() override = default;

        /***************************************************************************************************************
         * Static device instance functions
        /**************************************************************************************************************/

        static Microsoft::WRL::ComPtr<IDXGIFactory4>& DXGIFactory();
        static Microsoft::WRL::ComPtr<ID3D12Device4>& DX12Device();
        static D3D_FEATURE_LEVEL& FeatureLevel();
        static Microsoft::WRL::ComPtr<ID3D12CommandQueue>& CommandQueue();
    };
}