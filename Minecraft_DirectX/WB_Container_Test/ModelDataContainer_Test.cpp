#include "pch.h"

#include "WB_Container/include/ModelDataContainer.h"
#pragma comment(lib, WB_Container.lib);

TEST(ModelDataContainer, GetContainerType)
{
    std::unique_ptr<WB::IModelDataContainer> container = std::make_unique<WB::ModelDataContainer>();
    EXPECT_EQ(container->GetContainerType(), WB::ContainerType::ModelData);
}

TEST(ModelDataContainer, Create)
{
    std::unique_ptr<WB::IModelDataContainer> container = std::make_unique<WB::ModelDataContainer>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);
}

TEST(ModelDataContainer, Clear)
{
    std::unique_ptr<WB::IModelDataContainer> container = std::make_unique<WB::ModelDataContainer>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);

    container->Clear();
    EXPECT_EQ(container->GetSize(), 0);
}

TEST(ModelDataContainer, Add)
{
    std::unique_ptr<WB::IModelDataContainer> container = std::make_unique<WB::ModelDataContainer>();

    container->Add(nullptr);
    EXPECT_EQ(container->GetSize(), 1);
}

TEST(ModelDataContainer, Remove)
{
    std::unique_ptr<WB::IModelDataContainer> container = std::make_unique<WB::ModelDataContainer>();

    container->Add(nullptr);
    container->Remove(0);
}

TEST(ModelDataContainer, Get)
{
    std::unique_ptr<WB::IModelDataContainer> container = std::make_unique<WB::ModelDataContainer>();

    container->Add(nullptr);
    std::unique_ptr<WB::IModelData> &context = container->Get(0);
}

TEST(ModelDataContainer, Take)
{
    std::unique_ptr<WB::IModelDataContainer> container = std::make_unique<WB::ModelDataContainer>();

    container->Add(nullptr);
    std::unique_ptr<WB::IModelData> context = container->Take(0);
}

TEST(ModelDataContainer, Set)
{
    std::unique_ptr<WB::IModelDataContainer> container = std::make_unique<WB::ModelDataContainer>();

    container->Create(2);
    container->Set(0, nullptr);
}



