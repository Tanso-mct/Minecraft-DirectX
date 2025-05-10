#include "WB_Container/include/MonitorContainer.h"

#include "WB_Container/include/Log.h"
#include "WB_Utility/include/ErrorHandling.h"

WB::MonitorContainer::MonitorContainer()
{
#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"MonitorContainer Constructor : Created monitor container"});
#endif
}

WB::MonitorContainer::~MonitorContainer()
{
#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"MonitorContainer Destructor : Destroyed monitor container"});
#endif
}

WB::ContainerType WB::MonitorContainer::GetContainerType()
{
    return WB::ContainerType::Monitor;
}

void WB::MonitorContainer::Create(unsigned int size)
{
    if (_monitors.size() > size) 
    {
#ifndef NDEBUG
        WBContainer::ConsoleLog()->LogWrn({"MonitorContainer Create : No need to create more than needed"});
#endif
        return; // No need to create more than needed
    }

    _monitors.resize(size);

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"MonitorContainer Create : Created monitor container"});
#endif
}

void WB::MonitorContainer::Clear()
{
    _monitors.clear();

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"MonitorContainer Clear : Cleared monitor container"});
#endif
}

size_t WB::MonitorContainer::GetSize() const
{
    return _monitors.size();
}

void WB::MonitorContainer::Add(std::unique_ptr<IMonitor> windowContext)
{
    _monitors.push_back(std::move(windowContext));

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"MonitorContainer Add : Added monitor"});
#endif
}

void WB::MonitorContainer::Remove(int index)
{
    if (index < 0 || index >= static_cast<int>(_monitors.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"MonitorContainer Remove : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

        return; // Index out of bounds
    }

    _monitors[index].reset(); // Reset the unique_ptr to remove the monitor

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"MonitorContainer Remove : Removed monitor"});
#endif
}

std::unique_ptr<WB::IMonitor> &WB::MonitorContainer::Get(int index)
{
    if (index < 0 || index >= static_cast<int>(_monitors.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"MonitorContainer Get : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

         return _empty; // Index out of bounds
    }

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"MonitorContainer Get : Getting monitor"});
#endif

    return _monitors[index]; // Return the unique_ptr reference
}

std::unique_ptr<WB::IMonitor> WB::MonitorContainer::Take(int index)
{
    if (index < 0 || index >= static_cast<int>(_monitors.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"MonitorContainer Take : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

        return nullptr; // Index out of bounds
    }

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"MonitorContainer Take : Taking monitor"});
#endif

    return std::move(_monitors[index]); // Move the unique_ptr to the caller
}

void WB::MonitorContainer::Set(int index, std::unique_ptr<IMonitor> windowContext)
{
    if (index < 0 || index >= static_cast<int>(_monitors.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"MonitorContainer Set : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);
        
        return; // Index out of bounds
    }

    _monitors[index] = std::move(windowContext); // Move the unique_ptr into the container

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"MonitorContainer Set : Setted monitor"});
#endif
}