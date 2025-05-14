#include "pch.h"

#include "WB_Event/include/Event.h"

#include <memory>

class DummyEventInst
{
public:
    DummyEventInst() = default;
    ~DummyEventInst() = default;

    void DummyFunction(int a, float b)
    {
        std::cout << "DummyFunction called with args: " << a << ", " << b << std::endl;
    }
};

TEST(EventInstTable, Create)
{
    // Create
    std::unique_ptr<WB::IEventInstTable<int, DummyEventInst>> eventInstTable 
    = std::make_unique<WB::EventInstTable<int, DummyEventInst>>();

    EXPECT_EQ(eventInstTable->GetSize(), 0);
}

TEST(EventInstTable, Add)
{
    // Create
    std::unique_ptr<WB::IEventInstTable<int, DummyEventInst>> eventInstTable
    = std::make_unique<WB::EventInstTable<int, DummyEventInst>>();

    // Add
    eventInstTable->Add(1, std::make_unique<DummyEventInst>());
    EXPECT_EQ(eventInstTable->GetSize(), 1);

    // Add duplicate key
    eventInstTable->Add(1, std::make_unique<DummyEventInst>());
    EXPECT_EQ(eventInstTable->GetSize(), 1);
}

TEST(EventInstTable, Remove)
{
    // Create
    std::unique_ptr<WB::IEventInstTable<int, DummyEventInst>> eventInstTable
    = std::make_unique<WB::EventInstTable<int, DummyEventInst>>();

    // Add
    eventInstTable->Add(1, std::make_unique<DummyEventInst>());
    EXPECT_EQ(eventInstTable->GetSize(), 1);

    // Remove
    eventInstTable->Remove(1);
    EXPECT_EQ(eventInstTable->GetSize(), 0);

    // Remove non-existing key
    eventInstTable->Remove(2);
}

TEST(EventInstTable, Get)
{
    // Create
    std::unique_ptr<WB::IEventInstTable<int, DummyEventInst>> eventInstTable
    = std::make_unique<WB::EventInstTable<int, DummyEventInst>>();

    // Add
    eventInstTable->Add(1, std::make_unique<DummyEventInst>());
    EXPECT_EQ(eventInstTable->GetSize(), 1);

    // Get existing key
    std::unique_ptr<DummyEventInst>& event = eventInstTable->Get(1);
    EXPECT_NE(event, nullptr);

    // Get non-existing key.
    // std::unique_ptr<DummyEventInst>& nonExistingEvent = eventInstTable->Get(2);
    // EXPECT_EQ(nonExistingEvent, nullptr);
}

TEST(EventInstTable, Set)
{
    // Create
    std::unique_ptr<WB::IEventInstTable<int, DummyEventInst>> eventInstTable
    = std::make_unique<WB::EventInstTable<int, DummyEventInst>>();

    // Add
    eventInstTable->Add(1, std::make_unique<DummyEventInst>());
    EXPECT_EQ(eventInstTable->GetSize(), 1);

    // Set existing key
    eventInstTable->Set(1, std::make_unique<DummyEventInst>());
    EXPECT_EQ(eventInstTable->GetSize(), 1);

    // Set non-existing key
    // eventInstTable->Set(2, std::make_unique<DummyEventInst>());
}
