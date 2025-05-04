#pragma once

#include "WB_Container/include/config.h"

#include "Interface/Container.h"
#include "Interface/SceneContext.h"

#include <vector>
#include <memory>

namespace WB
{
    class CONTAINER_API SceneContextContainer : public ISceneContextContainer
    {
    private:
        std::vector<std::unique_ptr<ISceneContext>> _sceneContexts;
        std::unique_ptr<ISceneContext> _empty = nullptr; // Dummy used when returning references

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
         * Container has unique_ptr objects, so it is not copyable or assignable.
        /**************************************************************************************************************/

        SceneContextContainer() = default;
        ~SceneContextContainer() override = default;

        SceneContextContainer(const SceneContextContainer&) = delete;
        SceneContextContainer& operator=(const SceneContextContainer&) = delete;

        /***************************************************************************************************************
         * IContainer interface implementation
        /**************************************************************************************************************/

        ContainerType GetContainerType() override;

        void Create(unsigned int) override;
        void Clear() override;
        size_t GetSize() const override;

        /***************************************************************************************************************
         * ISceneContextContainer interface implementation
        /**************************************************************************************************************/

        void Add(std::unique_ptr<ISceneContext> sceneContext) override;
        void Remove(int index) override;
        std::unique_ptr<ISceneContext> &Get(int index) override;
        std::unique_ptr<ISceneContext> Take(int index) override;
        void Set(int index, std::unique_ptr<ISceneContext> sceneContext) override;
    };
}