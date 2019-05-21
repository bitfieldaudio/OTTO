#pragma once

#include "serialize.hpp"

namespace otto::util {

  /////////////////// SERIALIZATION

  template<typename Class, typename>
  json serialize(const Class& obj)
  {
    json value;
    reflect::for_all_members<Class>([&obj, &value](auto& member) {
      auto& valueName = value[std::string(member.get_name())];
      valueName = serialize(member.get(obj));
    });
    return value;
  }

  template<typename Class, typename, typename>
  json serialize(const Class& obj)
  {
    return serialize_basic(obj);
  }

  template<typename Class>
  json serialize_basic(const Class& obj)
  {
    return json(obj);
  }

  // specialization for std::array
  template<typename T, std::size_t N>
  json serialize_basic(const std::array<T, N>& obj)
  {
    json value;
    int i = 0;
    for (auto& elem : obj) {
      value[i] = serialize(elem);
      ++i;
    }
    return value;
  }

  // specialization for std::vector
  template<typename T>
  json serialize_basic(const std::vector<T>& obj)
  {
    json value;
    int i = 0;
    for (auto& elem : obj) {
      value[i] = serialize(elem);
      ++i;
    }
    return value;
  }

  // specialization for std::unordered_map
  template<typename K, typename V>
  json serialize_basic(const std::unordered_map<K, V>& obj)
  {
    json value;
    for (auto& pair : obj) {
      value.emplace(to_string(pair.first), serialize(pair.second));
    }
    return value;
  }

  /////////////////// DESERIALIZATION

  template<typename Class>
  Class deserialize(const json& obj)
  {
    Class c;
    deserialize(c, obj);
    return c;
  }

  template<typename Class, typename>
  void deserialize(Class& obj, const json& object)
  {
    if (object.is_object()) {
      reflect::for_all_members<Class>([&obj, &object](auto& member) {
        auto iter = object.find(std::string(member.get_name()));
        if (iter == object.end()) throw util::exception("Error: Member '{}' not found in json", member.get_name());
        auto& objName = *iter;
        if (!objName.is_null()) {
          using MemberT = reflect::get_member_type<decltype(member)>;
          if constexpr (std::decay_t<decltype(member)>::can_get_ref()) {
            deserialize(member.get_ref(obj), objName);
          } else if (member.has_setter()) {
            if constexpr (std::is_default_constructible_v<MemberT> &&
                          std::is_assignable_v<MemberT&, MemberT&&>) {
              MemberT m{};
              deserialize(m, objName);
              member.set(obj, std::move(m));
            } else {
              throw util::exception("Error: can't deserialize member '{}' because a reference can "
                                    "not be accessed and the type is not default constructible",
                                    member.get_name());
            }
          } else {
            throw util::exception("Error: can't deserialize member '{}' because it's read only",
                                  member.get_name());
          }
        }
      });
    } else {
      throw util::exception("Error: can't deserialize from Json::json to {}. Json: {}", reflect::get_name<Class>(), object);
    }
  }

  template<typename Class, typename, typename>
  void deserialize(Class& obj, const json& object)
  {
    obj = object.get<Class>();
  }

  template<typename T, std::size_t N>
  void deserialize(std::array<T, N>& obj, const json& object)
  {
    std::size_t i = 0;
    for (auto& elem : object) {
      deserialize(obj.at(i), elem);
      i++;
    }
  }


  // specialization for std::vector
  template<typename T>
  void deserialize(std::vector<T>& obj, const json& object)
  {
    obj.reserve(object.size()); // vector.resize() works only for default constructible types
    for (auto& elem : object) {
      obj.push_back(elem); // push rvalue
    }
  }

  // specialization for std::unodered_map
  template<typename K, typename V>
  void deserialize(std::unordered_map<K, V>& obj, const json& object)
  {
    for (auto it = object.begin(); it != object.end(); ++it) {
      obj.emplace(from_string<K>(it.key()), it.value());
    }
  }

} // namespace otto::util

// kak: other_file=serialize.hpp
