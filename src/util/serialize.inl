#pragma once

#include "serialize.hpp"

namespace otto::util {

  inline namespace serialization {

    /////////////////// SERIALIZATION

    template<typename Class, typename>
    nlohmann::json serialize(const Class& obj)
    {
      nlohmann::json value;
      reflect::for_all_members<Class>([&obj, &value](auto& member) {
        auto& valueName = value[std::string(member.get_name())];
        valueName = serialize(member.get(obj));
      });
      return value;
    }

    template<typename Class, typename, typename>
    nlohmann::json serialize(const Class& obj)
    {
      return serialize_basic(obj);
    }

    template<typename Class>
    nlohmann::json serialize_basic(const Class& obj)
    {
      return nlohmann::json(obj);
    }

    // specialization for std::array
    template<typename T, std::size_t N>
    nlohmann::json serialize_basic(const std::array<T, N>& obj)
    {
      nlohmann::json value;
      int i = 0;
      for (auto& elem : obj) {
        value[i] = serialize(elem);
        ++i;
      }
      return value;
    }

    // specialization for std::vector
    template<typename T>
    nlohmann::json serialize_basic(const std::vector<T>& obj)
    {
      nlohmann::json value;
      int i = 0;
      for (auto& elem : obj) {
        value[i] = serialize(elem);
        ++i;
      }
      return value;
    }

    // specialization for std::unordered_map
    template<typename K, typename V>
    nlohmann::json serialize_basic(const std::unordered_map<K, V>& obj)
    {
      nlohmann::json value;
      for (auto& pair : obj) {
        value.emplace(to_string(pair.first), serialize(pair.second));
      }
      return value;
    }

    namespace detail {
      template<typename... Types, std::size_t... Idx>
      nlohmann::json serialize_tuple_impl(const std::tuple<Types...>& obj, std::index_sequence<Idx...>)
      {
        return nlohmann::json::array({serialize(std::get<Idx>(obj))...});
      }
    } // namespace detail

    template<typename... Types>
    nlohmann::json serialize_basic(const std::tuple<Types...>& obj)
    {
      return detail::serialize_tuple_impl(obj, std::index_sequence_for<Types...>());
    }

    template<typename T1, typename T2>
    nlohmann::json serialize_basic(const std::pair<T1, T2>& obj)
    {
      return nlohmann::json::array({serialize(obj.first), serialize(obj.second)});
    }

    /////////////////// DESERIALIZATION

    template<typename Class>
    Class deserialize(const nlohmann::json& obj)
    {
      Class c;
      deserialize(c, obj);
      return c;
    }

    template<typename Class, typename>
    void deserialize(Class& obj, const nlohmann::json& object)
    {
      if (object.is_object()) {
        reflect::for_all_members<Class>([&obj, &object](auto& member) {
          auto iter = object.find(std::string(member.get_name()));
          if (iter == object.end())
            throw util::exception("Error: Member '{}' not found in nlohmann::json", member.get_name());
          auto& objName = *iter;
          if (!objName.is_null()) {
            using MemberT = reflect::get_member_type<decltype(member)>;
            if constexpr (std::decay_t<decltype(member)>::can_get_ref()) {
              deserialize(member.get_ref(obj), objName);
            } else if (member.has_setter()) {
              if constexpr (std::is_default_constructible_v<MemberT> && std::is_assignable_v<MemberT&, MemberT&&>) {
                MemberT m{};
                deserialize(m, objName);
                member.set(obj, std::move(m));
              } else {
                throw util::exception("Error: can't deserialize member '{}' because a reference can "
                                      "not be accessed and the type is not default constructible",
                                      member.get_name());
              }
            } else {
              throw util::exception("Error: can't deserialize member '{}' because it's read only", member.get_name());
            }
          }
        });
      } else {
        throw util::exception("Error: can't deserialize from nlohmann::json to {}. Json: {}",
                              reflect::get_name<Class>(), std::string(object));
      }
    }

    template<typename Class, typename, typename>
    void deserialize(Class& obj, const nlohmann::json& object)
    {
      object.get_to(obj);
    }

    template<typename T, std::size_t N>
    void deserialize(std::array<T, N>& obj, const nlohmann::json& object)
    {
      std::size_t i = 0;
      for (auto& elem : object) {
        deserialize(obj.at(i), elem);
        i++;
      }
    }


    // specialization for std::vector
    template<typename T>
    void deserialize(std::vector<T>& obj, const nlohmann::json& object)
    {
      obj.reserve(object.size()); // vector.resize() works only for default constructible types
      for (auto& elem : object) {
        obj.push_back(elem); // push rvalue
      }
    }

    // specialization for std::unodered_map
    template<typename K, typename V>
    void deserialize(std::unordered_map<K, V>& obj, const nlohmann::json& object)
    {
      for (auto it = object.begin(); it != object.end(); ++it) {
        obj.emplace(from_string<K>(it.key()), it.value());
      }
    }


    template<typename... Types>
    void deserialize(std::tuple<Types...>& obj, const nlohmann::json& object)
    {
      int i = 0;
      util::for_each(obj, [&](auto& v) {
        deserialize(v, object.at(i));
        i++;
      });
    }

    template<typename T1, typename T2>
    void deserialize(std::pair<T1, T2>& obj, const nlohmann::json& object)
    {
      deserialize(obj.first, object.at(0));
      deserialize(obj.second, object.at(1));
    }
  } // namespace serialize
} // namespace otto::util

template<typename T>
void to_json(nlohmann::json& j, T&& t)
{
  j = serialize(std::forward<T>(t));
}
template<typename T>
void from_json(const nlohmann::json& j, T& t)
{
  deserialize(t, j);
}
