#include "pch.h"

#include "WB_WindowContext/include/WindowContext.h"
#pragma comment(lib, "WB_WindowContext.lib")

#include "WB_Utility/include/WindowsHelpers.h"
#include "WB_Utility/include/DXHelpers.h"
#pragma comment(lib, "WB_Utility.lib")

#include "WB_GpuContext/include/GpuContext.h"
#pragma comment(lib, "WB_GpuContext.lib")

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

    // Create GpuContext
    WB::GpuContext::Create();

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

    // Create GpuContext
    WB::GpuContext::Create();

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

TEST(WindowContext, Maximize)
{
    std::unique_ptr<WB::IWindowContext> windowContext = std::make_unique<WB::WindowContext>();

    // Initialize
    {
        WB::WindowDesc desc;
        desc.hInstance = GetModuleHandle(nullptr);
        desc.hWndParent = nullptr;
        desc.name = L"WindowContext Maximize";

        windowContext->Initialize(desc);
    }

    // Create GpuContext
    WB::GpuContext::Create();

    // Create
    {
        WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = L"WindowContext Maximize";

        windowContext->Create(wc);
    }

    // Maximize
    {
        windowContext->Maximize();

        // Originally the window procedure receives WM_SIZE, but calls it directly for testing
        windowContext->Maximized();
    }

    // Destroy
    windowContext.reset();
}

TEST(WindowContext, Minimize)
{
    std::unique_ptr<WB::IWindowContext> windowContext = std::make_unique<WB::WindowContext>();

    // Initialize
    {
        WB::WindowDesc desc;
        desc.hInstance = GetModuleHandle(nullptr);
        desc.hWndParent = nullptr;
        desc.name = L"WindowContext Minimize";

        windowContext->Initialize(desc);
    }

    // Create GpuContext
    WB::GpuContext::Create();

    // Create
    {
        WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = L"WindowContext Minimize";

        windowContext->Create(wc);
    }

    // Minimize
    {
        windowContext->Minimize();

        // Originally the window procedure receives WM_SIZE, but calls it directly for testing
        windowContext->Minimized();
    }

    // Destroy
    windowContext.reset();
}

TEST(WindowContext, Restore)
{
    std::unique_ptr<WB::IWindowContext> windowContext = std::make_unique<WB::WindowContext>();

    // Initialize
    {
        WB::WindowDesc desc;
        desc.hInstance = GetModuleHandle(nullptr);
        desc.hWndParent = nullptr;
        desc.name = L"WindowContext Restore";

        windowContext->Initialize(desc);
    }

    // Create GpuContext
    WB::GpuContext::Create();

    // Create
    {
        WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = L"WindowContext Restore";

        windowContext->Create(wc);
    }

    // Restore
    {
        windowContext->Restore();

        // Originally the window procedure receives WM_SIZE, but calls it directly for testing
        windowContext->Restored();
    }

    // Destroy
    windowContext.reset();
}

TEST(WindowContext, SetPos)
{
    std::unique_ptr<WB::IWindowContext> windowContext = std::make_unique<WB::WindowContext>();

    // Initialize
    {
        WB::WindowDesc desc;
        desc.hInstance = GetModuleHandle(nullptr);
        desc.hWndParent = nullptr;
        desc.name = L"WindowContext SetPos";

        windowContext->Initialize(desc);
    }

    // Create GpuContext
    WB::GpuContext::Create();

    // Create
    {
        WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = L"WindowContext SetPos";

        windowContext->Create(wc);
    }

    // SetPos
    {
        windowContext->SetPos(1000, 500, 500, 500, SWP_NOZORDER | SWP_NOACTIVATE);

        // Originally the window procedure receives WM_SIZE, but calls it directly for testing
        windowContext->Resize();
    }

    // Destroy
    windowContext.reset();
}