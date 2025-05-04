#include "pch.h"

#include "WB_Container/include/ImageDataContainer.h"
#pragma comment(lib, WB_Container.lib);

TEST(ImageDataContainer, GetContainerType)
{
    std::unique_ptr<WB::IImageDataContainer> container = std::make_unique<WB::ImageDataContainer>();
    EXPECT_EQ(container->GetContainerType(), WB::ContainerType::ImageData);
}

TEST(ImageDataContainer, Create)
{
    std::unique_ptr<WB::IImageDataContainer> container = std::make_unique<WB::ImageDataContainer>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);
}

TEST(ImageDataContainer, Clear)
{
    std::unique_ptr<WB::IImageDataContainer> container = std::make_unique<WB::ImageDataContainer>();

    container->Create(5);
    EXPECT_EQ(container->GetSize(), 5);

    container->Clear();
    EXPECT_EQ(container->GetSize(), 0);
}

TEST(ImageDataContainer, Add)
{
    std::unique_ptr<WB::IImageDataContainer> container = std::make_unique<WB::ImageDataContainer>();

    container->Add(nullptr);
    EXPECT_EQ(container->GetSize(), 1);
}

TEST(ImageDataContainer, Remove)
{
    std::unique_ptr<WB::IImageDataContainer> container = std::make_unique<WB::ImageDataContainer>();

    container->Add(nullptr);
    container->Remove(0);
}

TEST(ImageDataContainer, Get)
{
    std::unique_ptr<WB::IImageDataContainer> container = std::make_unique<WB::ImageDataContainer>();

    container->Add(nullptr);
    std::unique_ptr<WB::IImageData> &context = container->Get(0);
}

TEST(ImageDataContainer, Take)
{
    std::unique_ptr<WB::IImageDataContainer> container = std::make_unique<WB::ImageDataContainer>();

    container->Add(nullptr);
    std::unique_ptr<WB::IImageData> context = container->Take(0);
}

TEST(ImageDataContainer, Set)
{
    std::unique_ptr<WB::IImageDataContainer> container = std::make_unique<WB::ImageDataContainer>();

    container->Create(2);
    container->Set(0, nullptr);
}



