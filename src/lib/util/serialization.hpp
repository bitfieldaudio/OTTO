#pragma once

#include <any>

#include "lib/util/enum.hpp"
#include "lib/util/visitor.hpp"

#include "lib/toml.hpp"

#include "fmt/core.h"

namespace otto::util {

  /// Used to implement serialization/deserialization functions for objects.
  ///
  /// Specialize this, and implement the following two functions
  /// ```cpp
  /// static void serialize_into(toml::value& toml, const T& value);
  /// static void deserialize_from(const toml::value& toml, T& value);
  /// ```
  template<typename T, unsigned order = 5>
  struct serialize_impl;

  template<typename T>
  concept ASerializable = requires(toml::value toml, T& t)
  {
    serialize_impl<std::decay_t<T>>::serialize_into(toml, t);
    serialize_impl<std::decay_t<T>>::deserialize_from(toml, t);
  };

  void serialize_into(toml::value& toml, const ASerializable auto& obj)
  {
    serialize_impl<std::decay_t<decltype(obj)>>::serialize_into(toml, obj);
    // The toml serializer cannot handle an empty value, so turn it into an empty table
    if (toml.type() == toml::value_t::empty) toml = toml::table();
  }

  void deserialize_from(const toml::value& toml, ASerializable auto& obj)
  {
    serialize_impl<std::decay_t<decltype(obj)>>::deserialize_from(toml, obj);
  }

  toml::value serialize(const ASerializable auto& obj)
  {
    toml::value res;
    serialize_into(res, obj);
    return res;
  }

  template<ASerializable T>
  requires(std::is_default_constructible_v<T>) //
    T deserialize(const toml::value& toml)
  {
    T res = {};
    deserialize_from(toml, res);
    return res;
  }

  struct ISerializable {
    virtual ~ISerializable() = default;
    virtual void serialize_into(toml::value& toml) const = 0;
    virtual void deserialize_from(const toml::value& toml) = 0;
  };

  struct DynSerializable {
    DynSerializable() = default;

    template<ASerializable T>
    DynSerializable(T& t)
      : ptr_(&t),
        serialize_into_([](toml::value& toml, void* ptr) { util::serialize_into(toml, *static_cast<const T*>(ptr)); }),
        deserialize_from_(
          [](const toml::value& toml, void* ptr) { util::deserialize_from(toml, *static_cast<T*>(ptr)); })
    {}

    template<ASerializable T>
    DynSerializable(T&& t) // NOLINT
      requires(std::is_rvalue_reference_v<decltype(t)> && !util::decays_to<T, DynSerializable> &&
               std::is_nothrow_move_constructible_v<T>)
      : ptr_(new T(std::move(t))), // NOLINT
        destroy_([](void* ptr) {
          delete static_cast<T*>(ptr); // NOLINT
        }),
        serialize_into_([](toml::value& toml, void* ptr) { util::serialize_into(toml, *static_cast<const T*>(ptr)); }),
        deserialize_from_(
          [](const toml::value& toml, void* ptr) { util::deserialize_from(toml, *static_cast<T*>(ptr)); })
    {}

    ~DynSerializable() noexcept
    {
      if (destroy_ != nullptr) destroy_(ptr_);
    }

    DynSerializable(const DynSerializable&) = delete;
    DynSerializable& operator=(const DynSerializable&) = delete;
    DynSerializable(DynSerializable&& rhs) noexcept
      : ptr_(rhs.ptr_),
        destroy_(rhs.destroy_),
        serialize_into_(rhs.serialize_into_),
        deserialize_from_(rhs.deserialize_from_)
    {
      rhs.destroy_ = nullptr;
    }

    DynSerializable& operator=(DynSerializable&& rhs) noexcept
    {
      ptr_ = rhs.ptr_;
      destroy_ = rhs.destroy_;
      serialize_into_ = rhs.serialize_into_;
      deserialize_from_ = rhs.deserialize_from_;
      rhs.destroy_ = nullptr;
      return *this;
    }

