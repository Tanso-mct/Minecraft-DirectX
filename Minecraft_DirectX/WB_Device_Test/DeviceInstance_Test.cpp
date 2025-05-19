#include "pch.h"

#include "WB_Device/include/DeviceInstance.h"
#pragma comment(lib, "WB_Device.lib")

#include "WB_Utility/include/DXHelpers.h"
#pragma comment(lib, "WB_Utility.lib")

TEST(DeviceInstance, Factory)
{
    {
        Microsoft::WRL::ComPtr<IDXGIFactory4> &factory = WB::DXGIFactory();
        WB::CreateDX12Factory(factory);
    }

    EXPECT_NE(WB::DXGIFactory().GetAddressOf(), nullptr);
}

TEST(DeviceInstance, Device)
{
    {
        Microsoft::WRL::ComPtr<IDXGIFactory4> &factory = WB::DXGIFactory();
        WB::CreateDX12Factory(factory);

        Microsoft::WRL::ComPtr<ID3D12Device4> &device = WB::DX12Device();
        D3D_FEATURE_LEVEL &featureLevel = WB::FeatureLevel();
        WB::CreateDX12Device(device, featureLevel, factory);
    }

    EXPECT_NE(WB::DX12Device().GetAddressOf(), nullptr);
}

TEST(DeviceInstance, CommandQueue)
{
    {
        Microsoft::WRL::ComPtr<IDXGIFactory4> &factory = WB::DXGIFactory();
        WB::CreateDX12Factory(factory);

        Microsoft::WRL::ComPtr<ID3D12Device4> &device = WB::DX12Device();
        D3D_FEATURE_LEVEL &featureLevel = WB::FeatureLevel();
        WB::CreateDX12Device(device, featureLevel, factory);

        Microsoft::WRL::ComPtr<ID3D12CommandQueue> &commandQueue = WB::CommandQueue();
        WB::CreateCommandQueue(commandQueue, device);
    }

    EXPECT_NE(WB::CommandQueue().GetAddressOf(), nullptr);
}