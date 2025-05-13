#pragma once

#include "WB_Container/include/Config.h"

#include "Interface/Container.h"
#include "Interface/ImageData.h"

#include <vector>
#include <memory>

namespace WB
{
    class CONTAINER_API ImageDataContainer : public IImageDataContainer
    {
    private:
        std::vector<std::unique_ptr<IImageData>> _imageDatas;
        std::unique_ptr<IImageData> _empty = nullptr; // Dummy used when returning references

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
         * Container has unique_ptr objects, so it is not copyable or assignable.
        /**************************************************************************************************************/

        ImageDataContainer();
        ~ImageDataContainer() override;

        ImageDataContainer(const ImageDataContainer&) = delete;
        ImageDataContainer& operator=(const ImageDataContainer&) = delete;

        /***************************************************************************************************************
         * IContainer interface implementation
        /**************************************************************************************************************/

        ContainerType GetContainerType() override;

        void Create(unsigned int) override;
        void Clear() override;
        size_t GetSize() const override;

        /***************************************************************************************************************
         * IImageDataContainer interface implementation
        /**************************************************************************************************************/

        void Add(std::unique_ptr<IImageData> imageData) override;
        void Remove(int index) override;
        std::unique_ptr<IImageData> &Get(int index) override;
        std::unique_ptr<IImageData> Take(int index) override;
        void Set(int index, std::unique_ptr<IImageData> imageData) override;
    };
}