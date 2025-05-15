#pragma once

#include "Interface/Event.h"

#include "WB_ConsoleLog/include/ConsoleLog.h"
#pragma comment(lib, "WB_ConsoleLog.lib")

#include "WB_Utility/include/ErrorHandling.h"
#pragma comment(lib, "WB_Utility.lib")

#include <memory>
#include <unordered_map>

namespace WBEvent
{
    inline std::unique_ptr<WB::IConsoleLog> &ConsoleLog()
    {
        static std::unique_ptr<WB::IConsoleLog> consoleLog = std::make_unique<WB::ConsoleLog>
        (
            WB::ConsoleLogConfig
            (
                "WB_Container",
                "\033[0m", // Normal color
                "\033[31m", // Red color
                "\033[33m"  // Yellow color
            )
        );
        
        return consoleLog;
    }
}

namespace WB
{
    template <typename EVENT_KEY, typename EVENT>
    class EventInstTable : public IEventInstTable<EVENT_KEY, EVENT>
    {
    private:
        std::unordered_map<EVENT_KEY, std::unique_ptr<EVENT>> _eventMap;
        std::unique_ptr<EVENT> _empty = nullptr; // Dummy used when returning references

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
         * EventInstTable has unique_ptr objects, so it is not copyable or assignable.
        /**************************************************************************************************************/

        EventInstTable()
        {
#ifndef NDEBUG
            WBEvent::ConsoleLog()->Log({"EventInstTable Constructor : Created event instance table"});
#endif
        }

        ~EventInstTable() override
        {
#ifndef NDEBUG
            WBEvent::ConsoleLog()->Log({"EventInstTable Destructor : Destroyed event instance table"});
#endif
        }

        EventInstTable(const EventInstTable&) = delete;
        EventInstTable& operator=(const EventInstTable&) = delete;

        /***************************************************************************************************************
         * IEventInstTable interface implementation
        /**************************************************************************************************************/

        void Clear() override
        {
            _eventMap.clear();

#ifndef NDEBUG
            WBEvent::ConsoleLog()->Log({"EventInstTable Clear : Cleared event instance table"});
#endif
        }

        bool Has(EVENT_KEY key) const override
        {
            return _eventMap.find(key) != _eventMap.end();
        }

        size_t GetSize() const override
        {
            return _eventMap.size();
        }

        void Add(EVENT_KEY key, std::unique_ptr<EVENT> event) override
        {
            if (Has(key))
            {
                WBEvent::ConsoleLog()->LogWrn({"EventInstTable Add : Key already exists"});
                return; // Key already exists
            }

            _eventMap[key] = std::move(event);

#ifndef NDEBUG
            WBEvent::ConsoleLog()->Log({"EventInstTable Add : Added event instance"});
#endif
        }

        void Remove(EVENT_KEY key) override
        {
            if (!Has(key))
            {
                WBEvent::ConsoleLog()->LogWrn({"EventInstTable Remove : Key does not exist"});
                return; // Key does not exist
            }

            _eventMap.erase(key);

#ifndef NDEBUG
            WBEvent::ConsoleLog()->Log({"EventInstTable Remove : Removed event instance"});
#endif
        }

        std::unique_ptr<EVENT>& Get(EVENT_KEY key) override
        {
            if (!Has(key))
            {
                std::string err = WBEvent::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"EventInstTable Get : Key does not exist"}
                );
                WB::MessageBoxError(WBEvent::ConsoleLog()->GetName(), err);

                return _empty; // Key does not exist
            }

#ifndef NDEBUG
            WBEvent::ConsoleLog()->Log({"EventInstTable Get : Getting event instance"});
#endif
            return _eventMap[key]; // Return the unique_ptr reference
        }

        void Set(EVENT_KEY key, std::unique_ptr<EVENT> event) override
        {
            if (!Has(key))
            {
                std::string err = WBEvent::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"EventInstTable Set : Key does not exist"}
                );
                WB::MessageBoxError(WBEvent::ConsoleLog()->GetName(), err);

                return; // Key does not exist
            }

            _eventMap[key] = std::move(event);
            
#ifndef NDEBUG
            WBEvent::ConsoleLog()->Log({"EventInstTable Set : Set event instance"});
