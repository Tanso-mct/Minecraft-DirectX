#include "WB_Container/include/SoundDataContainer.h"

#include "WB_Container/include/Log.h"
#include "WB_Utility/include/ErrorHandling.h"

WB::SoundDataContainer::SoundDataContainer()
{
#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SoundDataContainer Constructor : Created sound data container"});
#endif
}

WB::SoundDataContainer::~SoundDataContainer()
{
#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SoundDataContainer Destructor : Destroyed sound data container"});
#endif
}

WB::ContainerType WB::SoundDataContainer::GetContainerType()
{
    return WB::ContainerType::SoundData;
}

void WB::SoundDataContainer::Create(unsigned int size)
{
    if (_soundDatas.size() > size) 
    {
#ifndef NDEBUG
        WBContainer::ConsoleLog()->LogWrn({"SoundDataContainer Create : No need to create more than needed"});
#endif
        return; // No need to create more than needed
    }

    _soundDatas.resize(size);

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SoundDataContainer Create : Created sound data container"});
#endif
}

void WB::SoundDataContainer::Clear()
{
    _soundDatas.clear();

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SoundDataContainer Clear : Cleared sound data container"});
#endif
}

size_t WB::SoundDataContainer::GetSize() const
{
    return _soundDatas.size();
}

void WB::SoundDataContainer::Add(std::unique_ptr<ISoundData> windowContext)
{
    _soundDatas.push_back(std::move(windowContext));

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SoundDataContainer Add : Added sound data"});
#endif
}

void WB::SoundDataContainer::Remove(int index)
{
    if (index < 0 || index >= static_cast<int>(_soundDatas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"SoundDataContainer Remove : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

        return; // Index out of bounds
    }

    _soundDatas[index].reset(); // Reset the unique_ptr to remove the sound data

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SoundDataContainer Remove : Removed sound data"});
#endif
}

std::unique_ptr<WB::ISoundData> &WB::SoundDataContainer::Get(int index)
{
    if (index < 0 || index >= static_cast<int>(_soundDatas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"SoundDataContainer Get : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

         return _empty; // Index out of bounds
    }

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SoundDataContainer Get : Getting sound data"});
#endif

    return _soundDatas[index]; // Return the unique_ptr reference
}

std::unique_ptr<WB::ISoundData> WB::SoundDataContainer::Take(int index)
{
    if (index < 0 || index >= static_cast<int>(_soundDatas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"SoundDataContainer Take : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

        return nullptr; // Index out of bounds
    }

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SoundDataContainer Take : Taking sound data"});
#endif

    return std::move(_soundDatas[index]); // Move the unique_ptr to the caller
}

void WB::SoundDataContainer::Set(int index, std::unique_ptr<ISoundData> windowContext)
{
    if (index < 0 || index >= static_cast<int>(_soundDatas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"SoundDataContainer Set : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);
        
        return; // Index out of bounds
    }

    _soundDatas[index] = std::move(windowContext); // Move the unique_ptr into the container

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SoundDataContainer Set : Setted sound data"});
#endif
}