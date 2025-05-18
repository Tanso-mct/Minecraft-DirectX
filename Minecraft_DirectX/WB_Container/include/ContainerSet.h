#pragma once

#include "Interface/WindowContext.h"
#include "Interface/Monitor.h"
#include "Interface/ImageData.h"
#include "Interface/SoundData.h"
#include "Interface/ModelData.h"
#include "Interface/CsvData.h"

#include "WB_Container/include/Container.h"

#include <memory>
#include <string>

namespace WB
{
    /*******************************************************************************************************************
     * IDs of various data are defined in enumeration type
     * Use it to create various containers and access elements
    /******************************************************************************************************************/

    enum class WindowID
    {
        Game,
        Size,
    };
    using WindowContextContainer = StaticContainer<WB::IWindowContext, WindowID>;

    enum class MonitorID
    {
        Keyboard,
        Mouse,
        Size,
    };
    using MonitorContainer = StaticContainer<WB::IMonitor, MonitorID>;

    enum class ImageID
    {
        Example,
        Size,
    };
    using ImageDataContainer = StaticContainer<WB::IImageData, ImageID>;

    enum class SoundID
    {
        Example,
        Size,
    };
    using SoundDataContainer = StaticContainer<WB::ISoundData, SoundID>;

    enum class ModelID
    {
        Example,
        Size,
    };
    using ModelDataContainer = StaticContainer<WB::IModelData, ModelID>;

    enum class CsvID
    {
        Example,
        Size,
    };
    using CsvDataContainer = StaticContainer<WB::ICsvData, CsvID>;

    class ContainerSet
    {
    private:
        /***************************************************************************************************************
         * StaticContainers
        /**************************************************************************************************************/

        std::unique_ptr<WindowContextContainer> _windowContext = nullptr;
        std::unique_ptr<MonitorContainer> _monitor = nullptr;
        std::unique_ptr<ImageDataContainer> _image = nullptr;
        std::unique_ptr<SoundDataContainer> _sound = nullptr;
        std::unique_ptr<ModelDataContainer> _model = nullptr;
        std::unique_ptr<CsvDataContainer> _csv = nullptr;

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
         * ContainerSet has unique_ptr objects, so it is not copyable or assignable.
        /**************************************************************************************************************/

        ContainerSet()
        {
#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"ContainerSet Constructor"});
#endif
        }

        ~ContainerSet()
        {
#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"ContainerSet Destructor"});
#endif
        }

        ContainerSet(const ContainerSet&) = delete;
        ContainerSet& operator=(const ContainerSet&) = delete;

        /***************************************************************************************************************
         * Template function implementation
         * Specialization, to be used only with specified types
        /**************************************************************************************************************/

        template<typename T, typename ID>
        std::unique_ptr<StaticContainer<T, ID>>& Container()
        {
            std::string err = WBContainer::ConsoleLog()->LogErr
            (
                __FILE__, __LINE__, __FUNCTION__,
                {"ContainerSet Container : Invalid container type"}
            );
            WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

            return std::make_unique<StaticContainer<T, ID>>(); // Return an empty container
        }

        /***************************************************************************************************************
         * WindowContext
        /**************************************************************************************************************/

        template<>
        std::unique_ptr<WindowContextContainer>& Container<WB::IWindowContext, WindowID>()
        {
            return _windowContext;
        }

        /***************************************************************************************************************
         * Monitor
        /**************************************************************************************************************/

        template<>
        std::unique_ptr<MonitorContainer>& Container<WB::IMonitor, MonitorID>()
        {
            return _monitor;
        }

        /***************************************************************************************************************
         * Image
        /**************************************************************************************************************/

        template<>
        std::unique_ptr<ImageDataContainer>& Container<WB::IImageData, ImageID>()
        {
            return _image;
        }

        /***************************************************************************************************************
         * Sound
        /**************************************************************************************************************/

        template<>
        std::unique_ptr<SoundDataContainer>& Container<WB::ISoundData, SoundID>()
        {
            return _sound;
        }

        /***************************************************************************************************************
         * Model
        /**************************************************************************************************************/

        template<>
        std::unique_ptr<ModelDataContainer>& Container<WB::IModelData, ModelID>()
        {
            return _model;
        }

        /***************************************************************************************************************
         * CSV
        /**************************************************************************************************************/

        template<>
        std::unique_ptr<CsvDataContainer>& Container<WB::ICsvData, CsvID>()
        {
            return _csv;
        }

    };

} // namespace WB