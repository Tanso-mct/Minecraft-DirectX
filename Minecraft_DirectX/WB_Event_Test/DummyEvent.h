#pragma once

#include "WB_Event/include/Event.h"

#include <iostream>

class DummyEventWithID : public WB::IEvent
{
private:
    const int _id;
    bool _isDestroying = false;

public:
    DummyEventWithID(int id) : _id(id)
    {
        std::cout << "DummyEventWithID ID:" << _id << " constructor." << std::endl;
    }

    ~DummyEventWithID()
    {
        std::cout << "DummyEventWithID ID:" << _id << " destructor." << std::endl;
    }

    WB::EVENT_RETURN DummyFunction(int a, float b)
    {
        std::cout << "DummyFunction ID:" << _id << " called with args:" << a << ", " << b << std::endl;
    }

    void Destroy()
    {
        _isDestroying = true;
        std::cout << "DummyEvent ID:" << _id << " is destroying." << std::endl;
    }

    /*******************************************************************************************************************
     * IEvent interface implementation
    /******************************************************************************************************************/
    
    bool IsDestroying() override
    {
        return _isDestroying;
    }
};

class DummyEvent : public WB::IEvent
{
private:
    bool _isDestroying = false;

public:
    DummyEvent()
    {
        std::cout << "DummyEvent constructor." << std::endl;
    }

    ~DummyEvent()
    {
        std::cout << "DummyEvent destructor." << std::endl;
    }

    WB::EVENT_RETURN DummyFunction(int a, float b)
    {
        std::cout << "DummyFunction called with args:" << a << ", " << b << std::endl;
    }

    void Destroy()
    {
        _isDestroying = true;
        std::cout << "DummyEvent is destroying" << std::endl;
    }

    /*******************************************************************************************************************
     * IEvent interface implementation
    /******************************************************************************************************************/

    bool IsDestroying() override
    {
        return _isDestroying;
    }
};
