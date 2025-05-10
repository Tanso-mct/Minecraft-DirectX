#include "WB_Container/include/ModelDataContainer.h"

#include "WB_Container/include/Log.h"
#include "WB_Utility/include/ErrorHandling.h"

WB::ModelDataContainer::ModelDataContainer()
{
#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ModelDataContainer Constructor : Created model data container"});
#endif
}

WB::ModelDataContainer::~ModelDataContainer()
{
#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ModelDataContainer Destructor : Destroyed model data container"});
#endif
}

WB::ContainerType WB::ModelDataContainer::GetContainerType()
{
    return WB::ContainerType::ModelData;
}

void WB::ModelDataContainer::Create(unsigned int size)
{
    if (_modelDatas.size() > size) 
    {
#ifndef NDEBUG
        WBContainer::ConsoleLog()->LogWrn({"ModelDataContainer Create : No need to create more than needed"});
#endif
        return; // No need to create more than needed
    }

    _modelDatas.resize(size);

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ModelDataContainer Create : Created model data container"});
#endif
}

void WB::ModelDataContainer::Clear()
{
    _modelDatas.clear();

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ModelDataContainer Clear : Cleared model data container"});
#endif
}

size_t WB::ModelDataContainer::GetSize() const
{
    return _modelDatas.size();
}

void WB::ModelDataContainer::Add(std::unique_ptr<IModelData> windowContext)
{
    _modelDatas.push_back(std::move(windowContext));

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ModelDataContainer Add : Added model data"});
#endif
}

void WB::ModelDataContainer::Remove(int index)
{
    if (index < 0 || index >= static_cast<int>(_modelDatas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"ModelDataContainer Remove : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

        return; // Index out of bounds
    }

    _modelDatas[index].reset(); // Reset the unique_ptr to remove the model data

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ModelDataContainer Remove : Removed model data"});
#endif
}

std::unique_ptr<WB::IModelData> &WB::ModelDataContainer::Get(int index)
{
    if (index < 0 || index >= static_cast<int>(_modelDatas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"ModelDataContainer Get : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

         return _empty; // Index out of bounds
    }

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ModelDataContainer Get : Getting model data"});
#endif

    return _modelDatas[index]; // Return the unique_ptr reference
}

std::unique_ptr<WB::IModelData> WB::ModelDataContainer::Take(int index)
{
    if (index < 0 || index >= static_cast<int>(_modelDatas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"ModelDataContainer Take : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

        return nullptr; // Index out of bounds
    }

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ModelDataContainer Take : Taking model data"});
#endif

    return std::move(_modelDatas[index]); // Move the unique_ptr to the caller
}

void WB::ModelDataContainer::Set(int index, std::unique_ptr<IModelData> windowContext)
{
    if (index < 0 || index >= static_cast<int>(_modelDatas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"ModelDataContainer Set : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);
        
        return; // Index out of bounds
    }

    _modelDatas[index] = std::move(windowContext); // Move the unique_ptr into the container

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ModelDataContainer Set : Setted model data"});
#endif
}