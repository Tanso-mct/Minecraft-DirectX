#include "pch.h"

#include "WB_Container/include/Container.h"

#include <iostream>

class DummyData
{
public:
    DummyData() = default;
    ~DummyData() = default;

    void DoSomething()
    {
        std::cout << "Doing something!" << std::endl;
    }
};

TEST(DynamicContainer, Create)
{
    std::unique_ptr<WB::DynamicContainer<DummyData>> container 
    = std::make_unique<WB::DynamicContainer<DummyData>>();

    container->Create(10);
    EXPECT_EQ(container->GetSize(), 10);

    // container->Create(10); // Attempt to create again
}

TEST(DynamicContainer, Clear)
{
    std::unique_ptr<WB::DynamicContainer<DummyData>> container 
    = std::make_unique<WB::DynamicContainer<DummyData>>();

    container->Create(10);
    EXPECT_EQ(container->GetSize(), 10);

    container->Clear();
    EXPECT_EQ(container->GetSize(), 0);
}

TEST(DynamicContainer, Resize)
{
    std::unique_ptr<WB::DynamicContainer<DummyData>> container 
    = std::make_unique<WB::DynamicContainer<DummyData>>();

    container->Create(10);
    EXPECT_EQ(container->GetSize(), 10);

    container->Resize(20);
    EXPECT_EQ(container->GetSize(), 20);

    // container->Resize(-5); // Attempt to resize to negative size
}

TEST(DynamicContainer, PushBack)
{
    std::unique_ptr<WB::DynamicContainer<DummyData>> container 
    = std::make_unique<WB::DynamicContainer<DummyData>>();

    container->Create(10);
    EXPECT_EQ(container->GetSize(), 10);

    std::unique_ptr<DummyData> data = std::make_unique<DummyData>();
    int index = container->PushBack(std::move(data));

    EXPECT_EQ(index, 10); // New element should be at index 10
    EXPECT_EQ(container->GetSize(), 11);
}

TEST(DynamicContainer, PopBack)
{
    std::unique_ptr<WB::DynamicContainer<DummyData>> container 
    = std::make_unique<WB::DynamicContainer<DummyData>>();

    container->Create(10);
    EXPECT_EQ(container->GetSize(), 10);

    std::unique_ptr<DummyData> data = std::make_unique<DummyData>();
    container->PushBack(std::move(data));

    std::unique_ptr<DummyData> poppedData = container->PopBack();
    poppedData->DoSomething(); // Call a method on the popped data

    EXPECT_NE(poppedData, nullptr); // Popped data should not be null
    EXPECT_EQ(container->GetSize(), 10);
}

TEST(DynamicContainer, Set)
{
    std::unique_ptr<WB::DynamicContainer<DummyData>> container 
    = std::make_unique<WB::DynamicContainer<DummyData>>();

    container->Create(10);
    EXPECT_EQ(container->GetSize(), 10);

    std::unique_ptr<DummyData> data = std::make_unique<DummyData>();
    container->Set(0, std::move(data));

    // container->Set(10, std::make_unique<DummyData>()); // Attempt to set out of bounds
}

TEST(DynamicContainer, Get)
{
    std::unique_ptr<WB::DynamicContainer<DummyData>> container 
    = std::make_unique<WB::DynamicContainer<DummyData>>();

    container->Create(10);
    EXPECT_EQ(container->GetSize(), 10);

    std::unique_ptr<DummyData> data = std::make_unique<DummyData>();
    container->Set(0, std::move(data));

    std::unique_ptr<DummyData>& retrievedData = container->Get(0);
    EXPECT_NE(retrievedData, nullptr); // Retrieved data should not be null

    retrievedData->DoSomething();
}

TEST(DynamicContainer, Release)
{
    std::unique_ptr<WB::DynamicContainer<DummyData>> container 
    = std::make_unique<WB::DynamicContainer<DummyData>>();

    container->Create(10);
    EXPECT_EQ(container->GetSize(), 10);

    std::unique_ptr<DummyData> data = std::make_unique<DummyData>();
    container->Set(0, std::move(data));

    std::unique_ptr<DummyData> releasedData = container->Release(0);
    EXPECT_NE(releasedData, nullptr); // Released data should not be null

    releasedData->DoSomething();
}

