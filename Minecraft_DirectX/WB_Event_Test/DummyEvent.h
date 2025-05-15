#pragma once

#include "WB_Event/include/Event.h"

#include <iostream>

class DummyEventWithID
{
private:
    const int _id;
public:
    DummyEventWithID(int id) : _id(id){}
    ~DummyEventWithID() = default;

    WB::EVENT_RETURN DummyFunction(int a, float b)
    {
        std::cout << "DummyFunction ID:" << _id << " called with args:" << a << ", " << b << std::endl;
    }
};

class DummyEvent
{
public:
    DummyEvent() = default;
    ~DummyEvent() = default;

    WB::EVENT_RETURN DummyFunction(int a, float b)
    {
        std::cout << "DummyFunction called with args:" << a << ", " << b << std::endl;
    }
};
