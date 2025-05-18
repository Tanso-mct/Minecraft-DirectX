#include "pch.h"

#include "WB_Container/include/ContainerSet.h"

#include <memory>

TEST(ContainerSet, WindowContext)
{
    // Create a ContainerSet instance
    std::unique_ptr<WB::ContainerSet> containerSet = std::make_unique<WB::ContainerSet>();

    // Create a StaticContainer for WindowContext
    std::unique_ptr<WB::WindowContextContainer> container = std::make_unique<WB::WindowContextContainer>();

    // Set container in the ContainerSet
    containerSet->Container<WB::IWindowContext, WB::WindowID>() = std::move(container);

    // Get the container from the ContainerSet
    std::unique_ptr<WB::WindowContextContainer>& retrievedContainer 
    = containerSet->Container<WB::IWindowContext, WB::WindowID>();

    EXPECT_NE(retrievedContainer, nullptr);
}

TEST(ContainerSet, Monitor)
{
    // Create a ContainerSet instance
    std::unique_ptr<WB::ContainerSet> containerSet = std::make_unique<WB::ContainerSet>();

    // Create a StaticContainer for Monitor
    std::unique_ptr<WB::MonitorContainer> container = std::make_unique<WB::MonitorContainer>();

    // Set container in the ContainerSet
    containerSet->Container<WB::IMonitor, WB::MonitorID>() = std::move(container);

    // Get the container from the ContainerSet
    std::unique_ptr<WB::MonitorContainer>& retrievedContainer 
    = containerSet->Container<WB::IMonitor, WB::MonitorID>();

    EXPECT_NE(retrievedContainer, nullptr);
}

TEST(ContainerSet, Image)
{
    // Create a ContainerSet instance
    std::unique_ptr<WB::ContainerSet> containerSet = std::make_unique<WB::ContainerSet>();

    // Create a StaticContainer for Image
    std::unique_ptr<WB::ImageDataContainer> container = std::make_unique<WB::ImageDataContainer>();

    // Set container in the ContainerSet
    containerSet->Container<WB::IImageData, WB::ImageID>() = std::move(container);

    // Get the container from the ContainerSet
    std::unique_ptr<WB::ImageDataContainer>& retrievedContainer 
    = containerSet->Container<WB::IImageData, WB::ImageID>();

    EXPECT_NE(retrievedContainer, nullptr);
}

TEST(ContainerSet, Sound)
{
    // Create a ContainerSet instance
    std::unique_ptr<WB::ContainerSet> containerSet = std::make_unique<WB::ContainerSet>();

    // Create a StaticContainer for Sound
    std::unique_ptr<WB::SoundDataContainer> container = std::make_unique<WB::SoundDataContainer>();

    // Set container in the ContainerSet
    containerSet->Container<WB::ISoundData, WB::SoundID>() = std::move(container);

    // Get the container from the ContainerSet
    std::unique_ptr<WB::SoundDataContainer>& retrievedContainer 
    = containerSet->Container<WB::ISoundData, WB::SoundID>();

    EXPECT_NE(retrievedContainer, nullptr);
}

TEST(ContainerSet, Model)
{
    // Create a ContainerSet instance
    std::unique_ptr<WB::ContainerSet> containerSet = std::make_unique<WB::ContainerSet>();

    // Create a StaticContainer for Model
    std::unique_ptr<WB::ModelDataContainer> container = std::make_unique<WB::ModelDataContainer>();

    // Set container in the ContainerSet
    containerSet->Container<WB::IModelData, WB::ModelID>() = std::move(container);

    // Get the container from the ContainerSet
    std::unique_ptr<WB::ModelDataContainer>& retrievedContainer 
    = containerSet->Container<WB::IModelData, WB::ModelID>();

    EXPECT_NE(retrievedContainer, nullptr);
}

TEST(ContainerSet, Csv)
{
    // Create a ContainerSet instance
    std::unique_ptr<WB::ContainerSet> containerSet = std::make_unique<WB::ContainerSet>();

    // Create a StaticContainer for CSV
    std::unique_ptr<WB::CsvDataContainer> container = std::make_unique<WB::CsvDataContainer>();

    // Set container in the ContainerSet
    containerSet->Container<WB::ICsvData, WB::CsvID>() = std::move(container);

    // Get the container from the ContainerSet
    std::unique_ptr<WB::CsvDataContainer>& retrievedContainer 
    = containerSet->Container<WB::ICsvData, WB::CsvID>();

    EXPECT_NE(retrievedContainer, nullptr);
}

class DummyData
{
public:
    DummyData() = default;
    ~DummyData() = default;
};

enum class DummyID
{
    Example,
    Size,
};

TEST(ContainerSet, Invalid)
{
    // Create a ContainerSet instance
    std::unique_ptr<WB::ContainerSet> containerSet = std::make_unique<WB::ContainerSet>();

    // Create a StaticContainer for DummyData
    std::unique_ptr<WB::StaticContainer<DummyData, DummyID>> container
    = std::make_unique<WB::StaticContainer<DummyData, DummyID>>();

    // Set container in the ContainerSet. This should be invalid.
    // containerSet->Container<DummyData, DummyID>() = std::move(container);

    // Get the container from the ContainerSet. This should be invalid.
    // std::unique_ptr<WB::StaticContainer<DummyData, DummyID>>& retrievedContainer
    // = containerSet->Container<DummyData, DummyID>();
}
