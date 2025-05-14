#include "pch.h"

#include "WB_Container/include/Container.h"
#pragma comment(lib, "WB_Container.lib");

class MockData : public WB::IElement
{
public:
    MockData() = default;
    ~MockData() override = default;
};

TEST(Container, Create)
{
    std::unique_ptr<WB::IContainer> container = std::make_unique<WB::Container>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);
}

TEST(Container, Clear)
{
    std::unique_ptr<WB::IContainer> container = std::make_unique<WB::Container>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);

    container->Clear();
    EXPECT_EQ(container->GetSize(), 0);
}

TEST(Container, Add)
{
    std::unique_ptr<WB::IContainer> container = std::make_unique<WB::Container>();

    container->Add(nullptr);
    EXPECT_EQ(container->GetSize(), 1);
}

TEST(Container, Remove)
{
    std::unique_ptr<WB::IContainer> container = std::make_unique<WB::Container>();

    container->Add(nullptr);
    container->Remove(0);
}

TEST(Container, Get)
{
    std::unique_ptr<WB::IContainer> container = std::make_unique<WB::Container>();

    container->Add(nullptr);
    std::unique_ptr<WB::IElement> &context = container->Get(0);
}

TEST(Container, Take)
{
    std::unique_ptr<WB::IContainer> container = std::make_unique<WB::Container>();

    container->Add(nullptr);
    std::unique_ptr<WB::IElement> context = container->Take(0);
}

TEST(Container, Set)
{
    std::unique_ptr<WB::IContainer> container = std::make_unique<WB::Container>();

    container->Create(2);
    container->Set(0, nullptr);
}



