#include "WB_Container/include/SceneContextContainer.h"

#include "WB_Container/include/Log.h"
#include "WB_Utility/include/ErrorHandling.h"

WB::SceneContextContainer::SceneContextContainer()
{
#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SceneContextContainer Constructor : Created scene context container"});
#endif
}

WB::SceneContextContainer::~SceneContextContainer()
{
#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SceneContextContainer Destructor : Destroyed scene context container"});
#endif
}

WB::ContainerType WB::SceneContextContainer::GetContainerType()
{
    return WB::ContainerType::SceneContext;
}

void WB::SceneContextContainer::Create(unsigned int size)
{
    if (_sceneContexts.size() > size) 
    {
#ifndef NDEBUG
        WBContainer::ConsoleLog()->LogWrn({"SceneContextContainer Create : No need to create more than needed"});
#endif
        return; // No need to create more than needed
    }

    _sceneContexts.resize(size);

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SceneContextContainer Create : Created scene context container"});
#endif
}

void WB::SceneContextContainer::Clear()
{
    _sceneContexts.clear();

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SceneContextContainer Clear : Cleared scene context container"});
#endif
}

size_t WB::SceneContextContainer::GetSize() const
{
    return _sceneContexts.size();
}

void WB::SceneContextContainer::Add(std::unique_ptr<ISceneContext> windowContext)
{
    _sceneContexts.push_back(std::move(windowContext));

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SceneContextContainer Add : Added scene context"});
#endif
}

void WB::SceneContextContainer::Remove(int index)
{
    if (index < 0 || index >= static_cast<int>(_sceneContexts.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"SceneContextContainer Remove : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

        return; // Index out of bounds
    }

    _sceneContexts[index].reset(); // Reset the unique_ptr to remove the scene context

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SceneContextContainer Remove : Removed scene context"});
#endif
}

std::unique_ptr<WB::ISceneContext> &WB::SceneContextContainer::Get(int index)
{
    if (index < 0 || index >= static_cast<int>(_sceneContexts.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"SceneContextContainer Get : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

         return _empty; // Index out of bounds
    }

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SceneContextContainer Get : Getting scene context"});
#endif

    return _sceneContexts[index]; // Return the unique_ptr reference
}

std::unique_ptr<WB::ISceneContext> WB::SceneContextContainer::Take(int index)
{
    if (index < 0 || index >= static_cast<int>(_sceneContexts.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"SceneContextContainer Take : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

        return nullptr; // Index out of bounds
    }

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SceneContextContainer Take : Taking scene context"});
#endif

    return std::move(_sceneContexts[index]); // Move the unique_ptr to the caller
}

void WB::SceneContextContainer::Set(int index, std::unique_ptr<ISceneContext> windowContext)
{
    if (index < 0 || index >= static_cast<int>(_sceneContexts.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"SceneContextContainer Set : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);
        
        return; // Index out of bounds
    }

    _sceneContexts[index] = std::move(windowContext); // Move the unique_ptr into the container

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"SceneContextContainer Set : Setted scene context"});
#endif
}