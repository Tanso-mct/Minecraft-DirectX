#pragma once

#include "WB_Container/include/config.h"

#include "Interface/Container.h"
#include "Interface/Monitor.h"

#include <vector>
#include <memory>

namespace WB
{
    class CONTAINER_API MonitorContainer : public IMonitorContainer
    {
    private:
        std::vector<std::unique_ptr<IMonitor>> _monitors;
        std::unique_ptr<IMonitor> _empty = nullptr; // Dummy used when returning references

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
         * Container has unique_ptr objects, so it is not copyable or assignable.
        /**************************************************************************************************************/

        MonitorContainer();
        ~MonitorContainer() override;

        MonitorContainer(const MonitorContainer&) = delete;
        MonitorContainer& operator=(const MonitorContainer&) = delete;

        /***************************************************************************************************************
         * IContainer interface implementation
        /**************************************************************************************************************/

        ContainerType GetContainerType() override;

        void Create(unsigned int) override;
        void Clear() override;
        size_t GetSize() const override;

        /***************************************************************************************************************
         * IMonitorContainer interface implementation
        /**************************************************************************************************************/

        void Add(std::unique_ptr<IMonitor> monitor) override;
        void Remove(int index) override;
        std::unique_ptr<IMonitor> &Get(int index) override;
        std::unique_ptr<IMonitor> Take(int index) override;
        void Set(int index, std::unique_ptr<IMonitor> monitor) override;
    };
}