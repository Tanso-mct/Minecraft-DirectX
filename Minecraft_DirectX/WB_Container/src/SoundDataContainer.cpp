#include "WB_Container/include/SoundDataContainer.h"

WB::ContainerType WB::SoundDataContainer::GetContainerType()
{
    return WB::ContainerType::SoundData;
}

void WB::SoundDataContainer::Create(unsigned int size)
{
    if (_soundDatas.size() > size) return; // No need to create more than needed
    _soundDatas.resize(size);
}

void WB::SoundDataContainer::Clear()
{
    _soundDatas.clear();
}

size_t WB::SoundDataContainer::GetSize() const
{
    return _soundDatas.size();
}

void WB::SoundDataContainer::Add(std::unique_ptr<ISoundData> soundData)
{
    _soundDatas.push_back(std::move(soundData));
}

void WB::SoundDataContainer::Remove(int index)
{
    if (index < 0 || index >= static_cast<int>(_soundDatas.size())) return; // Index out of bounds
    _soundDatas[index].reset(); // Reset the unique_ptr to remove the window context
}

std::unique_ptr<WB::ISoundData> &WB::SoundDataContainer::Get(int index)
{
    if (index < 0 || index >= static_cast<int>(_soundDatas.size())) return _empty; // Index out of bounds
    return _soundDatas[index]; // Return the unique_ptr reference
}

std::unique_ptr<WB::ISoundData> WB::SoundDataContainer::Take(int index)
{
    if (index < 0 || index >= static_cast<int>(_soundDatas.size())) return nullptr; // Index out of bounds
    return std::move(_soundDatas[index]); // Move the unique_ptr to the caller
}

void WB::SoundDataContainer::Set(int index, std::unique_ptr<ISoundData> soundData)
{
    if (index < 0 || index >= static_cast<int>(_soundDatas.size())) return; // Index out of bounds
    _soundDatas[index] = std::move(soundData); // Move the unique_ptr into the container
}