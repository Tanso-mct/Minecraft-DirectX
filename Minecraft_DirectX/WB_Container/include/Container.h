#pragma once

#include "WB_Container/include/Config.h"
#include "Interface/Container.h"

#include "WB_Container/include/Log.h"
#include "WB_Utility/include/ErrorHandling.h"

#include <vector>
#include <memory>

namespace WB
{
    template<typename DATA>
    class Container : public IContainer
    {
    private:
        std::vector<std::unique_ptr<DATA>> _data;
        std::unique_ptr<DATA> _empty = nullptr; // Dummy used when returning references

    public:
        /***************************************************************************************************************
         * Constructor / Destructor
         * Container has unique_ptr objects, so it is not copyable or assignable.
        /**************************************************************************************************************/

        Container() = default;
        ~Container() override = default;

        Container(const Container&) = delete;
        Container& operator=(const Container&) = delete;

        /***************************************************************************************************************
         * IContainer interface implementation
        /**************************************************************************************************************/

        void Create(unsigned int size) override
        {
            _data.resize(size);
        }

        void Clear() override
        {
            _data.clear();
        }

        size_t GetSize() const override
        {
            return _data.size();
        }

        /***************************************************************************************************************
         * Container implementation
        /**************************************************************************************************************/

        int Add(std::unique_ptr<DATA> data)
        {
            _data.push_back(std::move(data));
            return static_cast<int>(_data.size() - 1);
        }
    };

} // namespace WB