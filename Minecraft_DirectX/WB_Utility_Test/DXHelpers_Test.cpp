#include "pch.h"

#include "WB_Utility/include/DXHelpers.h"
#pragma comment(lib, "WB_Utility.lib")

TEST(DXHelpers, CreateDX12Factory)
{
    Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
    WB::CreateDX12Factory(factory);

    EXPECT_NE(factory.GetAddressOf(), nullptr);
}

TEST(DXHelpers, CreateDX12Device)
{
    Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
    WB::CreateDX12Factory(factory);

    Microsoft::WRL::ComPtr<ID3D12Device4> device;
    D3D_FEATURE_LEVEL dstFeatureLevel;
    WB::CreateDX12Device(device, dstFeatureLevel, factory);

    EXPECT_NE(device.GetAddressOf(), nullptr);
}

TEST(DXHelpers, CreateCommandQueue)
{
    Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
    WB::CreateDX12Factory(factory);

    Microsoft::WRL::ComPtr<ID3D12Device4> device;
    D3D_FEATURE_LEVEL dstFeatureLevel;
    WB::CreateDX12Device(device, dstFeatureLevel, factory);

    Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
    WB::CreateCommandQueue(commandQueue, device);

    EXPECT_NE(commandQueue.GetAddressOf(), nullptr);
}