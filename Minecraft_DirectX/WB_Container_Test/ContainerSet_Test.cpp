#include "pch.h"

#include "WB_Container/include/ContainerSet.h"

#include <memory>

TEST(ContainerSet, WindowContext)
{
    // Create a ContainerSet instance
    std::unique_ptr<WB::ContainerSet> containerSet = std::make_unique<WB::ContainerSet>();

    // Create a StaticContainer for WindowContext
    std::unique_ptr<WB::IWindowContextContainer> container = std::make_unique<WB::WindowContextContainer>();

    // Set container in the ContainerSet
    containerSet->WindowContextCont() = std::move(container);

    // Get the container from the ContainerSet
    std::unique_ptr<WB::IWindowContextContainer>& retrievedContainer = containerSet->WindowContextCont();

    EXPECT_NE(retrievedContainer, nullptr);
}

TEST(ContainerSet, SceneContext)
{
    // Create a ContainerSet instance
    std::unique_ptr<WB::ContainerSet> containerSet = std::make_unique<WB::ContainerSet>();

    // Create a StaticContainer for SceneContext
    std::unique_ptr<WB::ISceneContextContainer> container = std::make_unique<WB::SceneContextContainer>();

    // Set container in the ContainerSet
    containerSet->SceneContextCont() = std::move(container);

    // Get the container from the ContainerSet
    std::unique_ptr<WB::ISceneContextContainer>& retrievedContainer = containerSet->SceneContextCont();

    EXPECT_NE(retrievedContainer, nullptr);
}

TEST(ContainerSet, Monitor)
{
    // Create a ContainerSet instance
    std::unique_ptr<WB::ContainerSet> containerSet = std::make_unique<WB::ContainerSet>();

    // Create a StaticContainer for Monitor
    std::unique_ptr<WB::IMonitorContainer> container = std::make_unique<WB::MonitorContainer>();

    // Set container in the ContainerSet
    containerSet->MonitorCont() = std::move(container);

    // Get the container from the ContainerSet
    std::unique_ptr<WB::IMonitorContainer>& retrievedContainer = containerSet->MonitorCont();

    EXPECT_NE(retrievedContainer, nullptr);
}

TEST(ContainerSet, ImageData)
{
    // Create a ContainerSet instance
    std::unique_ptr<WB::ContainerSet> containerSet = std::make_unique<WB::ContainerSet>();

    // Create a StaticContainer for ImageData
    std::unique_ptr<WB::IImageDataContainer> container = std::make_unique<WB::ImageDataContainer>();

    // Set container in the ContainerSet
    containerSet->ImageDataCont() = std::move(container);

    // Get the container from the ContainerSet
    std::unique_ptr<WB::IImageDataContainer>& retrievedContainer = containerSet->ImageDataCont();

    EXPECT_NE(retrievedContainer, nullptr);
}

TEST(ContainerSet, SoundData)
{
    // Create a ContainerSet instance
    std::unique_ptr<WB::ContainerSet> containerSet = std::make_unique<WB::ContainerSet>();

    // Create a StaticContainer for SoundData
    std::unique_ptr<WB::ISoundDataContainer> container = std::make_unique<WB::SoundDataContainer>();

    // Set container in the ContainerSet
    containerSet->SoundDataCont() = std::move(container);

    // Get the container from the ContainerSet
    std::unique_ptr<WB::ISoundDataContainer>& retrievedContainer = containerSet->SoundDataCont();

    EXPECT_NE(retrievedContainer, nullptr);
}

TEST(ContainerSet, ModelData)
{
    // Create a ContainerSet instance
    std::unique_ptr<WB::ContainerSet> containerSet = std::make_unique<WB::ContainerSet>();

    // Create a StaticContainer for ModelData
    std::unique_ptr<WB::IModelDataContainer> container = std::make_unique<WB::ModelDataContainer>();

    // Set container in the ContainerSet
    containerSet->ModelDataCont() = std::move(container);

    // Get the container from the ContainerSet
    std::unique_ptr<WB::IModelDataContainer>& retrievedContainer = containerSet->ModelDataCont();

    EXPECT_NE(retrievedContainer, nullptr);
}

TEST(ContainerSet, CsvData)
{
    // Create a ContainerSet instance
    std::unique_ptr<WB::ContainerSet> containerSet = std::make_unique<WB::ContainerSet>();

    // Create a StaticContainer for CsvData
    std::unique_ptr<WB::ICsvDataContainer> container = std::make_unique<WB::CsvDataContainer>();

    // Set container in the ContainerSet
    containerSet->CsvDataCont() = std::move(container);

    // Get the container from the ContainerSet
    std::unique_ptr<WB::ICsvDataContainer>& retrievedContainer = containerSet->CsvDataCont();

    EXPECT_NE(retrievedContainer, nullptr);
}
