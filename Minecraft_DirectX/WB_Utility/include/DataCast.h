#pragma once

#include "WB_Utility/include/config.h"

#include <memory>

namespace WB
{

/***********************************************************************************************************************
 * As
 * Casts an instance of type S to the specified type T.
/**********************************************************************************************************************/

template <typename T, typename S>
T* As(S* source)
{
    T* target = dynamic_cast<T*>(source);
    return target;
}

/***********************************************************************************************************************
 * UniqueAs
 * Casts an unique_ptr instance of type S to the specified type unique_ptr<T>
 * Ownership is transferred.
/**********************************************************************************************************************/

template <typename T, typename S>
std::unique_ptr<T> UniqueAs(std::unique_ptr<S>& source)
{
    T* target = dynamic_cast<T*>(source.get());

    if (target) return std::unique_ptr<T>(static_cast<T*>(source.release()));
    else return nullptr;
}

/***********************************************************************************************************************
 * CastWithReturn
 * Casts an instance of type unique_ptr to the specified type and 
 * returns ownership to the cast source when it exits scope.
 * Casting from one type of Cast to another is discouraged.WithReturn
/**********************************************************************************************************************/

template <typename D, typename S>
class UTILITY_API CastWithReturn
{
private:
    std::unique_ptr<S>& src_;
    std::unique_ptr<D> casted_ = nullptr;

public:
    CastWithReturn(std::unique_ptr<S>& src) : src_(src)
    {
        D* dstPtr = dynamic_cast<D*>(src.get());
        if (dstPtr) casted_.reset(dynamic_cast<D*>(src.release()));
    }

    ~CastWithReturn()
    {
        src_.reset(dynamic_cast<S*>(casted_.release()));
    }

    std::unique_ptr<D>& operator()() 
    {
        return casted_;
    }
};

} // namespace WB
