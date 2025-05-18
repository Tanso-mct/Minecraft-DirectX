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

    template <typename T, typename ID>
    class IStaticContainer : public IContainer
    {
    public:
        virtual ~IStaticContainer() = default;

        virtual void Create(ID size) = 0;

        virtual std::unique_ptr<T>& Get(ID index) = 0;
        virtual void Set(ID index, std::unique_ptr<T> data) = 0;
        virtual std::unique_ptr<T> Release(ID index) = 0;
    };

    template <typename T>
    class IDynamicContainer : public IContainer
    {
    public:
        virtual ~IDynamicContainer() = default;

        virtual void Create(int size) = 0;
        virtual void Resize(int size) = 0;

        virtual int PushBack(std::unique_ptr<T> data) = 0;
        virtual std::unique_ptr<T> PopBack() = 0;

        virtual std::unique_ptr<T>& Get(int index) = 0;
        virtual void Set(int index, std::unique_ptr<T> data) = 0;
        virtual std::unique_ptr<T> Release(int index) = 0;
    };

    /*******************************************************************************************************************
     * All data types of IStaticContainer defined here
    /******************************************************************************************************************/

    class IWindowContext;
    enum class WindowID
    {
        Game,
        Size,
    };
    using IWindowContextContainer = IStaticContainer<WB::IWindowContext, WindowID>;

    class ISceneContext;
    enum class SceneID
    {
        Main,
        Size,
    };
    using ISceneContextContainer = IStaticContainer<WB::ISceneContext, SceneID>;

    class IMonitor;
    enum class MonitorID
    {
        Keyboard,
        Mouse,
        Size,
    };
    using IMonitorContainer = IStaticContainer<WB::IMonitor, MonitorID>;

    class IImageData;
    enum class ImageID
    {
        Example,
        Size,
    };
    using IImageDataContainer = IStaticContainer<WB::IImageData, ImageID>;

    class ISoundData;
    enum class SoundID
    {
        Example,
        Size,
    };
    using ISoundDataContainer = IStaticContainer<WB::ISoundData, SoundID>;

    class IModelData;
    enum class ModelID
    {
        Example,
        Size,
    };
    using IModelDataContainer = IStaticContainer<WB::IModelData, ModelID>;

    class ICsvData;
    enum class CsvID
    {
        Example,
        Size,
    };
    using ICsvDataContainer = IStaticContainer<WB::ICsvData, CsvID>;

} // namespace WB