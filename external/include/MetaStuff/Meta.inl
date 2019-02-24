#include <cassert>
#include <tuple>
#include <cstring>

#include "Member.h"
#include "detail/template_helpers.h"
#include "detail/MetaHolder.h"

namespace metastuff
{

template <typename... Args>
auto members(Args&&... args)
{
    // just this... but may become more complex later, who knows!
    //  Still, better no to expose too much to end-user.
    return std::make_tuple(std::forward<Args>(args)...);
}

// No default implementations of these
// template <typename Class>
// inline auto registerMembers()
// {
//     return std::make_tuple();
// }
// 
// template <typename Class>
// constexpr auto registerName()
// {
//     return "";
// }

template <typename Class>
constexpr auto getName()
{
    return detail::MetaHolder<Class, decltype(registerMembers<Class>())>::name();
}

template <typename Class>
constexpr std::size_t getMemberCount()
{
	return std::tuple_size<decltype(registerMembers<Class>())>::value;
}

template <typename Class>
const auto& getMembers()
{
    return detail::MetaHolder<Class, decltype(registerMembers<Class>())>::members;
}

template <typename Class>
constexpr bool isRegistered()
{
    return !std::is_same<std::tuple<>, decltype(registerMembers<Class>())>::value;
}

// Check if Class has non-default ctor registered
template <typename Class>
constexpr bool ctorRegistered()
{
    return !std::is_same<type_list<>, constructor_arguments<Class>>::value;
}

template <typename Class>
bool hasMember(const char* name)
{
    bool found = false;
    doForAllMembers<Class>(
        [&found, &name](const auto& member)
        {
            if (!strcmp(name, member.getName())) {
                found = true;
            }
        }
    );
    return found;
}

template <typename Class, typename F, typename>
void doForAllMembers(F&& f)
{
    detail::for_tuple(std::forward<F>(f), getMembers<Class>());
}

// version for non-registered classes (to generate less template stuff)
template <typename Class, typename F,
    typename, typename>
    void doForAllMembers(F&& /*f*/)
{
    // do nothing! Nothing gets generated
}

template <typename Class, typename T, typename F>
void doForMember(const char* name, F&& f)
{
    doForAllMembers<Class>(
        [&](const auto& member)
        {
            if (!strcmp(name, member.getName())) {
                using MemberT = metastuff::get_member_type<decltype(member)>;
                assert((std::is_same<MemberT, T>::value) && "Member doesn't have type T");
                detail::call_if<std::is_same<MemberT, T>::value>(std::forward<F>(f), member);
            }
        }
    );
}

template <typename T, typename Class>
T getMemberValue(Class& obj, const char* name)
{
    T value;
    doForMember<Class, T>(name,
        [&value, &obj](const auto& member)
        {
            value = member.getCopy(obj);
        }
    );
    return value;
}

template <typename T, typename Class, typename V,
    typename>
void setMemberValue(Class& obj, const char* name, V&& value)
{
    doForMember<Class, T>(name,
        [&obj, value = std::forward<V>(value)](const auto& member)
        {
            member.set(obj, value);
        }
    );
}

} // end of namespace meta
