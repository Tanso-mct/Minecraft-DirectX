#include "WB_Container/include/ImageDataContainer.h"

WB::ContainerType WB::ImageDataContainer::GetContainerType()
{
    return WB::ContainerType::ImageData;
}

void WB::ImageDataContainer::Create(unsigned int size)
{
    if (_imageDatas.size() > size) return; // No need to create more than needed
    _imageDatas.resize(size);
}

void WB::ImageDataContainer::Clear()
{
    _imageDatas.clear();
}

size_t WB::ImageDataContainer::GetSize() const
{
    return _imageDatas.size();
}

void WB::ImageDataContainer::Add(std::unique_ptr<IImageData> imageData)
{
    _imageDatas.push_back(std::move(imageData));
}

void WB::ImageDataContainer::Remove(int index)
{
    if (index < 0 || index >= static_cast<int>(_imageDatas.size())) return; // Index out of bounds
    _imageDatas[index].reset(); // Reset the unique_ptr to remove the window context
}

std::unique_ptr<WB::IImageData> &WB::ImageDataContainer::Get(int index)
{
    if (index < 0 || index >= static_cast<int>(_imageDatas.size())) return _empty; // Index out of bounds
    return _imageDatas[index]; // Return the unique_ptr reference
}

std::unique_ptr<WB::IImageData> WB::ImageDataContainer::Take(int index)
{
    if (index < 0 || index >= static_cast<int>(_imageDatas.size())) return nullptr; // Index out of bounds
    return std::move(_imageDatas[index]); // Move the unique_ptr to the caller
}

void WB::ImageDataContainer::Set(int index, std::unique_ptr<IImageData> imageData)
{
    if (index < 0 || index >= static_cast<int>(_imageDatas.size())) return; // Index out of bounds
    _imageDatas[index] = std::move(imageData); // Move the unique_ptr into the container
}