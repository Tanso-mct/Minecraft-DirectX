#include "pch.h"

#include "WB_Device/include/DeviceInstance.h"
#pragma comment(lib, "WB_Device.lib")

#include "WB_Utility/include/DXHelpers.h"
#pragma comment(lib, "WB_Utility.lib")

using Microsoft::WRL::ComPtr;

TEST(DeviceInstance, Factory)
{
    {
        ComPtr<IDXGIFactory4> &factory = WB::DXGIFactory();
        if (factory.GetAddressOf() == nullptr) WB::CreateDX12Factory(factory);
    }

    EXPECT_NE(WB::DXGIFactory().GetAddressOf(), nullptr);
}

TEST(DeviceInstance, Device)
{
    {
        ComPtr<IDXGIFactory4> &factory = WB::DXGIFactory();
        if (factory.GetAddressOf() == nullptr) WB::CreateDX12Factory(factory);

        ComPtr<ID3D12Device4> &device = WB::DX12Device();
        D3D_FEATURE_LEVEL &featureLevel = WB::FeatureLevel();
        if (device.GetAddressOf() == nullptr) WB::CreateDX12Device(device, featureLevel, factory);
    }

    EXPECT_NE(WB::DX12Device().GetAddressOf(), nullptr);
}

TEST(DeviceInstance, CommandQueue)
{
    {
        ComPtr<IDXGIFactory4> &factory = WB::DXGIFactory();
        if (factory.GetAddressOf() == nullptr) WB::CreateDX12Factory(factory);

        ComPtr<ID3D12Device4> &device = WB::DX12Device();
        D3D_FEATURE_LEVEL &featureLevel = WB::FeatureLevel();
        if (device.GetAddressOf() == nullptr) WB::CreateDX12Device(device, featureLevel, factory);

        ComPtr<ID3D12CommandQueue> &commandQueue = WB::CommandQueue();
        if (commandQueue.GetAddressOf() == nullptr) WB::CreateCommandQueue(commandQueue, device);
    }

    EXPECT_NE(WB::CommandQueue().GetAddressOf(), nullptr);
}