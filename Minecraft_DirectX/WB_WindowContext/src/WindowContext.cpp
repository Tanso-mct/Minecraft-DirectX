#include "WB_WindowContext/include/WindowContext.h"

#include "WB_WindowContext/include/Log.h"

#include "WB_Utility/include/WindowsHelpers.h"
#include "WB_Utility/include/ErrorHandling.h"
#pragma comment(lib, "WB_Utility.lib")

using Microsoft::WRL::ComPtr;
#pragma comment(lib, "d3d12.lib")

WB::WindowContext::WindowContext()
{
#ifndef NDEBUG
    WBWindowContext::ConsoleLog()->Log({"WindowContext Constructor : Created window context"});
#endif
}

WB::WindowContext::~WindowContext()
{
#ifndef NDEBUG
    WBWindowContext::ConsoleLog()->Log({"WindowContext Destructor : Destroyed window context"});
#endif
}

void WB::WindowContext::Initialize(const WindowDesc &desc)
{
    _hInstance = desc.hInstance;
    _hWndParent = desc.hWndParent;

    _name = desc.name;
    _posX = desc.posX;
    _posY = desc.posY;
    _width = desc.width;
    _height = desc.height;

#ifndef NDEBUG
    WBWindowContext::ConsoleLog()->Log({"WindowContext Initialize : Initialized window context"});
#endif

}

void WB::WindowContext::Create(WNDCLASSEX &wc)
{
    WB::CreateWindowNotApi
    (
        _hWnd,
        _name.c_str(),
        _posX, _posY,
        _width, _height,
        _hWndParent,
        wc
    );

    WB::ShowWindowNotApi(_hWnd);
}

void WB::WindowContext::Release()
{
}

void WB::WindowContext::Resize(int width, int height)
{
}

void WB::WindowContext::Show()
{
}

void WB::WindowContext::Hide()
{
}