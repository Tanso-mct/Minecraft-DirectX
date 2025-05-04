#include "pch.h"

#include "WB_Container/include/SoundDataContainer.h"
#pragma comment(lib, WB_Container.lib);

TEST(SoundDataContainer, GetContainerType)
{
    std::unique_ptr<WB::ISoundDataContainer> container = std::make_unique<WB::SoundDataContainer>();
    EXPECT_EQ(container->GetContainerType(), WB::ContainerType::SoundData);
}

TEST(SoundDataContainer, Create)
{
    std::unique_ptr<WB::ISoundDataContainer> container = std::make_unique<WB::SoundDataContainer>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);
}

TEST(SoundDataContainer, Clear)
{
    std::unique_ptr<WB::ISoundDataContainer> container = std::make_unique<WB::SoundDataContainer>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);

    container->Clear();
    EXPECT_EQ(container->GetSize(), 0);
}

TEST(SoundDataContainer, Add)
{
    std::unique_ptr<WB::ISoundDataContainer> container = std::make_unique<WB::SoundDataContainer>();

    container->Add(nullptr);
    EXPECT_EQ(container->GetSize(), 1);
}

TEST(SoundDataContainer, Remove)
{
    std::unique_ptr<WB::ISoundDataContainer> container = std::make_unique<WB::SoundDataContainer>();

    container->Add(nullptr);
    container->Remove(0);
}

TEST(SoundDataContainer, Get)
{
    std::unique_ptr<WB::ISoundDataContainer> container = std::make_unique<WB::SoundDataContainer>();

    container->Add(nullptr);
    std::unique_ptr<WB::ISoundData> &context = container->Get(0);
}

TEST(SoundDataContainer, Take)
{
    std::unique_ptr<WB::ISoundDataContainer> container = std::make_unique<WB::SoundDataContainer>();

    container->Add(nullptr);
    std::unique_ptr<WB::ISoundData> context = container->Take(0);
}

TEST(SoundDataContainer, Set)
{
    std::unique_ptr<WB::ISoundDataContainer> container = std::make_unique<WB::SoundDataContainer>();

    container->Create(2);
    container->Set(0, nullptr);
}



