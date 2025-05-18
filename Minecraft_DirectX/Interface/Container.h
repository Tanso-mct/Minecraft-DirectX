#pragma once

#include <memory>

namespace WB
{
    class IContainer
    {
    public:
        virtual ~IContainer() = default;
        
        virtual void Clear() = 0;
        virtual size_t GetSize() const = 0;
    };

} // namespace WB