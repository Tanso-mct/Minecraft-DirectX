#include "WB_GpuContext/include/GpuContext.h"

#include "WB_GpuContext/include/Log.h"

#include "WB_Utility/include/DXHelpers.h"
#include "WB_Utility/include/ErrorHandling.h"
#pragma comment(lib, "WB_Utility.lib")

using Microsoft::WRL::ComPtr;

#include <string>

void WB::GpuContext::Create()
{
    if (DXGIFactory() == nullptr) WB::CreateDX12Factory(DXGIFactory());
    if (DX12Device() == nullptr) WB::CreateDX12Device(DX12Device(), FeatureLevel(), DXGIFactory());
    if (CommandQueue() == nullptr) WB::CreateCommandQueue(CommandQueue(), DX12Device());
}

void WB::GpuContext::ThrowIfNotCreated()
{
    if (DXGIFactory() == nullptr)
    {
        std::string err = WBGpuContext::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"DXGIFactory is null."}
        );
        WB::MessageBoxError(WBGpuContext::ConsoleLog()->GetName(), err);
    }

    if (DX12Device() == nullptr)
    {
        std::string err = WBGpuContext::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"DX12Device is null."}
        );
        WB::MessageBoxError(WBGpuContext::ConsoleLog()->GetName(), err);
    }

    if (CommandQueue() == nullptr)
    {
        std::string err = WBGpuContext::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"CommandQueue is null."}
        );
        WB::MessageBoxError(WBGpuContext::ConsoleLog()->GetName(), err);
    }
}

ComPtr<IDXGIFactory4> &WB::GpuContext::DXGIFactory()
{
    static ComPtr<IDXGIFactory4> factory = nullptr;
    return factory;
}

ComPtr<ID3D12Device4> &WB::GpuContext::DX12Device()
{
    static ComPtr<ID3D12Device4> device = nullptr;
    return device;
}

D3D_FEATURE_LEVEL &WB::GpuContext::FeatureLevel()
{
    static D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_12_1;
    return featureLevel;
}

ComPtr<ID3D12CommandQueue> &WB::GpuContext::CommandQueue()
{
    static ComPtr<ID3D12CommandQueue> commandQueue = nullptr;
    return commandQueue;
}