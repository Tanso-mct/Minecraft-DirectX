#include "pch.h"

#include "WB_Container/include/MonitorContainer.h"
#pragma comment(lib, WB_Container.lib);

TEST(MonitorContainer, GetContainerType)
{
    std::unique_ptr<WB::IMonitorContainer> container = std::make_unique<WB::MonitorContainer>();
    EXPECT_EQ(container->GetContainerType(), WB::ContainerType::Monitor);
}

TEST(MonitorContainer, Create)
{
    std::unique_ptr<WB::IMonitorContainer> container = std::make_unique<WB::MonitorContainer>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);
}

TEST(MonitorContainer, Clear)
{
    std::unique_ptr<WB::IMonitorContainer> container = std::make_unique<WB::MonitorContainer>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);

    container->Clear();
    EXPECT_EQ(container->GetSize(), 0);
}

TEST(MonitorContainer, Add)
{
    std::unique_ptr<WB::IMonitorContainer> container = std::make_unique<WB::MonitorContainer>();

    container->Add(nullptr);
    EXPECT_EQ(container->GetSize(), 1);
}

TEST(MonitorContainer, Remove)
{
    std::unique_ptr<WB::IMonitorContainer> container = std::make_unique<WB::MonitorContainer>();

    container->Add(nullptr);
    container->Remove(0);
}

TEST(MonitorContainer, Get)
{
    std::unique_ptr<WB::IMonitorContainer> container = std::make_unique<WB::MonitorContainer>();

    container->Add(nullptr);
    std::unique_ptr<WB::IMonitor> &context = container->Get(0);
}

TEST(MonitorContainer, Take)
{
    std::unique_ptr<WB::IMonitorContainer> container = std::make_unique<WB::MonitorContainer>();

    container->Add(nullptr);
    std::unique_ptr<WB::IMonitor> context = container->Take(0);
}

TEST(MonitorContainer, Set)
{
    std::unique_ptr<WB::IMonitorContainer> container = std::make_unique<WB::MonitorContainer>();

    container->Create(2);
    container->Set(0, nullptr);
}



