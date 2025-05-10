#include "WB_Container/include/JsonDataContainer.h"

#include "WB_Container/include/Log.h"
#include "WB_Utility/include/ErrorHandling.h"

WB::JsonDataContainer::JsonDataContainer()
{
#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"JsonDataContainer Constructor : Created json data container"});
#endif
}

WB::JsonDataContainer::~JsonDataContainer()
{
#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"JsonDataContainer Destructor : Destroyed json data container"});
#endif
}

WB::ContainerType WB::JsonDataContainer::GetContainerType()
{
    return WB::ContainerType::JsonData;
}

void WB::JsonDataContainer::Create(unsigned int size)
{
    if (_jsonDatas.size() > size) 
    {
#ifndef NDEBUG
        WBContainer::ConsoleLog()->LogWrn({"JsonDataContainer Create : No need to create more than needed"});
#endif
        return; // No need to create more than needed
    }

    _jsonDatas.resize(size);

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"JsonDataContainer Create : Created json data container"});
#endif
}

void WB::JsonDataContainer::Clear()
{
    _jsonDatas.clear();

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"JsonDataContainer Clear : Cleared json data container"});
#endif
}

size_t WB::JsonDataContainer::GetSize() const
{
    return _jsonDatas.size();
}

void WB::JsonDataContainer::Add(std::unique_ptr<IJsonData> windowContext)
{
    _jsonDatas.push_back(std::move(windowContext));

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"JsonDataContainer Add : Added json data"});
#endif
}

void WB::JsonDataContainer::Remove(int index)
{
    if (index < 0 || index >= static_cast<int>(_jsonDatas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"JsonDataContainer Remove : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

        return; // Index out of bounds
    }

    _jsonDatas[index].reset(); // Reset the unique_ptr to remove the json data

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"JsonDataContainer Remove : Removed json data"});
#endif
}

std::unique_ptr<WB::IJsonData> &WB::JsonDataContainer::Get(int index)
{
    if (index < 0 || index >= static_cast<int>(_jsonDatas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"JsonDataContainer Get : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

         return _empty; // Index out of bounds
    }

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"JsonDataContainer Get : Getting json data"});
#endif

    return _jsonDatas[index]; // Return the unique_ptr reference
}

std::unique_ptr<WB::IJsonData> WB::JsonDataContainer::Take(int index)
{
    if (index < 0 || index >= static_cast<int>(_jsonDatas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"JsonDataContainer Take : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

        return nullptr; // Index out of bounds
    }

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"JsonDataContainer Take : Taking json data"});
#endif

    return std::move(_jsonDatas[index]); // Move the unique_ptr to the caller
}

void WB::JsonDataContainer::Set(int index, std::unique_ptr<IJsonData> windowContext)
{
    if (index < 0 || index >= static_cast<int>(_jsonDatas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"JsonDataContainer Set : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);
        
        return; // Index out of bounds
    }

    _jsonDatas[index] = std::move(windowContext); // Move the unique_ptr into the container

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"JsonDataContainer Set : Setted json data"});
#endif
}