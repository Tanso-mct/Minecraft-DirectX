#pragma once

#include "Interface/Container.h"

#include "Interface/WindowContext.h"
#include "Interface/SceneContext.h"
#include "Interface/Monitor.h"
#include "Interface/ImageData.h"
#include "Interface/SoundData.h"
#include "Interface/ModelData.h"
#include "Interface/CsvData.h"

#include "WB_ConsoleLog/include/ConsoleLog.h"
#pragma comment(lib, "WB_ConsoleLog.lib")

#include "WB_Utility/include/ErrorHandling.h"
#pragma comment(lib, "WB_Utility.lib")

#include <vector>
#include <memory>

namespace WBContainer
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
    /*******************************************************************************************************************
     * StaticContainer
    /******************************************************************************************************************/

    template <typename T, typename ID>
    class StaticContainer : public IStaticContainer<T, ID>
    {
    private:
        std::vector<std::unique_ptr<T>> _datas;
        std::unique_ptr<T> _empty = nullptr; // Dummy used when returning references

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
         * StaticContainer has unique_ptr objects, so it is not copyable or assignable.
        /**************************************************************************************************************/

        StaticContainer()
        {
#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"StaticContainer Constructor"});
#endif
        }

        ~StaticContainer() override
        {
#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"StaticContainer Destructor"});
#endif
        }

        StaticContainer(const StaticContainer&) = delete;
        StaticContainer& operator=(const StaticContainer&) = delete;

        /***************************************************************************************************************
         * IContainer interface implementation
        /**************************************************************************************************************/

        void Clear() override
        {
            _datas.clear();
#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"StaticContainer Clear : Cleared container"});
#endif
        }

        size_t GetSize() const override
        {
            return _datas.size();
        }

        /***************************************************************************************************************
         * IStaticContainer interface implementation
        /**************************************************************************************************************/

        void Create(ID size) override
        {
            int sizeInt = static_cast<int>(size);

            if (sizeInt < 0)
            {
                std::string err = WBContainer::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"StaticContainer Create : Size must be greater than 0"}
                );
                WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

                return; // Size must be greater than 0
            }

            if (static_cast<int>(_datas.size()) > 0)
            {
                std::string err = WBContainer::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"StaticContainer Create : StaticContainer already created"}
                );
                WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

                return; // StaticContainer already created
            }

            _datas.resize(sizeInt);

#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"StaticContainer Create : Created container"});
#endif
        }

        std::unique_ptr<T>& Get(ID index) override
        {
            int indexInt = static_cast<int>(index);

            if (indexInt < 0 || indexInt >= static_cast<int>(_datas.size()))
            {
                std::string err = WBContainer::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"StaticContainer Get : Index out of bounds"}
                );
                WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

                return _empty; // Index out of bounds
            }

#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"StaticContainer Get : Getting data"});
#endif
            return _datas[indexInt]; // Return the unique_ptr reference
        }

        void Set(ID index, std::unique_ptr<T> data) override
        {
            int indexInt = static_cast<int>(index);

            if (indexInt < 0 || indexInt >= static_cast<int>(_datas.size()))
            {
                std::string err = WBContainer::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"StaticContainer Set : Index out of bounds"}
                );
                WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);
                
                return; // Index out of bounds
            }

            _datas[indexInt] = std::move(data); // Move the unique_ptr into the container

#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"StaticContainer Set : Set data"});
#endif
        }

        std::unique_ptr<T> Release(ID index) override
        {
            int indexInt = static_cast<int>(index);

            if (indexInt < 0 || indexInt >= static_cast<int>(_datas.size()))
            {
                std::string err = WBContainer::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"StaticContainer Release : Index out of bounds"}
                );
                WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

                return nullptr; // Index out of bounds
            }

