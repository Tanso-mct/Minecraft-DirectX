#include "WB_Container/include/ImageDataContainer.h"

#include "WB_Container/include/Log.h"
#include "WB_Utility/include/ErrorHandling.h"

WB::ImageDataContainer::ImageDataContainer()
{
#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ImageDataContainer Constructor : Created image data container"});
#endif
}

WB::ImageDataContainer::~ImageDataContainer()
{
#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ImageDataContainer Destructor : Destroyed image data container"});
#endif
}

WB::ContainerType WB::ImageDataContainer::GetContainerType()
{
    return WB::ContainerType::ImageData;
}

void WB::ImageDataContainer::Create(unsigned int size)
{
    if (_imageDatas.size() > size) 
    {
#ifndef NDEBUG
        WBContainer::ConsoleLog()->LogWrn({"ImageDataContainer Create : No need to create more than needed"});
#endif
        return; // No need to create more than needed
    }

    _imageDatas.resize(size);

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ImageDataContainer Create : Created image data container"});
#endif
}

void WB::ImageDataContainer::Clear()
{
    _imageDatas.clear();

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ImageDataContainer Clear : Cleared image data container"});
#endif
}

size_t WB::ImageDataContainer::GetSize() const
{
    return _imageDatas.size();
}

void WB::ImageDataContainer::Add(std::unique_ptr<IImageData> windowContext)
{
    _imageDatas.push_back(std::move(windowContext));

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ImageDataContainer Add : Added image data"});
#endif
}

void WB::ImageDataContainer::Remove(int index)
{
    if (index < 0 || index >= static_cast<int>(_imageDatas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"ImageDataContainer Remove : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

        return; // Index out of bounds
    }

    _imageDatas[index].reset(); // Reset the unique_ptr to remove the image data

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ImageDataContainer Remove : Removed image data"});
#endif
}

std::unique_ptr<WB::IImageData> &WB::ImageDataContainer::Get(int index)
{
    if (index < 0 || index >= static_cast<int>(_imageDatas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"ImageDataContainer Get : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

         return _empty; // Index out of bounds
    }

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ImageDataContainer Get : Getting image data"});
#endif

    return _imageDatas[index]; // Return the unique_ptr reference
}

std::unique_ptr<WB::IImageData> WB::ImageDataContainer::Take(int index)
{
    if (index < 0 || index >= static_cast<int>(_imageDatas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"ImageDataContainer Take : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

        return nullptr; // Index out of bounds
    }

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ImageDataContainer Take : Taking image data"});
#endif

    return std::move(_imageDatas[index]); // Move the unique_ptr to the caller
}

void WB::ImageDataContainer::Set(int index, std::unique_ptr<IImageData> windowContext)
{
    if (index < 0 || index >= static_cast<int>(_imageDatas.size()))
    {
        std::string err = WBContainer::ConsoleLog()->LogErr
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"ImageDataContainer Set : Index out of bounds"}
        );
        WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);
        
        return; // Index out of bounds
    }

    _imageDatas[index] = std::move(windowContext); // Move the unique_ptr into the container

#ifndef NDEBUG
    WBContainer::ConsoleLog()->Log({"ImageDataContainer Set : Setted image data"});
#endif
}