#include "pch.h"

#include "WB_Event/include/Event.h"

#include <memory>

class DummyEventInst
{
public:
    DummyEventInst() = default;
    ~DummyEventInst() = default;

    float DummyFunction(int a, float b)
    {
        std::cout << "DummyFunction called with args: " << a << ", " << b << std::endl;
        return a + b;
    }
};

TEST(EventFuncTable, Create)
{
    // Create
    std::unique_ptr<WB::IEventFuncTable<int, DummyEventInst, float, int, float>> eventFuncTable 
    = std::make_unique<WB::EventFuncTable<int, DummyEventInst, float, int, float>>();
    
    EXPECT_EQ(eventFuncTable->GetSize(), 0);
}

TEST(EventFuncTable, Add)
{
    // Create
    std::unique_ptr<WB::IEventFuncTable<int, DummyEventInst, float, int, float>> eventFuncTable
    = std::make_unique<WB::EventFuncTable<int, DummyEventInst, float, int, float>>();
    
    // Add
    eventFuncTable->Add(1, &DummyEventInst::DummyFunction);
    EXPECT_EQ(eventFuncTable->GetSize(), 1);
    
    // Add duplicate key
    eventFuncTable->Add(1, &DummyEventInst::DummyFunction);
    EXPECT_EQ(eventFuncTable->GetSize(), 1);
}

TEST(EventFuncTable, Remove)
{
    // Create
    std::unique_ptr<WB::IEventFuncTable<int, DummyEventInst, float, int, float>> eventFuncTable
    = std::make_unique<WB::EventFuncTable<int, DummyEventInst, float, int, float>>();
    
    // Add
    eventFuncTable->Add(1, &DummyEventInst::DummyFunction);
    EXPECT_EQ(eventFuncTable->GetSize(), 1);
    
    // Remove
    eventFuncTable->Remove(1);
    EXPECT_EQ(eventFuncTable->GetSize(), 0);
    
    // Remove non-existing key
    eventFuncTable->Remove(2);
}

TEST(EventFuncTable, Get)
{
    // Create
    std::unique_ptr<WB::IEventFuncTable<int, DummyEventInst, float, int, float>> eventFuncTable
    = std::make_unique<WB::EventFuncTable<int, DummyEventInst, float, int, float>>();
    
    // Add
    eventFuncTable->Add(1, &DummyEventInst::DummyFunction);
    EXPECT_EQ(eventFuncTable->GetSize(), 1);
    
    // Get
    float (DummyEventInst::*func)(int, float) = eventFuncTable->Get(1);

    DummyEventInst dummyInst;
    float value = (dummyInst.*func)(7, 3.14f); // Call the function with dummy instance

    EXPECT_FLOAT_EQ(value, 10.14f); // Check if the result is correct
    
    // Get non-existing key
    auto func2 = eventFuncTable->Get(2);
    EXPECT_EQ(func2, nullptr);
}