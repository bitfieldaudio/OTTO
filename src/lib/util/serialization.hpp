#pragma once

#include <any>

#include "lib/util/enum.hpp"
#include "lib/util/visitor.hpp"

#include "lib/chrono.hpp"
#include "lib/json.hpp"
#include "lib/logging.hpp"

#include "fmt/core.h"

namespace otto::util {

  /// Used to implement serialization/deserialization functions for objects.
  ///
  /// Specialize this, and implement the following two functions
  /// ```cpp
  /// static void serialize_into(json::value& json, const T& value);
  /// static void deserialize_from(const json::value& json, T& value);
  /// ```
  /// There is a specialization for having these as member functions as well,
  /// so you can do the following:
  /// ```cpp
  /// void serialize_into(json::value& json) const;
  /// void deserialize_from(const json::value& json);
  /// ```
  template<typename T, unsigned order = 5>
  struct serialize_impl;

  template<typename T>
  concept ASerializable = requires(json::value json, T& t)
  {
    serialize_impl<std::decay_t<T>>::serialize_into(json, t);
    serialize_impl<std::decay_t<T>>::deserialize_from(json, t);
  };

  void serialize_into(json::value& json, const ASerializable auto& obj)
  {
    serialize_impl<std::decay_t<decltype(obj)>>::serialize_into(json, obj);
  }

  void deserialize_from(const json::value& json, ASerializable auto& obj)
  {
    serialize_impl<std::decay_t<decltype(obj)>>::deserialize_from(json, obj);
  }

  /// Checks if the member exists, and then calls `deserialize_from(json[key], obj)`
  ///
  /// Otherwise, does nothing
  void deserialize_from_member(const json::value& json, const std::string& key, ASerializable auto& obj)
  {
    if (json.contains(key)) util::deserialize_from(json[key], obj);
  }

  json::value serialize(const ASerializable auto& obj)
  {
    json::value res;
    serialize_into(res, obj);
    return res;
  }

  template<ASerializable T>
  requires(std::is_default_constructible_v<T>) //
    T deserialize(const json::value& json)
  {
    T res = {};
    deserialize_from(json, res);
    return res;
  }

  /// Base class with pure virtual serialize/deserialize functions
  struct ISerializable {
    virtual ~ISerializable() = default;
    virtual void serialize_into(json::value& json) const = 0;
    virtual void deserialize_from(const json::value& json) = 0;
  };

  /// An owning or non-owning reference to any serializable object
  ///
  /// Used to type-erase serializable objects, whether or not they derive from
  /// `ISerializable`
  /// Can either be constructed from an rvalue reference, i.e. by moving an object into it,
  /// or from a `std::reference_wrapper`, as created by calling `std::ref`
  struct DynSerializable final {
    DynSerializable() = default;

    template<ASerializable T>
    DynSerializable(std::reference_wrapper<T> t)
      : data_(t),
        serialize_into_([](json::value& json, const std::any& data) {
          util::serialize_into(json, std::any_cast<std::reference_wrapper<T>>(data).get());
        }),
        deserialize_from_([](const json::value& json, std::any& data) {
          util::deserialize_from(json, std::any_cast<std::reference_wrapper<T>>(data).get());
        })
    {}

    template<ASerializable T>
    DynSerializable(T&& t) // NOLINT
      requires(std::is_rvalue_reference_v<decltype(t)> && !util::decays_to<T, DynSerializable> &&
               std::is_nothrow_move_constructible_v<T>)
      : data_(std::move(t)), // NOLINT
        serialize_into_(
          [](json::value& json, const std::any& data) { util::serialize_into(json, std::any_cast<const T&>(data)); }),
        deserialize_from_(
          [](const json::value& json, std::any& data) { util::deserialize_from(json, std::any_cast<T&>(data)); })
    {}

    DynSerializable(const DynSerializable&) = delete;
    DynSerializable& operator=(const DynSerializable&) = delete;
    DynSerializable(DynSerializable&& rhs) noexcept = default;
    DynSerializable& operator=(DynSerializable&& rhs) noexcept = default;

    void serialize_into(json::value& json) const
    {
      if (serialize_into_ != nullptr) serialize_into_(json, data_);
    }
    void deserialize_from(const json::value& json)
    {
      if (deserialize_from_ != nullptr) deserialize_from_(json, data_);
    }

