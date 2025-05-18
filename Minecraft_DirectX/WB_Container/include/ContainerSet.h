#pragma once

#include "Interface/Container.h"
#include "Interface/ContainerSet.h"

#include "WB_Container/include/Container.h"

#include <memory>
#include <string>

namespace WB
{
    class ContainerSet : public IContainerSet
    {
    private:
        /***************************************************************************************************************
         * StaticContainers
        /**************************************************************************************************************/

        std::unique_ptr<IWindowContextContainer> _windowContext = nullptr;
        std::unique_ptr<ISceneContextContainer> _sceneContext = nullptr;
        std::unique_ptr<IMonitorContainer> _monitor = nullptr;
        std::unique_ptr<IImageDataContainer> _image = nullptr;
        std::unique_ptr<ISoundDataContainer> _sound = nullptr;
        std::unique_ptr<IModelDataContainer> _model = nullptr;
        std::unique_ptr<ICsvDataContainer> _csv = nullptr;

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
         * IContainerSet interface implementation
        /**************************************************************************************************************/

        std::unique_ptr<IWindowContextContainer>& WindowContextCont() override
        {
            return _windowContext;
        }

        std::unique_ptr<ISceneContextContainer>& SceneContextCont() override
        {
            return _sceneContext;
        }

        std::unique_ptr<IMonitorContainer>& MonitorCont() override
        {
            return _monitor;
        }

        std::unique_ptr<IImageDataContainer>& ImageDataCont() override
        {
            return _image;
        }

        std::unique_ptr<ISoundDataContainer>& SoundDataCont() override
        {
            return _sound;
        }

        std::unique_ptr<IModelDataContainer>& ModelDataCont() override
        {
            return _model;
        }

        std::unique_ptr<ICsvDataContainer>& CsvDataCont() override
        {
            return _csv;
        }

    };

} // namespace WB