#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"StaticContainer Release : Releasing data"});
#endif
            return std::move(_datas[indexInt]); // Move the unique_ptr to the caller
        }
    };

    /*******************************************************************************************************************
     * All data types of StaticContainer defined here
    /******************************************************************************************************************/

    using WindowContextContainer = StaticContainer<IWindowContext, WindowID>;
    using SceneContextContainer = StaticContainer<ISceneContext, SceneID>;
    using MonitorContainer = StaticContainer<IMonitor, MonitorID>;
    using ImageDataContainer = StaticContainer<IImageData, ImageID>;
    using SoundDataContainer = StaticContainer<ISoundData, SoundID>;
    using ModelDataContainer = StaticContainer<IModelData, ModelID>;
    using CsvDataContainer = StaticContainer<ICsvData, CsvID>;

    /*******************************************************************************************************************
     * DynamicContainer
    /******************************************************************************************************************/

    template <typename T>
    class DynamicContainer : public IDynamicContainer<T>
    {
    private:
        std::vector<std::unique_ptr<T>> _datas;
        std::unique_ptr<T> _empty = nullptr; // Dummy used when returning references

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
         * DynamicContainer has unique_ptr objects, so it is not copyable or assignable.
        /**************************************************************************************************************/

        DynamicContainer()
        {
#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"DynamicContainer Constructor"});
#endif
        }

        ~DynamicContainer() override
        {
#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"DynamicContainer Destructor"});
#endif
        }

        DynamicContainer(const DynamicContainer&) = delete;
        DynamicContainer& operator=(const DynamicContainer&) = delete;

        /***************************************************************************************************************
         * IContainer interface implementation
        /**************************************************************************************************************/

        void Clear() override
        {
            _datas.clear();
#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"DynamicContainer Clear : Cleared container"});
#endif
        }

        size_t GetSize() const override
        {
            return _datas.size();
        }

        /***************************************************************************************************************
         * IDynamicContainer interface implementation
        /**************************************************************************************************************/

        void Create(int size) override
        {
            if (size < 0)
            {
                std::string err = WBContainer::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"DynamicContainer Create : Size must be greater than 0"}
                );
                WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

                return; // Size must be greater than 0
            }

            if (static_cast<int>(_datas.size()) > 0)
            {
                std::string err = WBContainer::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"DynamicContainer Create : DynamicContainer already created"}
                );
                WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

                return; // DynamicContainer already created
            }

            _datas.resize(size);

#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"DynamicContainer Create : Created container"});
#endif
        }

        void Resize(int size) override
        {
            if (size < 0)
            {
                std::string err = WBContainer::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"DynamicContainer Resize : Size must be greater than 0"}
                );
                WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

                return; // Size must be greater than 0
            }

            _datas.resize(size);

#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"DynamicContainer Resize : Resized container"});
#endif
        }

        int PushBack(std::unique_ptr<T> data) override
        {
            _datas.push_back(std::move(data)); // Move the unique_ptr into the container

#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"DynamicContainer PushBack : Pushed data"});
#endif
            return static_cast<int>(_datas.size()) - 1; // Return the index of the new element
        }

        std::unique_ptr<T> PopBack() override
        {
            if (_datas.empty())
            {
                std::string err = WBContainer::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"DynamicContainer PopBack : Container is empty"}
                );
                WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

                return nullptr; // Container is empty
            }

            std::unique_ptr<T> data = std::move(_datas.back());
            _datas.pop_back(); // Remove the last element from the container

#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"DynamicContainer PopBack : Popped data"});
#endif
            return data; // Return the unique_ptr
        }

        std::unique_ptr<T>& Get(int index) override
        {
            if (index < 0 || index >= static_cast<int>(_datas.size()))
            {
                std::string err = WBContainer::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"DynamicContainer Get : Index out of bounds"}
                );
                WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

                return _empty; // Index out of bounds
            }

#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"DynamicContainer Get : Getting data"});
#endif
            return _datas[index]; // Return the unique_ptr reference
        }

        void Set(int index, std::unique_ptr<T> data) override
        {
            if (index < 0 || index >= static_cast<int>(_datas.size()))
            {
                std::string err = WBContainer::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"DynamicContainer Set : Index out of bounds"}
                );
                WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);
                
                return; // Index out of bounds
            }

            _datas[index] = std::move(data); // Move the unique_ptr into the container

#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"DynamicContainer Set : Set data"});
#endif
        }

        std::unique_ptr<T> Release(int index) override
        {
            if (index < 0 || index >= static_cast<int>(_datas.size()))
            {
                std::string err = WBContainer::ConsoleLog()->LogErr
                (
                    __FILE__, __LINE__, __FUNCTION__,
                    {"DynamicContainer Release : Index out of bounds"}
                );
                WB::MessageBoxError(WBContainer::ConsoleLog()->GetName(), err);

                return nullptr; // Index out of bounds
            }

#ifndef NDEBUG
            WBContainer::ConsoleLog()->Log({"DynamicContainer Release : Releasing data"});
#endif
            return std::move(_datas[index]); // Move the unique_ptr to the caller
        }
    };



} // namespace WB