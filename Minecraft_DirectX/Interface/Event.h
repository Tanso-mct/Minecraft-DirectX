#pragma once

#include <memory>

namespace WB
{
    using EVENT_RETURN = void;

    template <typename EVENT_KEY, typename EVENT>
    class IEventInstTable
    {
    public:
        virtual ~IEventInstTable() = default;

        virtual void Clear() = 0;
        virtual bool Has(EVENT_KEY key) const = 0;
        virtual size_t GetSize() const = 0;

        virtual void Add(EVENT_KEY key, std::unique_ptr<EVENT> event) = 0;
        virtual void Remove(EVENT_KEY key) = 0;
        virtual std::unique_ptr<EVENT>& Get(EVENT_KEY key) = 0;
        virtual void Set(EVENT_KEY key, std::unique_ptr<EVENT> event) = 0;
    };

    template <typename FUNC_KEY, typename EVENT, typename... ARGS>
    class IEventFuncTable
    {
    public:
        virtual ~IEventFuncTable() = default;

        virtual void Clear() = 0;
        virtual bool Has(FUNC_KEY key) const = 0;
        virtual size_t GetSize() const = 0;

        virtual void Add(FUNC_KEY key, EVENT_RETURN (EVENT::*func)(ARGS...)) = 0;
        virtual void Remove(FUNC_KEY key) = 0;
        virtual EVENT_RETURN (EVENT::*Get(FUNC_KEY key))(ARGS...) = 0;
        virtual void Set(FUNC_KEY key, EVENT_RETURN (EVENT::*func)(ARGS...)) = 0;
    };

    template <typename EVENT_KEY, typename EVENT, typename FUNC_KEY, typename... ARGS>
    class IEventInvoker
    {
    public:
        virtual ~IEventInvoker() = default;
        virtual EVENT_RETURN Invoke(EVENT_KEY eventKey, FUNC_KEY funcKey, ARGS... args) = 0;
    };

} // namespace WB