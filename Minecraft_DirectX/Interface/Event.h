#pragma once

#include <memory>

namespace WB
{
    using EVENT_RETURN = void;

    class IEvent
    {
    public:
        virtual ~IEvent() = default;
        virtual bool IsDestroying() = 0;
    };

    template <typename KEY>
    class IEventTable
    {
    public:
        virtual ~IEventTable() = default;

        virtual void Clear() = 0;
        virtual bool Has(KEY key) const = 0;
        virtual size_t GetSize() const = 0;
    };

    template <typename KEY, typename EVENT>
    class IEventInstTable : public IEventTable<KEY>
    {
    public:
        virtual ~IEventInstTable() = default;

        virtual void Add(KEY key, std::unique_ptr<EVENT> event) = 0;
        virtual std::unique_ptr<EVENT> Remove(KEY key) = 0;
        virtual std::unique_ptr<EVENT>& Get(KEY key) = 0;
        virtual void Set(KEY key, std::unique_ptr<EVENT> event) = 0;
    };

    template <typename KEY, typename EVENT, typename... ARGS>
    class IEventFuncTable : public IEventTable<KEY>
    {
    public:
        virtual ~IEventFuncTable() = default;

        virtual void Add(KEY key, EVENT_RETURN (EVENT::*func)(ARGS...)) = 0;
        virtual EVENT_RETURN (EVENT::*Remove(KEY key))(ARGS...) = 0;
        virtual EVENT_RETURN (EVENT::*Get(KEY key))(ARGS...) = 0;
        virtual void Set(KEY key, EVENT_RETURN (EVENT::*func)(ARGS...)) = 0;
    };

    template <typename EVENT_KEY, typename EVENT, typename FUNC_KEY, typename... ARGS>
    class IEventInvoker
    {
    public:
        virtual ~IEventInvoker() = default;
        virtual void SetTables
        (
            std::unique_ptr<IEventInstTable<EVENT_KEY, EVENT>> instTable,
            std::unique_ptr<IEventFuncTable<FUNC_KEY, EVENT, ARGS...>> funcTable
        ) = 0;
        virtual EVENT_RETURN Invoke(EVENT_KEY eventKey, FUNC_KEY funcKey, ARGS... args) = 0;
    };

} // namespace WB