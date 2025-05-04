#include "WB_Container/include/JsonDataContainer.h"

WB::ContainerType WB::JsonDataContainer::GetContainerType()
{
    return WB::ContainerType::JsonData;
}

void WB::JsonDataContainer::Create(unsigned int size)
{
    if (_jsonDatas.size() > size) return; // No need to create more than needed
    _jsonDatas.resize(size);
}

void WB::JsonDataContainer::Clear()
{
    _jsonDatas.clear();
}

size_t WB::JsonDataContainer::GetSize() const
{
    return _jsonDatas.size();
}

void WB::JsonDataContainer::Add(std::unique_ptr<IJsonData> jsonData)
{
    _jsonDatas.push_back(std::move(jsonData));
}

void WB::JsonDataContainer::Remove(int index)
{
    if (index < 0 || index >= static_cast<int>(_jsonDatas.size())) return; // Index out of bounds
    _jsonDatas[index].reset(); // Reset the unique_ptr to remove the window context
}

std::unique_ptr<WB::IJsonData> &WB::JsonDataContainer::Get(int index)
{
    if (index < 0 || index >= static_cast<int>(_jsonDatas.size())) return _empty; // Index out of bounds
    return _jsonDatas[index]; // Return the unique_ptr reference
}

std::unique_ptr<WB::IJsonData> WB::JsonDataContainer::Take(int index)
{
    if (index < 0 || index >= static_cast<int>(_jsonDatas.size())) return nullptr; // Index out of bounds
    return std::move(_jsonDatas[index]); // Move the unique_ptr to the caller
}

void WB::JsonDataContainer::Set(int index, std::unique_ptr<IJsonData> jsonData)
{
    if (index < 0 || index >= static_cast<int>(_jsonDatas.size())) return; // Index out of bounds
    _jsonDatas[index] = std::move(jsonData); // Move the unique_ptr into the container
}