#endif
        }        
    };

    template <typename FUNC_KEY, typename EVENT, typename... ARGS>
    class EventFuncTable : public IEventFuncTable<FUNC_KEY, EVENT, ARGS...>
    {
    private:
        std::unordered_map<FUNC_KEY, EVENT_RETURN (EVENT::*)(ARGS...)> _funcMap;
        EVENT_RETURN (EVENT::*_empty) (ARGS...) = nullptr; // Dummy used when returning references

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
         * EventFuncTable has unique_ptr objects, so it is not copyable or assignable.
        /**************************************************************************************************************/

        EventFuncTable()
        {
#ifndef NDEBUG
            WBEvent::ConsoleLog()->Log({"EventFuncTable Constructor : Created event function table"});
#endif
        }

        ~EventFuncTable() override
        {
#ifndef NDEBUG
            WBEvent::ConsoleLog()->Log({"EventFuncTable Destructor : Destroyed event function table"});
#endif
        }

        EventFuncTable(const EventFuncTable&) = delete;
        EventFuncTable& operator=(const EventFuncTable&) = delete;

        /***************************************************************************************************************
         * IEventFuncTable interface implementation
        /**************************************************************************************************************/

        void Clear() override
        {
            _funcMap.clear();

#ifndef NDEBUG
            WBEvent::ConsoleLog()->Log({"EventFuncTable Clear : Cleared event function table"});
#endif
        }

        bool Has(FUNC_KEY key) const override
        {
            return _funcMap.find(key) != _funcMap.end();
        }

        size_t GetSize() const override
        {
            return _funcMap.size();
        }

        void Add(FUNC_KEY key, EVENT_RETURN (EVENT::*func)(ARGS...)) override
        {
            if (Has(key))
            {
                WBEvent::ConsoleLog()->LogWrn({"EventFuncTable Add : Key already exists"});
                return; // Key already exists
            }

            _funcMap[key] = func;

#ifndef NDEBUG
            WBEvent::ConsoleLog()->Log({"EventFuncTable Add : Added event function"});
#endif
        }

        void Remove(FUNC_KEY key) override
        {
            if (!Has(key))
            {
                WBEvent::ConsoleLog()->LogWrn({"EventFuncTable Remove : Key does not exist"});
                return; // Key does not exist
            }

            _funcMap.erase(key);

#ifndef NDEBUG
            WBEvent::ConsoleLog()->Log({"EventFuncTable Remove : Removed event function"});
#endif
        }

        EVENT_RETURN (EVENT::*Get(FUNC_KEY key))(ARGS...) override
        {
            if (!Has(key))
            {
                std::string err = WBEvent::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"EventFuncTable Get : Key does not exist"}
                );
                WB::MessageBoxError(WBEvent::ConsoleLog()->GetName(), err);

                return _empty; // Key does not exist
            }

#ifndef NDEBUG
            WBEvent::ConsoleLog()->Log({"EventFuncTable Get : Getting event function"});
#endif
            return _funcMap[key]; // Return the function pointer
        }

        void Set(FUNC_KEY key, EVENT_RETURN (EVENT::*func)(ARGS...)) override
        {
            if (!Has(key))
            {
                std::string err = WBEvent::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"EventFuncTable Set : Key does not exist"}
                );
                WB::MessageBoxError(WBEvent::ConsoleLog()->GetName(), err);

                return; // Key does not exist
            }

            _funcMap[key] = func;

#ifndef NDEBUG
            WBEvent::ConsoleLog()->Log({"EventFuncTable Set : Set event function"});
#endif
        }

    };

    template <typename EVENT_KEY, typename EVENT, typename FUNC_KEY, typename... ARGS>
    class EventInvoker : public IEventInvoker<EVENT_KEY, EVENT, FUNC_KEY, ARGS...>
    {
    private:
        std::unique_ptr<IEventInstTable<EVENT_KEY, EVENT>>& _instTable;
        std::unique_ptr<IEventFuncTable<FUNC_KEY, EVENT, ARGS...>>& _funcTable;

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
         * EventInvoker has unique_ptr reference so it need to initialize in constructor.
        /**************************************************************************************************************/

        EventInvoker
        (
            std::unique_ptr<IEventInstTable<EVENT_KEY, EVENT>>& instTable,
            std::unique_ptr<IEventFuncTable<FUNC_KEY, EVENT, ARGS...>>& funcTable
        ) : _instTable(instTable), _funcTable(funcTable)
        {
#ifndef NDEBUG
            WBEvent::ConsoleLog()->Log({"EventInvoker Constructor : Created event invoker"});
#endif
        }

        ~EventInvoker() override
        {
#ifndef NDEBUG
            WBEvent::ConsoleLog()->Log({"EventInvoker Destructor : Destroyed event invoker"});
#endif
        }

        EventInvoker(const EventInvoker&) = delete;
        EventInvoker& operator=(const EventInvoker&) = delete;

        /***************************************************************************************************************
         * IEventInvoker interface implementation
        /**************************************************************************************************************/

        EVENT_RETURN Invoke(EVENT_KEY eventKey, FUNC_KEY funcKey, ARGS... args) override
        {
            if (!_instTable->Has(eventKey)) return; // Event key does not exist
            if (!_funcTable->Has(funcKey)) return; // Function key does not exist

            std::unique_ptr<EVENT>& event = _instTable->Get(eventKey);
            if (event == nullptr)
            {
                std::string err = WBEvent::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"EventInvoker Invoke : Event instance is null"}
                );
                WB::MessageBoxError(WBEvent::ConsoleLog()->GetName(), err);

                return; // Event instance is null
            }

            EVENT_RETURN (EVENT::*func)(ARGS...) = _funcTable->Get(funcKey);
            if (func == nullptr)
            {
                std::string err = WBEvent::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"EventInvoker Invoke : Function pointer is null"}
                );
                WB::MessageBoxError(WBEvent::ConsoleLog()->GetName(), err);

                return; // Function pointer is null
            }

            // Call the function on the event instance
            (event.get()->*func)(args...);
        }

        
    };
}