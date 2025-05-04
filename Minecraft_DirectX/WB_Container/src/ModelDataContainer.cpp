#include "WB_Container/include/ModelDataContainer.h"

WB::ContainerType WB::ModelDataContainer::GetContainerType()
{
    return WB::ContainerType::ModelData;
}

void WB::ModelDataContainer::Create(unsigned int size)
{
    if (_models.size() > size) return; // No need to create more than needed
    _models.resize(size);
}

void WB::ModelDataContainer::Clear()
{
    _models.clear();
}

size_t WB::ModelDataContainer::GetSize() const
{
    return _models.size();
}

void WB::ModelDataContainer::Add(std::unique_ptr<IModelData> model)
{
    _models.push_back(std::move(model));
}

void WB::ModelDataContainer::Remove(int index)
{
    if (index < 0 || index >= static_cast<int>(_models.size())) return; // Index out of bounds
    _models[index].reset(); // Reset the unique_ptr to remove the window context
}

std::unique_ptr<WB::IModelData> &WB::ModelDataContainer::Get(int index)
{
    if (index < 0 || index >= static_cast<int>(_models.size())) return _empty; // Index out of bounds
    return _models[index]; // Return the unique_ptr reference
}

std::unique_ptr<WB::IModelData> WB::ModelDataContainer::Take(int index)
{
    if (index < 0 || index >= static_cast<int>(_models.size())) return nullptr; // Index out of bounds
    return std::move(_models[index]); // Move the unique_ptr to the caller
}

void WB::ModelDataContainer::Set(int index, std::unique_ptr<IModelData> model)
{
    if (index < 0 || index >= static_cast<int>(_models.size())) return; // Index out of bounds
    _models[index] = std::move(model); // Move the unique_ptr into the container
}