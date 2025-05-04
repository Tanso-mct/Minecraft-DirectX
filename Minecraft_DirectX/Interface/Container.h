#pragma once

#include <memory>

namespace WB
{
    enum class ContainerType : int
    {
        Unknown = -1,
        WindowContext,
        SceneContext,
        Monitor,
        ImageData,
        SoundData,
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

    class ISceneContext;

    class ISceneContextContainer : public IContainer
    {
    public:
        virtual ~ISceneContextContainer() = default;

        virtual void Add(std::unique_ptr<ISceneContext> sceneContext) = 0;
        virtual void Remove(int index) = 0;
        virtual std::unique_ptr<ISceneContext>& Get(int index) = 0;
        virtual std::unique_ptr<ISceneContext> Take(int index) = 0;
        virtual void Set(int index, std::unique_ptr<ISceneContext> sceneContext) = 0;
    };

    class IMonitor;

    class IMonitorContainer : public IContainer
    {
    public:
        virtual ~IMonitorContainer() = default;

        virtual void Add(std::unique_ptr<IMonitor> monitor) = 0;
        virtual void Remove(int index) = 0;
        virtual std::unique_ptr<IMonitor>& Get(int index) = 0;
        virtual std::unique_ptr<IMonitor> Take(int index) = 0;
        virtual void Set(int index, std::unique_ptr<IMonitor> monitor) = 0;
    };

    class IImageData;

    class IImageDataContainer : public IContainer
    {
    public:
        virtual ~IImageDataContainer() = default;

        virtual void Add(std::unique_ptr<IImageData> imageData) = 0;
        virtual void Remove(int index) = 0;
        virtual std::unique_ptr<IImageData>& Get(int index) = 0;
        virtual std::unique_ptr<IImageData> Take(int index) = 0;
        virtual void Set(int index, std::unique_ptr<IImageData> imageData) = 0;
    };

    class ISoundData;

    class ISoundDataContainer : public IContainer
    {
    public:
        virtual ~ISoundDataContainer() = default;

        virtual void Add(std::unique_ptr<ISoundData> soundData) = 0;
        virtual void Remove(int index) = 0;
        virtual std::unique_ptr<ISoundData>& Get(int index) = 0;
        virtual std::unique_ptr<ISoundData> Take(int index) = 0;
        virtual void Set(int index, std::unique_ptr<ISoundData> soundData) = 0;
    };

} // namespace MCT