    void serialize_into(toml::value& toml) const
    {
      if (ptr_ == nullptr) return;
      serialize_into_(toml, ptr_);
    }
    void deserialize_from(const toml::value& toml)
    {
      if (ptr_ == nullptr) return;
      deserialize_from_(toml, ptr_);
    }

  private:
    void* ptr_ = nullptr;
    util::function_ptr<void(void*)> destroy_ = nullptr;
    util::function_ptr<void(toml::value&, void*)> serialize_into_ = nullptr;
    util::function_ptr<void(const toml::value&, void*)> deserialize_from_ = nullptr;
  };

  // Specializations

  template<typename T, unsigned Order>
  struct serialize_impl : serialize_impl<T, Order - 1> {};

  template<typename T>
  struct serialize_impl<T, 0> {};

  // Using toml11
  template<toml::ATomlSerializable T>
  struct serialize_impl<T, 0> {
    static void serialize_into(toml::value& toml, const T& value)
    {
      toml = value;
    }
    static void deserialize_from(const toml::value& toml, T& value)
    {
      value = toml::get<T>(toml);
    }
  };

  template<ASerializable T, typename A>
  struct serialize_impl<std::vector<T, A>, 1> {
    static void serialize_into(toml::value& toml, const std::vector<T, A>& r)
    {
      toml::ensure_array(toml);
      for (int i = 0; i < r.size(); i++) {
        if (i == toml.as_array().size()) toml.as_array().emplace_back();
        util::serialize_into(toml.as_array()[i], r[i]);
      }
    }
    static void deserialize_from(const toml::value& toml, std::vector<T, A>& r)
    {
      r.clear();
      for (const auto& v : toml.as_array()) {
        r.emplace_back(util::deserialize<T>(v));
      }
    }
  };

  template<ASerializable T, std::size_t N>
  struct serialize_impl<std::array<T, N>, 1> {
    static void serialize_into(toml::value& toml, const std::array<T, N>& r)
    {
      toml::ensure_array(toml);
      toml.as_array().resize(N);
      for (auto&& [src, dst] : util::zip(r, toml.as_array())) {
        util::serialize_into(dst, src);
      }
    }
    static void deserialize_from(const toml::value& toml, std::array<T, N>& r)
    {
      if (toml.as_array().size() != N) {
        throw std::invalid_argument(toml::format_error(
          fmt::format("Expected array of size {}, got {}.\n", N, toml.as_array().size()), toml, "here"));
      }
      for (auto&& [input, toml] : util::zip(r, toml.as_array())) {
        util::deserialize_from(toml, input);
      }
    }
  };

  template<AVisitable T>
  struct serialize_impl<T, 2> {
    static void serialize_into(toml::value& toml, const T& value)
    {
      toml::ensure_table(toml);
      util::visit(value, [&](util::string_ref name, const auto& member) {
        util::serialize_into(toml.as_table()[name.c_str()], member);
      });
    }
    static void deserialize_from(const toml::value& toml, T& value)
    {
      util::visit(value, [&](util::string_ref name, auto& member) {
        try {
          util::deserialize_from(toml::find(toml, name.c_str()), member);
        } catch (std::out_of_range& e) {
        }
      });
    }
  };

  // With member functions
  template<typename T>
  requires requires(const toml::value& ctoml, toml::value& toml, T& obj, const T& cobj)
  {
    cobj.serialize_into(toml);
    obj.deserialize_from(ctoml);
  } //
  struct serialize_impl<T, 3> {
    static void serialize_into(toml::value& toml, const T& value)
    {
      value.serialize_into(toml);
    }
    static void deserialize_from(const toml::value& toml, T& value)
    {
      value.deserialize_from(toml);
    }
  };

  template<AnEnum E>
  struct serialize_impl<E, 3> {
    static void serialize_into(toml::value& toml, const E& value)
    {
      toml = util::enum_name(value);
    }
    static void deserialize_from(const toml::value& toml, E& value)
    {
      auto opt = util::enum_cast<E>(std::string_view(toml.as_string()));
      if (!opt) {
        throw std::invalid_argument(fmt::format("Invalid name when deserializing enum: {}", toml.as_string()));
      }
      value = *opt;
    }
  };

} // namespace otto::util
