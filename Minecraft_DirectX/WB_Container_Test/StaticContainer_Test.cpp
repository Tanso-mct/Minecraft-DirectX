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

enum class DummyDataID
{
    A,
    B,
    C,
    Size,
};

TEST(StaticContainer, Create)
{
    std::unique_ptr<WB::StaticContainer<DummyData, DummyDataID>> container 
    = std::make_unique<WB::StaticContainer<DummyData, DummyDataID>>();

    container->Create(DummyDataID::Size);
    EXPECT_EQ(container->GetSize(), static_cast<int>(DummyDataID::Size));

    // container->Create(DummyDataID::Size); // Attempt to create again
}

TEST(StaticContainer, Clear)
{
    std::unique_ptr<WB::StaticContainer<DummyData, DummyDataID>> container 
    = std::make_unique<WB::StaticContainer<DummyData, DummyDataID>>();

    container->Create(DummyDataID::Size);
    EXPECT_EQ(container->GetSize(), static_cast<int>(DummyDataID::Size));

    container->Clear();
    EXPECT_EQ(container->GetSize(), 0);
}

TEST(StaticContainer, Set)
{
    std::unique_ptr<WB::StaticContainer<DummyData, DummyDataID>> container 
    = std::make_unique<WB::StaticContainer<DummyData, DummyDataID>>();

    container->Create(DummyDataID::Size);
    EXPECT_EQ(container->GetSize(), static_cast<int>(DummyDataID::Size));

    container->Set(DummyDataID::A, std::make_unique<DummyData>());

    // container->Set(DummyDataID::Size, std::make_unique<DummyData>()); // Attempt to set out of bounds
}

TEST(StaticContainer, Get)
{
    std::unique_ptr<WB::StaticContainer<DummyData, DummyDataID>> container 
    = std::make_unique<WB::StaticContainer<DummyData, DummyDataID>>();

    container->Create(DummyDataID::Size);
    EXPECT_EQ(container->GetSize(), static_cast<int>(DummyDataID::Size));

    container->Set(DummyDataID::A, std::make_unique<DummyData>());
    
    std::unique_ptr<DummyData>& data = container->Get(DummyDataID::A);
    EXPECT_NE(data, nullptr);

    data->DoSomething();

    // std::unique_ptr<DummyData>& invalidData = container->Get(DummyDataID::Size); // Attempt to get out of bounds
}

TEST(StaticContainer, Release)
{
    std::unique_ptr<WB::StaticContainer<DummyData, DummyDataID>> container 
    = std::make_unique<WB::StaticContainer<DummyData, DummyDataID>>();

    container->Create(DummyDataID::Size);
    EXPECT_EQ(container->GetSize(), static_cast<int>(DummyDataID::Size));

    container->Set(DummyDataID::A, std::make_unique<DummyData>());
    
    std::unique_ptr<DummyData> data = container->Release(DummyDataID::A);
    EXPECT_NE(data, nullptr);

    data->DoSomething();

    // std::unique_ptr<DummyData> invalidData = container->Release(DummyDataID::Size); // Attempt to release out of bounds
}



