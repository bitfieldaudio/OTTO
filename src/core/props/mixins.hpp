#pragma once

#include "base.hpp"
#include "macros.hpp"
#include "util/utility.hpp"

#include <json.hpp>

namespace otto::core::props {

  namespace mixins {

    OTTO_PROPS_MIXIN( //
      has_value,
      // on_set can be used to modify the value before asignment,
      // as well as updating cached variables.
      HOOKS((on_set, value_type)),
      LEAF_INTERFACE(struct { const std::function<void()> reset; }))
    {
      OTTO_PROPS_MIXIN_DECLS(has_value);

      has_value_() {}
      has_value_(const value_type& v) : _value(v) {}

      const value_type& get() const
      {
        return _value;
      }

      void set(const value_type& v)
      {
        _value = run_hook<hooks::on_set>(v);
      }

      void reset(){};

      self_type& operator=(const value_type& rhs)
      {
        set(rhs);
        return *this;
      }

      operator const value_type&() const
      {
        return get();
      }

    protected:
      value_type _value;

      interface_type interface_ = {[this]() { reset(); }};
    };

    OTTO_PROPS_MIXIN(has_limits) {
      OTTO_PROPS_MIXIN_DECLS(has_limits);

      void init(const value_type& min, const value_type& max) {
        _min = min;
        _max = max;
      }

      void on_hook(hook<has_value::hooks::on_set, HookOrder::Early>& hook) {
        hook.value() = std::clamp(hook.value(), _min, _max);
      }

    protected:
      value_type _min;
      value_type _max;
    };

    OTTO_PROPS_MIXIN(has_name)
    {
      OTTO_PROPS_MIXIN_DECLS(has_name);

      void init(std::string name)
      {
        _name = name;
      }

      const std::string& name()
      {
        return _name;
      }

    protected:
      std::string _name;
    };

    struct JsonClient {
      const std::string& name;
      std::function<void(const nlohmann::json&)> from_json;
      std::function<nlohmann::json()> to_json;
    };

    OTTO_PROPS_MIXIN(serializable, //
      REQUIRES(has_value, has_name),
      LEAF_INTERFACE(JsonClient),
      EXTEND_BRANCH_INTERFACE({
          void from_json(const nlohmann::json& js) {
          }

          void to_json(const nlohmann::json& js) {
          }
      }))
    {
      OTTO_PROPS_MIXIN_DECLS(serializable);

      nlohmann::json to_json() const
      {
        return as<has_value>().get();
      }

      void from_json(const nlohmann::json& js) {
        as<has_value>().set(js);
      }

      const interface_type& interface() {
        return interface_;
      }

    private:
      const interface_type interface_ = {
        as<has_name>().name(),
        util::capture_this(&self_type::from_json, this),
        util::capture_this(&self_type::to_json, this),
      };
    };

    struct FaustLink {
      enum struct Type { ToFaust, FromFaust };

      FaustLink(const std::string_view& name,
                const std::function<float()>& get,
                float* faust_var)
        : name(name),
          get_or_set_(get),
          faust_var_(faust_var),
          type(Type::ToFaust)
      {}

      FaustLink(const std::string_view& name,
                const std::function<void(float)>& set,
                float* faust_var)
        : name(name),
          get_or_set_(set),
          faust_var_(faust_var),
          type(Type::FromFaust)
      {}

      void refresh() {
        if (type == Type::ToFaust) {
          *faust_var_ = mpark::get<0>(get_or_set_)();
        } else {
          mpark::get<1>(get_or_set_)(*faust_var_);
        }
      }

      void update(float& fptr) {
        if (type == Type::ToFaust) {
          *faust_var_ = fptr;
        } else {
          fptr = *faust_var_;
        }
      }

      const std::string_view name;

    private:
      mpark::variant<std::function<float()>, std::function<void(float)>> const get_or_set_;
      float* const faust_var_;

    public:
      Type const type;
    };

    OTTO_PROPS_MIXIN(faust_link, //
      REQUIRES(has_value),
      LEAF_INTERFACE(struct {
        const std::function<void()> refresh_links;
      }),
      EXTEND_BRANCH_INTERFACE({
        void refresh_links() {
          for (auto&& itf : children()) {
            if (itf.is_branch()) itf.get_branch().refresh_links();
            else itf.get_leaf().refresh_links();
          }
        }
      }))
    {
      OTTO_PROPS_MIXIN_DECLS(faust_link);

      void refresh_links() {
        for (auto&& fl : faust_links_) {
          fl.refresh();
        }
      }

      void add_link(const FaustLink& fl) {
        faust_links_.push_back(fl);
      }

      void clear_links() {
        faust_links_.clear();
      }

      void on_hook(hook<has_value::hooks::on_set, HookOrder::After> & hook) {
        for (auto&& fl : faust_links_) {
          if (fl.type == FaustLink::Type::ToFaust) {
            fl.update(hook.value());
          }
        }
      }

      interface_type& interface() noexcept
      {
        return interface_;
      }

    private:
      std::vector<interface_type> faust_links_;

      interface_type interface_ = {
        util::capture_this(&self_type::refresh_links, this)};
    };

    OTTO_PROPS_MIXIN(steppable, REQUIRES(has_value))
    {
      OTTO_PROPS_MIXIN_DECLS(steppable);

      static_assert(util::is_number_or_enum_v<value_type>,
                    "The 'steppable' mixin requires a number or enum type");

      void init(value_type p_step_size = value_type{1})
      {
        step_size = p_step_size;
      }

      void step(int n)
      {
        as<has_value>().set(as<has_value>().get() + n * step_size);
      }

      value_type step_size;
    };

  } // namespace mixins

} // namespace otto::core::props
