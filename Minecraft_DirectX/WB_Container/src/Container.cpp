#include "WB_Container/include/Container.h"

#include "WB_Container/include/Log.h"
#include "WB_Utility/include/ErrorHandling.h"

WB::Container::Container()
{
#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"Container Constructor : Created image data container"});
#endif
}

WB::Container::~Container()
{
#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"Container Destructor : Destroyed image data container"});
#endif
}

void WB::Container::Create(unsigned int size)
{
    if (_datas.size() > size) 
    {
#ifndef NDEBUG
        WBContainer::ConsoleLog()->LogWrn({"Container Create : No need to create more than needed"});
#endif
        return; // No need to create more than needed
    }

    _datas.resize(size);

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"Container Create : Created image data container"});
#endif
}

void WB::Container::Clear()
{
    _datas.clear();

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"Container Clear : Cleared image data container"});
#endif
}

size_t WB::Container::GetSize() const
{
    return _datas.size();
}

size_t WB::Container::Add(std::unique_ptr<WB::IElement> windowContext)
{
    _datas.push_back(std::move(windowContext));

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"Container Add : Added image data"});
#endif

    return _datas.size() - 1; // Return the index of the added element
}

void WB::Container::Remove(int index)
{
    if (index < 0 || index >= static_cast<int>(_datas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"Container Remove : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

        return; // Index out of bounds
    }

    _datas[index].reset(); // Reset the unique_ptr to remove the image data

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"Container Remove : Removed image data"});
#endif
}

std::unique_ptr<WB::IElement> &WB::Container::Get(int index)
{
    if (index < 0 || index >= static_cast<int>(_datas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"Container Get : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

         return _empty; // Index out of bounds
    }

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"Container Get : Getting image data"});
#endif

    return _datas[index]; // Return the unique_ptr reference
}

std::unique_ptr<WB::IElement> WB::Container::Take(int index)
{
    if (index < 0 || index >= static_cast<int>(_datas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"Container Take : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

        return nullptr; // Index out of bounds
    }

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"Container Take : Taking image data"});
#endif

    return std::move(_datas[index]); // Move the unique_ptr to the caller
}

void WB::Container::Set(int index, std::unique_ptr<WB::IElement> windowContext)
{
    if (index < 0 || index >= static_cast<int>(_datas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"Container Set : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);
        
        return; // Index out of bounds
    }

    _datas[index] = std::move(windowContext); // Move the unique_ptr into the container

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"Container Set : Setted image data"});
#endif
}