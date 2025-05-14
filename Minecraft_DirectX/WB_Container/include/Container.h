#pragma once

#include "WB_Container/include/Config.h"

#include "Interface/Container.h"

#include <vector>
#include <memory>

namespace WB
{
    class CONTAINER_API Container : public IContainer
    {
    private:
        std::vector<std::unique_ptr<IContainable>> _datas;
        std::unique_ptr<IContainable> _empty = nullptr; // Dummy used when returning references

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
         * Container has unique_ptr objects, so it is not copyable or assignable.
        /**************************************************************************************************************/

        Container();
        ~Container() override;

        Container(const Container&) = delete;
        Container& operator=(const Container&) = delete;

        /***************************************************************************************************************
         * IContainer interface implementation
        /**************************************************************************************************************/

        void Create(unsigned int) override;
        void Clear() override;
        size_t GetSize() const override;

        size_t Add(std::unique_ptr<IContainable> data) override;
        void Remove(int index) override;
        std::unique_ptr<IContainable>& Get(int index) override;
        std::unique_ptr<IContainable> Take(int index) override;
        void Set(int index, std::unique_ptr<IContainable> data) override;
    };

} // namespace WB