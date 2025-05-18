#pragma once

#include <memory>
#include <Windows.h>

namespace WB
{
    class IContainerSet;

    class IWindowEvent
    {
    public:
        virtual ~IWindowEvent() = default;

        virtual void OnKeyDown(std::unique_ptr<IContainerSet> containerSet, UINT msg, WPARAM wParam, LPARAM lParam) = 0;
        virtual void OnKeyUp(std::unique_ptr<IContainerSet> containerSet, UINT msg, WPARAM wParam, LPARAM lParam) = 0;
        virtual void OnMouse(std::unique_ptr<IContainerSet> containerSet, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

        virtual void OnSetFocus(std::unique_ptr<IContainerSet> containerSet, UINT msg, WPARAM wParam, LPARAM lParam) = 0;
        virtual void OnKillFocus(std::unique_ptr<IContainerSet> containerSet, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

        virtual void OnSize(std::unique_ptr<IContainerSet> containerSet, UINT msg, WPARAM wParam, LPARAM lParam) = 0;
        virtual void OnMove(std::unique_ptr<IContainerSet> containerSet, UINT msg, WPARAM wParam, LPARAM lParam) = 0;
        virtual void OnPaint(std::unique_ptr<IContainerSet> containerSet, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

        virtual void OnClose(std::unique_ptr<IContainerSet> containerSet, UINT msg, WPARAM wParam, LPARAM lParam) = 0;
        virtual void OnDestroy(std::unique_ptr<IContainerSet> containerSet, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

    };
}