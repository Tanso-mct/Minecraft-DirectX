#include "pch.h"

#include "WB_Event/include/Event.h"
#include "WB_Event_Test/DummyEvent.h"

#include <memory>

TEST(EventInvoker, Create)
{
    // Create instance table
    std::unique_ptr<WB::IEventInstTable<int, DummyEventWithID>> eventInstTable 
    = std::make_unique<WB::EventInstTable<int, DummyEventWithID>>();

    // Keys
    int eventKey = 1;
    bool funcKey = true;

    // Event instance id
    int eventInstId = 1;

    // Add instance to table
    eventInstTable->Add(eventKey, std::make_unique<DummyEventWithID>(eventInstId));
    EXPECT_EQ(eventInstTable->GetSize(), 1);

    // Create function table
    std::unique_ptr<WB::IEventFuncTable<bool, DummyEventWithID, int, float>> eventFuncTable 
    = std::make_unique<WB::EventFuncTable<bool, DummyEventWithID, int, float>>();

    // Add function to table
    eventFuncTable->Add(funcKey, &DummyEventWithID::DummyFunction);
    EXPECT_EQ(eventFuncTable->GetSize(), 1);

    // Create invoker
    std::unique_ptr<WB::IEventInvoker<int, DummyEventWithID, bool, int, float>> eventInvoker
    = std::make_unique<WB::EventInvoker<int, DummyEventWithID, bool, int, float>>
    (
        eventInstTable,
        eventFuncTable
    );
    
    EXPECT_NE(eventInvoker, nullptr);
}

TEST(EventInvoker, Invoke)
{
    // Create instance table
    std::unique_ptr<WB::IEventInstTable<int, DummyEventWithID>> eventInstTable 
    = std::make_unique<WB::EventInstTable<int, DummyEventWithID>>();

    // Keys
    int eventKey = 1;
    bool funcKey = true;

    // Event instance id
    int eventInstId = 1;

    // Add instance to table
    eventInstTable->Add(eventKey, std::make_unique<DummyEventWithID>(eventInstId));
    EXPECT_EQ(eventInstTable->GetSize(), 1);

    // Set null instance. If event invoked, it will crash.
    // eventInstTable->Set(eventKey, nullptr);

    // Create function table
    std::unique_ptr<WB::IEventFuncTable<bool, DummyEventWithID, int, float>> eventFuncTable 
    = std::make_unique<WB::EventFuncTable<bool, DummyEventWithID, int, float>>();

    // Add function to table
    eventFuncTable->Add(funcKey, &DummyEventWithID::DummyFunction);
    EXPECT_EQ(eventFuncTable->GetSize(), 1);

    // Set function to null. If event invoked, it will crash.
    // eventFuncTable->Set(funcKey, nullptr);

    // Create invoker
    std::unique_ptr<WB::IEventInvoker<int, DummyEventWithID, bool, int, float>> eventInvoker
    = std::make_unique<WB::EventInvoker<int, DummyEventWithID, bool, int, float>>
    (
        eventInstTable,
        eventFuncTable
    );
    
    EXPECT_NE(eventInvoker, nullptr);

    // Invoke function
    eventInvoker->Invoke(eventKey, funcKey, 7, 3.14f);
}