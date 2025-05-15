#include "pch.h"

#include "WB_Event/include/Event.h"
#include "WB_Event_Test/DummyEvent.h"

#include <memory>

TEST(EventInstTable, Create)
{
    // Create
    std::unique_ptr<WB::IEventInstTable<int, DummyEvent>> eventInstTable 
    = std::make_unique<WB::EventInstTable<int, DummyEvent>>();

    EXPECT_EQ(eventInstTable->GetSize(), 0);
}

TEST(EventInstTable, Add)
{
    // Create
    std::unique_ptr<WB::IEventInstTable<int, DummyEvent>> eventInstTable
    = std::make_unique<WB::EventInstTable<int, DummyEvent>>();

    // Key
    int eventKey = 1;

    // Add
    eventInstTable->Add(eventKey, std::make_unique<DummyEvent>());
    EXPECT_EQ(eventInstTable->GetSize(), 1);

    // Add duplicate key
    eventInstTable->Add(eventKey, std::make_unique<DummyEvent>());
    EXPECT_EQ(eventInstTable->GetSize(), 1);
}

TEST(EventInstTable, Remove)
{
    // Create
    std::unique_ptr<WB::IEventInstTable<int, DummyEvent>> eventInstTable
    = std::make_unique<WB::EventInstTable<int, DummyEvent>>();

    // Key
    int eventKey = 1;

    // Add
    eventInstTable->Add(eventKey, std::make_unique<DummyEvent>());
    EXPECT_EQ(eventInstTable->GetSize(), 1);

    // Remove
    eventInstTable->Remove(eventKey);
    EXPECT_EQ(eventInstTable->GetSize(), 0);

    // Remove non-existing key
    eventInstTable->Remove(2);
}

TEST(EventInstTable, Get)
{
    // Create
    std::unique_ptr<WB::IEventInstTable<int, DummyEvent>> eventInstTable
    = std::make_unique<WB::EventInstTable<int, DummyEvent>>();

    // Key
    int eventKey = 1;

    // Add
    eventInstTable->Add(eventKey, std::make_unique<DummyEvent>());
    EXPECT_EQ(eventInstTable->GetSize(), 1);

    // Get existing key
    std::unique_ptr<DummyEvent>& event = eventInstTable->Get(eventKey);
    EXPECT_NE(event, nullptr);

    // Get non-existing key.
    // std::unique_ptr<DummyEvent>& nonExistingEvent = eventInstTable->Get(2);
    // EXPECT_EQ(nonExistingEvent, nullptr);
}

TEST(EventInstTable, Set)
{
    // Create
    std::unique_ptr<WB::IEventInstTable<int, DummyEvent>> eventInstTable
    = std::make_unique<WB::EventInstTable<int, DummyEvent>>();

    // Key
    int eventKey = 1;

    // Add
    eventInstTable->Add(eventKey, std::make_unique<DummyEvent>());
    EXPECT_EQ(eventInstTable->GetSize(), 1);

    // Set existing key
    eventInstTable->Set(eventKey, std::make_unique<DummyEvent>());
    EXPECT_EQ(eventInstTable->GetSize(), 1);

    // Set non-existing key
    // eventInstTable->Set(2, std::make_unique<DummyEvent>());
}
