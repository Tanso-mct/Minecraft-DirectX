#include "pch.h"

#include "WB_Container/include/SceneContextContainer.h"
#pragma comment(lib, WB_Container.lib);

TEST(SceneContextContainer, GetContainerType)
{
    std::unique_ptr<WB::ISceneContextContainer> container = std::make_unique<WB::SceneContextContainer>();
    EXPECT_EQ(container->GetContainerType(), WB::ContainerType::SceneContext);
}

TEST(SceneContextContainer, Create)
{
    std::unique_ptr<WB::ISceneContextContainer> container = std::make_unique<WB::SceneContextContainer>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);
}

TEST(SceneContextContainer, Clear)
{
    std::unique_ptr<WB::ISceneContextContainer> container = std::make_unique<WB::SceneContextContainer>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);

    container->Clear();
    EXPECT_EQ(container->GetSize(), 0);
}

TEST(SceneContextContainer, Add)
{
    std::unique_ptr<WB::ISceneContextContainer> container = std::make_unique<WB::SceneContextContainer>();

    container->Add(nullptr);
    EXPECT_EQ(container->GetSize(), 1);
}

TEST(SceneContextContainer, Remove)
{
    std::unique_ptr<WB::ISceneContextContainer> container = std::make_unique<WB::SceneContextContainer>();

    container->Add(nullptr);
    container->Remove(0);
}

TEST(SceneContextContainer, Get)
{
    std::unique_ptr<WB::ISceneContextContainer> container = std::make_unique<WB::SceneContextContainer>();

    container->Add(nullptr);
    std::unique_ptr<WB::ISceneContext> &context = container->Get(0);
}

TEST(SceneContextContainer, Take)
{
    std::unique_ptr<WB::ISceneContextContainer> container = std::make_unique<WB::SceneContextContainer>();

    container->Add(nullptr);
    std::unique_ptr<WB::ISceneContext> context = container->Take(0);
}

TEST(SceneContextContainer, Set)
{
    std::unique_ptr<WB::ISceneContextContainer> container = std::make_unique<WB::SceneContextContainer>();

    container->Create(2);
    container->Set(0, nullptr);
}



