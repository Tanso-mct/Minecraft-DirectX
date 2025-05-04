#include "WB_Container/include/SceneContextContainer.h"

WB::ContainerType WB::SceneContextContainer::GetContainerType()
{
    return WB::ContainerType::SceneContext;
}

void WB::SceneContextContainer::Create(unsigned int size)
{
    if (_sceneContexts.size() > size) return; // No need to create more than needed
    _sceneContexts.resize(size);
}

void WB::SceneContextContainer::Clear()
{
    _sceneContexts.clear();
}

size_t WB::SceneContextContainer::GetSize() const
{
    return _sceneContexts.size();
}

void WB::SceneContextContainer::Add(std::unique_ptr<ISceneContext> sceneContext)
{
    _sceneContexts.push_back(std::move(sceneContext));
}

void WB::SceneContextContainer::Remove(int index)
{
    if (index < 0 || index >= static_cast<int>(_sceneContexts.size())) return; // Index out of bounds
    _sceneContexts[index].reset(); // Reset the unique_ptr to remove the window context
}

std::unique_ptr<WB::ISceneContext> &WB::SceneContextContainer::Get(int index)
{
    if (index < 0 || index >= static_cast<int>(_sceneContexts.size())) return _empty; // Index out of bounds
    return _sceneContexts[index]; // Return the unique_ptr reference
}

std::unique_ptr<WB::ISceneContext> WB::SceneContextContainer::Take(int index)
{
    if (index < 0 || index >= static_cast<int>(_sceneContexts.size())) return nullptr; // Index out of bounds
    return std::move(_sceneContexts[index]); // Move the unique_ptr to the caller
}

void WB::SceneContextContainer::Set(int index, std::unique_ptr<ISceneContext> sceneContext)
{
    if (index < 0 || index >= static_cast<int>(_sceneContexts.size())) return; // Index out of bounds
    _sceneContexts[index] = std::move(sceneContext); // Move the unique_ptr into the container
}