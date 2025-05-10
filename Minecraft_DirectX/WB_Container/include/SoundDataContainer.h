#pragma once

#include "WB_Container/include/config.h"

#include "Interface/Container.h"
#include "Interface/SoundData.h"

#include <vector>
#include <memory>

namespace WB
{
    class CONTAINER_API SoundDataContainer : public ISoundDataContainer
    {
    private:
        std::vector<std::unique_ptr<ISoundData>> _soundDatas;
        std::unique_ptr<ISoundData> _empty = nullptr; // Dummy used when returning references

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
         * Container has unique_ptr objects, so it is not copyable or assignable.
        /**************************************************************************************************************/

        SoundDataContainer();
        ~SoundDataContainer() override;

        SoundDataContainer(const SoundDataContainer&) = delete;
        SoundDataContainer& operator=(const SoundDataContainer&) = delete;

        /***************************************************************************************************************
         * IContainer interface implementation
        /**************************************************************************************************************/

        ContainerType GetContainerType() override;

        void Create(unsigned int) override;
        void Clear() override;
        size_t GetSize() const override;

        /***************************************************************************************************************
         * ISoundDataContainer interface implementation
        /**************************************************************************************************************/

        void Add(std::unique_ptr<ISoundData> soundData) override;
        void Remove(int index) override;
        std::unique_ptr<ISoundData> &Get(int index) override;
        std::unique_ptr<ISoundData> Take(int index) override;
        void Set(int index, std::unique_ptr<ISoundData> soundData) override;
    };
}