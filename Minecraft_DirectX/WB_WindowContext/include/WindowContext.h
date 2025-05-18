#pragma once

#include "WB_WindowContext/include/Config.h"
#include "Interface/WindowContext.h"

#include <string>

namespace WB
{
    WINDOW_CONTEXT_API class WindowContext : public IWindowContext
    {
    private:
        HWND _hWnd = nullptr;
        HINSTANCE _hInstance = nullptr;

        std::string _name = "Window";
        int _posX = CW_USEDEFAULT;
        int _posY = CW_USEDEFAULT;
        unsigned int _width = 800;
        unsigned int _height = 600;

        bool _isFocus = false;
        bool _isMaximized = false;
        bool _isMinimized = false;

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
        /**************************************************************************************************************/

        WindowContext() = default;
        ~WindowContext() override = default;

        /***************************************************************************************************************
         * IWindowContext interface implementation
        /**************************************************************************************************************/

        void Initialize(WindowContextConfig& config) override;

        HWND& GetHWnd() override { return _hWnd; }
        HINSTANCE& GetHInstance() override { return _hInstance; }

        std::string_view GetName() override { return _name; }
        int GetPosX() override { return _posX; }
        int GetPosY() override { return _posY; }
        int GetWidth() override { return _width; }
        int GetHeight() override { return _height; }

        void CreateWindowNotApi() override;

        bool& IsFocus() override { return _isFocus; }
        bool& IsMaximized() override { return _isMaximized; }
        bool& IsMinimized() override { return _isMinimized; }

        void CreateSwapChain() override;
        void ResizeSwapChain(int width, int height) override;

        void CreateRenderTarget() override;
        void ResizeRenderTarget(int width, int height) override;

        void CreateDepthStencil() override;
        void ResizeDepthStencil(int width, int height) override;

        void CreateViewport() override;
        void ResizeViewport(int width, int height) override;

        void CreateScissorRect() override;
        void ResizeScissorRect(int width, int height) override;

    };
}