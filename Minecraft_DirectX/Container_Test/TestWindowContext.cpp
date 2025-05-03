#include "pch.h"

#include "Container/include/WindowContextContainer.h"
#pragma comment(lib, Container.lib);

TEST(WindowContextContainer, GetContainerType)
{
    std::unique_ptr<MCT::IWindowContextContainer> container = std::make_unique<MCT::WindowContextContainer>();
    EXPECT_EQ(container->GetContainerType(), MCT::ContainerType::WindowContext);
}

TEST(WindowContextContainer, Create)
{
    std::unique_ptr<MCT::IWindowContextContainer> container = std::make_unique<MCT::WindowContextContainer>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);
}

TEST(WindowContextContainer, Clear)
{
    std::unique_ptr<MCT::IWindowContextContainer> container = std::make_unique<MCT::WindowContextContainer>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);

    container->Clear();
    EXPECT_EQ(container->GetSize(), 0);
}

TEST(WindowContextContainer, Add)
{
    std::unique_ptr<MCT::IWindowContextContainer> container = std::make_unique<MCT::WindowContextContainer>();

    container->Add(nullptr);
    EXPECT_EQ(container->GetSize(), 1);
}

TEST(WindowContextContainer, Remove)
{
    std::unique_ptr<MCT::IWindowContextContainer> container = std::make_unique<MCT::WindowContextContainer>();

    container->Add(nullptr);
    container->Remove(0);
}

TEST(WindowContextContainer, Get)
{
    std::unique_ptr<MCT::IWindowContextContainer> container = std::make_unique<MCT::WindowContextContainer>();

    container->Add(nullptr);
    std::unique_ptr<MCT::IWindowContext> &context = container->Get(0);
}

TEST(WindowContextContainer, Take)
{
    std::unique_ptr<MCT::IWindowContextContainer> container = std::make_unique<MCT::WindowContextContainer>();

    container->Add(nullptr);
    std::unique_ptr<MCT::IWindowContext> context = container->Take(0);
}

TEST(WindowContextContainer, Set)
{
    std::unique_ptr<MCT::IWindowContextContainer> container = std::make_unique<MCT::WindowContextContainer>();

    container->Create(2);
    container->Set(0, nullptr);
}



