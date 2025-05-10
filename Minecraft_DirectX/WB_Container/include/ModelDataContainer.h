#pragma once

#include "WB_Container/include/config.h"

#include "Interface/Container.h"
#include "Interface/ModelData.h"

#include <vector>
#include <memory>

namespace WB
{
    class CONTAINER_API ModelDataContainer : public IModelDataContainer
    {
    private:
        std::vector<std::unique_ptr<IModelData>> _modelDatas;
        std::unique_ptr<IModelData> _empty = nullptr; // Dummy used when returning references

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
         * Container has unique_ptr objects, so it is not copyable or assignable.
        /**************************************************************************************************************/

        ModelDataContainer();
        ~ModelDataContainer() override;

        ModelDataContainer(const ModelDataContainer&) = delete;
        ModelDataContainer& operator=(const ModelDataContainer&) = delete;

        /***************************************************************************************************************
         * IContainer interface implementation
        /**************************************************************************************************************/

        ContainerType GetContainerType() override;

        void Create(unsigned int) override;
        void Clear() override;
        size_t GetSize() const override;

        /***************************************************************************************************************
         * IModelDataContainer interface implementation
        /**************************************************************************************************************/

        void Add(std::unique_ptr<IModelData> model) override;
        void Remove(int index) override;
        std::unique_ptr<IModelData> &Get(int index) override;
        std::unique_ptr<IModelData> Take(int index) override;
        void Set(int index, std::unique_ptr<IModelData> model) override;
    };
}