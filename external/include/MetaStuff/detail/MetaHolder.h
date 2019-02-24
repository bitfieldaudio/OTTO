/* -----------------------------------------------------------------------------------------------

MetaHolder holds all Member objects constructed via meta::registerMembers<T> call.
If the class is not registered, members is std::tuple<>

-------------------------------------------------------------------------------------------------*/

#pragma once

#include <tuple>

namespace metastuff
{
namespace detail
{

template <typename T, typename TupleType>
struct MetaHolder {
    static TupleType members;
    static constexpr const char* name() 
    {
        return registerName<T>();
    }
};

template <typename T, typename TupleType>
TupleType MetaHolder<T, TupleType>::members = registerMembers<T>();


} // end of namespace detail
} // end of namespace meta
