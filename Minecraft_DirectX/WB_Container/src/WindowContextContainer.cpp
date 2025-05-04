#include "WB_Container/include/WindowContextContainer.h"

WB::ContainerType WB::WindowContextContainer::GetContainerType()
{
    return WB::ContainerType::WindowContext;
}

void WB::WindowContextContainer::Create(unsigned int size)
{
    if (_windowContexts.size() > size) return; // No need to create more than needed
    _windowContexts.resize(size);
}

void WB::WindowContextContainer::Clear()
{
    _windowContexts.clear();
}

size_t WB::WindowContextContainer::GetSize() const
{
    return _windowContexts.size();
}

void WB::WindowContextContainer::Add(std::unique_ptr<IWindowContext> windowContext)
{
    _windowContexts.push_back(std::move(windowContext));
}

void WB::WindowContextContainer::Remove(int index)
{
    if (index < 0 || index >= static_cast<int>(_windowContexts.size())) return; // Index out of bounds
    _windowContexts[index].reset(); // Reset the unique_ptr to remove the window context
}

std::unique_ptr<WB::IWindowContext> &WB::WindowContextContainer::Get(int index)
{
    if (index < 0 || index >= static_cast<int>(_windowContexts.size())) return _empty; // Index out of bounds
    return _windowContexts[index]; // Return the unique_ptr reference
}

std::unique_ptr<WB::IWindowContext> WB::WindowContextContainer::Take(int index)
{
    if (index < 0 || index >= static_cast<int>(_windowContexts.size())) return nullptr; // Index out of bounds
    return std::move(_windowContexts[index]); // Move the unique_ptr to the caller
}

void WB::WindowContextContainer::Set(int index, std::unique_ptr<IWindowContext> windowContext)
{
    if (index < 0 || index >= static_cast<int>(_windowContexts.size())) return; // Index out of bounds
    _windowContexts[index] = std::move(windowContext); // Move the unique_ptr into the container
}