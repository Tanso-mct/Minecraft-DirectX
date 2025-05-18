#pragma once

#include "Interface/Container.h"

namespace WB
{
    class IContainerSet
    {
    public:
        virtual ~IContainerSet() = default;

        virtual std::unique_ptr<IWindowContextContainer>& WindowContextCont() = 0;
        virtual std::unique_ptr<ISceneContextContainer>& SceneContextCont() = 0;
        virtual std::unique_ptr<IMonitorContainer>& MonitorCont() = 0;
        virtual std::unique_ptr<IImageDataContainer>& ImageDataCont() = 0;
        virtual std::unique_ptr<ISoundDataContainer>& SoundDataCont() = 0;
        virtual std::unique_ptr<IModelDataContainer>& ModelDataCont() = 0;
        virtual std::unique_ptr<ICsvDataContainer>& CsvDataCont() = 0;
    };

} // namespace WB