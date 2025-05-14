#pragma once

#include <memory>

namespace WB
{
    class IElement
    {
    public:
        virtual ~IElement() = default;
    };

    class IContainer
    {
    public:
        virtual ~IContainer() = default;
        
        virtual void Create(unsigned int size) = 0;
        virtual void Clear() = 0;
        virtual size_t GetSize() const = 0;

        virtual size_t Add(std::unique_ptr<IElement> data) = 0;
        virtual void Remove(int index) = 0;
        virtual std::unique_ptr<IElement>& Get(int index) = 0;
        virtual std::unique_ptr<IElement> Take(int index) = 0;
        virtual void Set(int index, std::unique_ptr<IElement> data) = 0;
    };

} // namespace WB