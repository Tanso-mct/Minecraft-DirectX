#include "WB_Container/include/MonitorContainer.h"

WB::ContainerType WB::MonitorContainer::GetContainerType()
{
    return WB::ContainerType::Monitor;
}

void WB::MonitorContainer::Create(unsigned int size)
{
    if (_monitors.size() > size) return; // No need to create more than needed
    _monitors.resize(size);
}

void WB::MonitorContainer::Clear()
{
    _monitors.clear();
}

size_t WB::MonitorContainer::GetSize() const
{
    return _monitors.size();
}

void WB::MonitorContainer::Add(std::unique_ptr<IMonitor> monitor)
{
    _monitors.push_back(std::move(monitor));
}

void WB::MonitorContainer::Remove(int index)
{
    if (index < 0 || index >= static_cast<int>(_monitors.size())) return; // Index out of bounds
    _monitors[index].reset(); // Reset the unique_ptr to remove the window context
}

std::unique_ptr<WB::IMonitor> &WB::MonitorContainer::Get(int index)
{
    if (index < 0 || index >= static_cast<int>(_monitors.size())) return _empty; // Index out of bounds
    return _monitors[index]; // Return the unique_ptr reference
}

std::unique_ptr<WB::IMonitor> WB::MonitorContainer::Take(int index)
{
    if (index < 0 || index >= static_cast<int>(_monitors.size())) return nullptr; // Index out of bounds
    return std::move(_monitors[index]); // Move the unique_ptr to the caller
}

void WB::MonitorContainer::Set(int index, std::unique_ptr<IMonitor> monitor)
{
    if (index < 0 || index >= static_cast<int>(_monitors.size())) return; // Index out of bounds
    _monitors[index] = std::move(monitor); // Move the unique_ptr into the container
}