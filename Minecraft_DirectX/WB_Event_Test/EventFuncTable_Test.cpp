#include "pch.h"

#include "WB_Event/include/Event.h"
#include "WB_Event_Test/DummyEvent.h"

#include <memory>

TEST(EventFuncTable, Create)
{
    // Create
    std::unique_ptr<WB::IEventFuncTable<int, DummyEvent, int, float>> eventFuncTable 
    = std::make_unique<WB::EventFuncTable<int, DummyEvent, int, float>>();
    
    EXPECT_EQ(eventFuncTable->GetSize(), 0);
}

TEST(EventFuncTable, Add)
{
    // Create
    std::unique_ptr<WB::IEventFuncTable<int, DummyEvent, int, float>> eventFuncTable
    = std::make_unique<WB::EventFuncTable<int, DummyEvent, int, float>>();

    // Key
    int funcKey = 1;
    
    // Add
    eventFuncTable->Add(funcKey, &DummyEvent::DummyFunction);
    EXPECT_EQ(eventFuncTable->GetSize(), 1);
    
    // Add duplicate key
    eventFuncTable->Add(funcKey, &DummyEvent::DummyFunction);
    EXPECT_EQ(eventFuncTable->GetSize(), 1);
}

TEST(EventFuncTable, Remove)
{
    // Create
    std::unique_ptr<WB::IEventFuncTable<int, DummyEvent, int, float>> eventFuncTable
    = std::make_unique<WB::EventFuncTable<int, DummyEvent, int, float>>();

    // Key
    int funcKey = 1;
    
    // Add
    eventFuncTable->Add(funcKey, &DummyEvent::DummyFunction);
    EXPECT_EQ(eventFuncTable->GetSize(), 1);
    
    // Remove
    eventFuncTable->Remove(funcKey);
    EXPECT_EQ(eventFuncTable->GetSize(), 0);
    
    // Remove non-existing key
    eventFuncTable->Remove(2);
}

TEST(EventFuncTable, Get)
{
    // Create
    std::unique_ptr<WB::IEventFuncTable<int, DummyEvent, int, float>> eventFuncTable
    = std::make_unique<WB::EventFuncTable<int, DummyEvent, int, float>>();

    // Key
    int funcKey = 1;
    
    // Add
    eventFuncTable->Add(funcKey, &DummyEvent::DummyFunction);
    EXPECT_EQ(eventFuncTable->GetSize(), 1);
    
    // Get
    WB::EVENT_RETURN (DummyEvent::*func)(int, float) = eventFuncTable->Get(funcKey);

    DummyEvent dummyInst;
    (dummyInst.*func)(7, 3.14f); // Call the function with dummy instance

    // Get non-existing key
    // float (DummyEvent::*func2)(int, float) = eventFuncTable->Get(2);
}

TEST(EventFuncTable, Set)
{
    // Create
    std::unique_ptr<WB::IEventFuncTable<int, DummyEvent, int, float>> eventFuncTable
    = std::make_unique<WB::EventFuncTable<int, DummyEvent, int, float>>();

    // Key
    int funcKey = 1;
    
    // Add
    eventFuncTable->Add(funcKey, &DummyEvent::DummyFunction);
    EXPECT_EQ(eventFuncTable->GetSize(), 1);
    
    // Set
    eventFuncTable->Set(funcKey, &DummyEvent::DummyFunction);
    EXPECT_EQ(eventFuncTable->GetSize(), 1);

    // Set non-existing key
    // eventFuncTable->Set(2, &DummyEvent::DummyFunction);
}