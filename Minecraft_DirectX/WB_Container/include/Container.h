#pragma once

#include "WB_Container/include/Config.h"

#include "Interface/Container.h"

#include <vector>
#include <memory>

namespace WB
{
    class CONTAINER_API Container : public IContainer, public IElement
    {
    private:
        std::vector<std::unique_ptr<IElement>> _datas;
        std::unique_ptr<IElement> _empty = nullptr; // Dummy used when returning references

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

        size_t Add(std::unique_ptr<IElement> data) override;
        void Remove(int index) override;
        std::unique_ptr<IElement>& Get(int index) override;
        std::unique_ptr<IElement> Take(int index) override;
        void Set(int index, std::unique_ptr<IElement> data) override;
    };

} // namespace WB