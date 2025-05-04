#pragma once

#include "WB_Container/include/config.h"

#include "Interface/Container.h"
#include "Interface/JsonData.h"

#include <vector>
#include <memory>

namespace WB
{
    class CONTAINER_API JsonDataContainer : public IJsonDataContainer
    {
    private:
        std::vector<std::unique_ptr<IJsonData>> _jsonDatas;
        std::unique_ptr<IJsonData> _empty = nullptr; // Dummy used when returning references

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
         * Container has unique_ptr objects, so it is not copyable or assignable.
        /**************************************************************************************************************/

        JsonDataContainer() = default;
        ~JsonDataContainer() override = default;

        JsonDataContainer(const JsonDataContainer&) = delete;
        JsonDataContainer& operator=(const JsonDataContainer&) = delete;

        /***************************************************************************************************************
         * IContainer interface implementation
        /**************************************************************************************************************/

        ContainerType GetContainerType() override;

        void Create(unsigned int) override;
        void Clear() override;
        size_t GetSize() const override;

        /***************************************************************************************************************
         * IJsonDataContainer interface implementation
        /**************************************************************************************************************/

        void Add(std::unique_ptr<IJsonData> jsonData) override;
        void Remove(int index) override;
        std::unique_ptr<IJsonData> &Get(int index) override;
        std::unique_ptr<IJsonData> Take(int index) override;
        void Set(int index, std::unique_ptr<IJsonData> jsonData) override;
    };
}