  private:
    std::any data_;
    util::function_ptr<void(json::value&, const std::any&)> serialize_into_ = nullptr;
    util::function_ptr<void(const json::value&, std::any&)> deserialize_from_ = nullptr;
  };

  // Specializations

  // Default implementation: use the next one in the chain
  template<typename T, unsigned Order>
  struct serialize_impl : serialize_impl<T, Order - 1> {};

  // No implementation at level 0
  template<typename T>
  struct serialize_impl<T, 0> {};

  // Fallback to json library
  template<json::AJsonSerializable T>
  struct serialize_impl<T, 0> {
    static void serialize_into(json::value& json, const T& value)
    {
      json = value;
    }
    static void deserialize_from(const json::value& json, T& value)
    {
      value = json.get<T>();
    }
  };

  template<ASerializable T, typename A>
  requires std::is_default_constructible_v<T> //
  struct serialize_impl<std::vector<T, A>, 1> {
    static void serialize_into(json::value& json, const std::vector<T, A>& r)
    {
      if (json == nullptr) json = json::array();
      json.get_ref<json::array&>().resize(r.size());
      for (int i = 0; i < r.size(); i++) {
        util::serialize_into(json[i], r[i]);
      }
    }
    static void deserialize_from(const json::value& json, std::vector<T, A>& r)
    {
      r.clear();
      for (const auto& v : json) {
        r.emplace_back(util::deserialize<T>(v));
      }
    }
  };

  template<ASerializable T, std::size_t N>
  struct serialize_impl<std::array<T, N>, 1> {
    static void serialize_into(json::value& json, const std::array<T, N>& r)
    {
      if (json == nullptr) json = json::array();
      json.get_ref<json::array&>().resize(N);
      for (auto&& [src, dst] : util::zip(r, json)) {
        util::serialize_into(dst, src);
      }
    }
    static void deserialize_from(const json::value& json, std::array<T, N>& r)
    {
      json.is_discarded();
      if (json.type() != json::type::array) {
        throw std::invalid_argument(fmt::format("Expected array, got {}", json.type_name()));
      }
      if (json.size() != N) {
        throw std::invalid_argument(fmt::format("Expected array of size {}, got {}", N, json.size()));
      }
      for (auto&& [input, json] : util::zip(r, json)) {
        util::deserialize_from(json, input);
      }
    }
  };

  template<AVisitable T>
  struct serialize_impl<T, 2> {
    static void serialize_into(json::value& json, const T& value)
    {
      util::visit(value,
                  [&](util::string_ref name, const auto& member) { util::serialize_into(json[name.c_str()], member); });
    }
    static void deserialize_from(const json::value& json, T& value)
    {
      util::visit(value, [&](util::string_ref name, auto& member) {
        try {
          util::deserialize_from_member(json, name.c_str(), member);
        } catch (std::out_of_range& e) {
          // LOGD("Nonexistent key {} when deserializing", name);
        }
      });
    }
  };

  // With member functions
  template<typename T>
  requires requires(const json::value& cjson, json::value& json, T& obj, const T& cobj)
  {
    cobj.serialize_into(json);
    obj.deserialize_from(cjson);
  } //
  struct serialize_impl<T, 3> {
    static void serialize_into(json::value& json, const T& value)
    {
      value.serialize_into(json);
    }
    static void deserialize_from(const json::value& json, T& value)
    {
      value.deserialize_from(json);
    }
  };

  template<AnEnum E>
  struct serialize_impl<E, 3> {
    static void serialize_into(json::value& json, const E& value)
    {
      json = util::enum_name(value);
    }
    static void deserialize_from(const json::value& json, E& value)
    {
      auto opt = util::enum_cast<E>(json.get<std::string_view>());
      if (!opt) {
        throw std::invalid_argument(fmt::format("Invalid name when deserializing enum: {}", json));
      }
      value = *opt;
    }
  };

  // TODO: better represenatation of durations in serialization?
  template<>
  struct serialize_impl<chrono::duration, 5> {
    static void serialize_into(json::value& json, const chrono::duration& value)
    {
      json = value.count();
    }
    static void deserialize_from(const json::value& json, chrono::duration& value)
    {
      value = chrono::duration(json.get<std::int64_t>());
    }
  };
} // namespace otto::util
