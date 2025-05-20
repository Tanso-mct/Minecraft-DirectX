#include "pch.h"

#include "WB_WindowContext/include/WindowContext.h"
#pragma comment(lib, "WB_WindowContext.lib")

#include "WB_Utility/include/WindowsHelpers.h"
#include "WB_Utility/include/DXHelpers.h"
#pragma comment(lib, "WB_Utility.lib")

#include "WB_Render/include/Render.h"
#pragma comment(lib, "WB_Render.lib")

#include <memory>

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_PAINT:
        // Returning DefWindowProc with WM_PAINT will stop the updating, so WM_PAINT is returned 0.
        break;

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}

TEST(WindowContext, Initialize)
{
    std::unique_ptr<WB::IWindowContext> windowContext = std::make_unique<WB::WindowContext>();

    {
        WB::WindowDesc desc;
        desc.hInstance = GetModuleHandle(nullptr);
        desc.hWndParent = nullptr;
        desc.name = L"WindowContext Initialize";

        windowContext->Initialize(desc);
    }
}

TEST(WindowContext, Create)
{
    std::unique_ptr<WB::IWindowContext> windowContext = std::make_unique<WB::WindowContext>();

    // Initialize
    {
        WB::WindowDesc desc;
        desc.hInstance = GetModuleHandle(nullptr);
        desc.hWndParent = nullptr;
        desc.name = L"WindowContext Create";

        windowContext->Initialize(desc);
    }

    // Create DXGIFactory
    if (WB::Render::DXGIFactory() == nullptr) 
        WB::CreateDX12Factory(WB::Render::DXGIFactory());

    // Create DX12Device
    if (WB::Render::DX12Device() == nullptr) 
        WB::CreateDX12Device(WB::Render::DX12Device(), WB::Render::FeatureLevel(), WB::Render::DXGIFactory());

    // Create CommandQueue
    if (WB::Render::CommandQueue() == nullptr) 
        WB::CreateCommandQueue(WB::Render::CommandQueue(), WB::Render::DX12Device());

    // Create
    {
        WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = L"WindowContext Create";

        windowContext->Create(wc);
    }

    // Destroy
    windowContext.reset();
}

TEST(WindowContext, Resize)
{
    std::unique_ptr<WB::IWindowContext> windowContext = std::make_unique<WB::WindowContext>();

    // Initialize
    {
        WB::WindowDesc desc;
        desc.hInstance = GetModuleHandle(nullptr);
        desc.hWndParent = nullptr;
        desc.name = L"WindowContext Resize";

        windowContext->Initialize(desc);
    }

    // Create DXGIFactory
    if (WB::Render::DXGIFactory() == nullptr) 
        WB::CreateDX12Factory(WB::Render::DXGIFactory());

    // Create DX12Device
    if (WB::Render::DX12Device() == nullptr) 
        WB::CreateDX12Device(WB::Render::DX12Device(), WB::Render::FeatureLevel(), WB::Render::DXGIFactory());

    // Create CommandQueue
    if (WB::Render::CommandQueue() == nullptr) 
        WB::CreateCommandQueue(WB::Render::CommandQueue(), WB::Render::DX12Device());

    // Create
    {
        WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = L"WindowContext Resize";

        windowContext->Create(wc);
    }

    // Resize
    {
        windowContext->SetPos(0, 0, 500, 500, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
        windowContext->Resize();
    }

    // Destroy
    windowContext.reset();
}