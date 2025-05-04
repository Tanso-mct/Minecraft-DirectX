#include "pch.h"

#include "WB_Container/include/JsonDataContainer.h"
#pragma comment(lib, WB_Container.lib);

TEST(JsonDataContainer, GetContainerType)
{
    std::unique_ptr<WB::IJsonDataContainer> container = std::make_unique<WB::JsonDataContainer>();
    EXPECT_EQ(container->GetContainerType(), WB::ContainerType::JsonData);
}

TEST(JsonDataContainer, Create)
{
    std::unique_ptr<WB::IJsonDataContainer> container = std::make_unique<WB::JsonDataContainer>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);
}

TEST(JsonDataContainer, Clear)
{
    std::unique_ptr<WB::IJsonDataContainer> container = std::make_unique<WB::JsonDataContainer>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);

    container->Clear();
    EXPECT_EQ(container->GetSize(), 0);
}

TEST(JsonDataContainer, Add)
{
    std::unique_ptr<WB::IJsonDataContainer> container = std::make_unique<WB::JsonDataContainer>();

    container->Add(nullptr);
    EXPECT_EQ(container->GetSize(), 1);
}

TEST(JsonDataContainer, Remove)
{
    std::unique_ptr<WB::IJsonDataContainer> container = std::make_unique<WB::JsonDataContainer>();

    container->Add(nullptr);
    container->Remove(0);
}

TEST(JsonDataContainer, Get)
{
    std::unique_ptr<WB::IJsonDataContainer> container = std::make_unique<WB::JsonDataContainer>();

    container->Add(nullptr);
    std::unique_ptr<WB::IJsonData> &context = container->Get(0);
}

TEST(JsonDataContainer, Take)
{
    std::unique_ptr<WB::IJsonDataContainer> container = std::make_unique<WB::JsonDataContainer>();

    container->Add(nullptr);
    std::unique_ptr<WB::IJsonData> context = container->Take(0);
}

TEST(JsonDataContainer, Set)
{
    std::unique_ptr<WB::IJsonDataContainer> container = std::make_unique<WB::JsonDataContainer>();

    container->Create(2);
    container->Set(0, nullptr);
}



