#include "Container/include/WindowContextContainer.h"

MCT::ContainerType MCT::WindowContextContainer::GetContainerType()
{
    return MCT::ContainerType::WindowContext;
}

void MCT::WindowContextContainer::Create(unsigned int size)
{
    if (_windowContexts.size() > size) return; // No need to create more than needed
    _windowContexts.resize(size);
}

void MCT::WindowContextContainer::Clear()
{
    _windowContexts.clear();
}

size_t MCT::WindowContextContainer::GetSize() const
{
    return _windowContexts.size();
}

void MCT::WindowContextContainer::Add(std::unique_ptr<IWindowContext> windowContext)
{
    _windowContexts.push_back(std::move(windowContext));
}

void MCT::WindowContextContainer::Remove(int index)
{
    if (index < 0 || index >= static_cast<int>(_windowContexts.size())) return; // Index out of bounds
    _windowContexts[index].reset(); // Reset the unique_ptr to remove the window context
}

std::unique_ptr<MCT::IWindowContext> &MCT::WindowContextContainer::Get(int index)
{
    if (index < 0 || index >= static_cast<int>(_windowContexts.size())) return _empty; // Index out of bounds
    return _windowContexts[index]; // Return the unique_ptr reference
}

std::unique_ptr<MCT::IWindowContext> MCT::WindowContextContainer::Take(int index)
{
    if (index < 0 || index >= static_cast<int>(_windowContexts.size())) return nullptr; // Index out of bounds
    return std::move(_windowContexts[index]); // Move the unique_ptr to the caller
}

void MCT::WindowContextContainer::Set(int index, std::unique_ptr<IWindowContext> windowContext)
{
    if (index < 0 || index >= static_cast<int>(_windowContexts.size())) return; // Index out of bounds
    _windowContexts[index] = std::move(windowContext); // Move the unique_ptr into the container
}