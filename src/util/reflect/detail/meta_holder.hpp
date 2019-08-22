/* -----------------------------------------------------------------------------------------------

MetaHolder holds all Member objects constructed via meta::registerMembers<T> call.
If the class is not registered, members is std::tuple<>

-------------------------------------------------------------------------------------------------*/

#pragma once

#include <tuple>
#include "../reflect.hpp"

namespace otto::reflect {
  namespace detail {

    template<typename T, typename TupleType>
    struct MetaHolder {
      static constexpr TupleType members = register_members<T>();
      static constexpr util::string_ref name()
      {
        return register_name<T>();
      }
    };

  } // end of namespace detail
} // namespace otto::reflect
