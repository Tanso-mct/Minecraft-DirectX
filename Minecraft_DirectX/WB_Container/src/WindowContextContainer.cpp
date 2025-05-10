#include "WB_Container/include/WindowContextContainer.h"

#include "WB_Container/include/Log.h"
#include "WB_Utility/include/ErrorHandling.h"

WB::WindowContextContainer::WindowContextContainer()
{
#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"WindowContextContainer Constructor : Created window context container"});
#endif
}

WB::WindowContextContainer::~WindowContextContainer()
{
#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"WindowContextContainer Destructor : Destroyed window context container"});
#endif
}

WB::ContainerType WB::WindowContextContainer::GetContainerType()
{
    return WB::ContainerType::WindowContext;
}

void WB::WindowContextContainer::Create(unsigned int size)
{
    if (_windowContexts.size() > size) 
    {
#ifndef NDEBUG
        WBContainer::ConsoleLog()->LogWrn({"WindowContextContainer Create : No need to create more than needed"});
#endif
        return; // No need to create more than needed
    }

    _windowContexts.resize(size);

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"WindowContextContainer Create : Created window context container"});
#endif
}

void WB::WindowContextContainer::Clear()
{
    _windowContexts.clear();

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"WindowContextContainer Clear : Cleared window context container"});
#endif
}

size_t WB::WindowContextContainer::GetSize() const
{
    return _windowContexts.size();
}

void WB::WindowContextContainer::Add(std::unique_ptr<IWindowContext> windowContext)
{
    _windowContexts.push_back(std::move(windowContext));

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"WindowContextContainer Add : Added window context"});
#endif
}

void WB::WindowContextContainer::Remove(int index)
{
    if (index < 0 || index >= static_cast<int>(_windowContexts.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"WindowContextContainer Remove : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

        return; // Index out of bounds
    }

    _windowContexts[index].reset(); // Reset the unique_ptr to remove the window context

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"WindowContextContainer Remove : Removed window context"});
#endif
}

std::unique_ptr<WB::IWindowContext> &WB::WindowContextContainer::Get(int index)
{
    if (index < 0 || index >= static_cast<int>(_windowContexts.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"WindowContextContainer Get : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

         return _empty; // Index out of bounds
    }

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"WindowContextContainer Get : Getting window context"});
#endif

    return _windowContexts[index]; // Return the unique_ptr reference
}

std::unique_ptr<WB::IWindowContext> WB::WindowContextContainer::Take(int index)
{
    if (index < 0 || index >= static_cast<int>(_windowContexts.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"WindowContextContainer Take : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

        return nullptr; // Index out of bounds
    }

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"WindowContextContainer Take : Taking window context"});
#endif

    return std::move(_windowContexts[index]); // Move the unique_ptr to the caller
}

void WB::WindowContextContainer::Set(int index, std::unique_ptr<IWindowContext> windowContext)
{
    if (index < 0 || index >= static_cast<int>(_windowContexts.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"WindowContextContainer Set : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);
        
        return; // Index out of bounds
    }

    _windowContexts[index] = std::move(windowContext); // Move the unique_ptr into the container

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"WindowContextContainer Set : Setted window context"});
#endif
}