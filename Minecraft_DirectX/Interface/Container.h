#pragma once

#include <memory>

namespace MCT
{
    enum class ContainerType : int
    {
        Unknown = -1,
        WindowContext,
    };

    class IContainer
    {
    public:
        virtual ~IContainer() = default;
        
        virtual ContainerType GetContainerType() = 0;

        virtual void Create(unsigned int size) = 0;
        virtual void Clear() = 0;
        virtual size_t GetSize() const = 0;
    };

    class IWindowContext;

    class IWindowContextContainer : public IContainer
    {
    public:
        virtual ~IWindowContextContainer() = default;

        virtual void Add(std::unique_ptr<IWindowContext> windowContext) = 0;
        virtual void Remove(int index) = 0;
        virtual std::unique_ptr<IWindowContext>& Get(int index) = 0;
        virtual std::unique_ptr<IWindowContext> Take(int index) = 0;
        virtual void Set(int index, std::unique_ptr<IWindowContext> windowContext) = 0;
    };

} // namespace MCT