#include "pch.h"

#include "WB_Container/include/WindowContextContainer.h"
#pragma comment(lib, WB_Container.lib);

TEST(WindowContextContainer, GetContainerType)
{
    std::unique_ptr<WB::IWindowContextContainer> container = std::make_unique<WB::WindowContextContainer>();
    EXPECT_EQ(container->GetContainerType(), WB::ContainerType::WindowContext);
}

TEST(WindowContextContainer, Create)
{
    std::unique_ptr<WB::IWindowContextContainer> container = std::make_unique<WB::WindowContextContainer>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);
}

TEST(WindowContextContainer, Clear)
{
    std::unique_ptr<WB::IWindowContextContainer> container = std::make_unique<WB::WindowContextContainer>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);

    container->Clear();
    EXPECT_EQ(container->GetSize(), 0);
}

TEST(WindowContextContainer, Add)
{
    std::unique_ptr<WB::IWindowContextContainer> container = std::make_unique<WB::WindowContextContainer>();

    container->Add(nullptr);
    EXPECT_EQ(container->GetSize(), 1);
}

TEST(WindowContextContainer, Remove)
{
    std::unique_ptr<WB::IWindowContextContainer> container = std::make_unique<WB::WindowContextContainer>();

    container->Add(nullptr);
    container->Remove(0);
}

TEST(WindowContextContainer, Get)
{
    std::unique_ptr<WB::IWindowContextContainer> container = std::make_unique<WB::WindowContextContainer>();

    container->Add(nullptr);
    std::unique_ptr<WB::IWindowContext> &context = container->Get(0);
}

TEST(WindowContextContainer, Take)
{
    std::unique_ptr<WB::IWindowContextContainer> container = std::make_unique<WB::WindowContextContainer>();

    container->Add(nullptr);
    std::unique_ptr<WB::IWindowContext> context = container->Take(0);
}

TEST(WindowContextContainer, Set)
{
    std::unique_ptr<WB::IWindowContextContainer> container = std::make_unique<WB::WindowContextContainer>();

    container->Create(2);
    container->Set(0, nullptr);
}



