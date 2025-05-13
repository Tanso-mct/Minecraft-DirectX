#pragma once

#include "WB_Container/include/Config.h"

#include "Interface/Container.h"
#include "Interface/WindowContext.h"

#include <vector>
#include <memory>

namespace WB
{
    class CONTAINER_API WindowContextContainer : public IWindowContextContainer
    {
    private:
        std::vector<std::unique_ptr<IWindowContext>> _windowContexts;
        std::unique_ptr<IWindowContext> _empty = nullptr; // Dummy used when returning references

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
         * Container has unique_ptr objects, so it is not copyable or assignable.
        /**************************************************************************************************************/

        WindowContextContainer();
        ~WindowContextContainer() override;

        WindowContextContainer(const WindowContextContainer&) = delete;
        WindowContextContainer& operator=(const WindowContextContainer&) = delete;

        /***************************************************************************************************************
         * IContainer interface implementation
        /**************************************************************************************************************/

        ContainerType GetContainerType() override;

        void Create(unsigned int) override;
        void Clear() override;
        size_t GetSize() const override;

        /***************************************************************************************************************
         * IWindowContextContainer interface implementation
        /**************************************************************************************************************/

        void Add(std::unique_ptr<IWindowContext> windowContext) override;
        void Remove(int index) override;
        std::unique_ptr<IWindowContext> &Get(int index) override;
        std::unique_ptr<IWindowContext> Take(int index) override;
        void Set(int index, std::unique_ptr<IWindowContext> windowContext) override;
    };
}