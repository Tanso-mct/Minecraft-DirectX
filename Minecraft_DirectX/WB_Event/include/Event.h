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

    template <typename FUNC_KEY, typename FUNC, typename RETURN, typename... ARGS>
    class EventFuncTable : public IEventFuncTable<FUNC_KEY, FUNC, RETURN, ARGS...>
    {
    private:
        std::unordered_map<FUNC_KEY, RETURN (FUNC::*)(ARGS...)> _funcMap;
        RETURN (FUNC::*_empty) (ARGS...) = nullptr; // Dummy used when returning references

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

        void Add(FUNC_KEY key, RETURN (FUNC::*func)(ARGS...)) override
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

        RETURN (FUNC::*Get(FUNC_KEY key))(ARGS...) override
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

        void Set(FUNC_KEY key, RETURN (FUNC::*func)(ARGS...)) override
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
}