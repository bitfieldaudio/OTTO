#pragma once

#include "base.hpp"
#include "macros.hpp"

#include <json.hpp>

namespace otto::core::props {

  namespace mixins {

    OTTO_PROPS_MIXIN(has_value, HOOKS((on_set, value_type)))
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
    };

    OTTO_PROPS_MIXIN(has_limits) {
      OTTO_PROPS_MIXIN_DECLS(has_limits);

      void init(const value_type& min, const value_type& max) {
        _min = min;
        _max = max;
      }

      void on_hook(hook<has_value::hooks::on_set>& hook) {
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

    OTTO_PROPS_MIXIN(serializable, REQUIRES(has_value))
    {
      OTTO_PROPS_MIXIN_DECLS(serializable);

      nlohmann::json to_json() const
      {
        return as<has_value>().value;
      }
    };

    OTTO_PROPS_MIXIN(faust_link, REQUIRES(has_value))
    {
      OTTO_PROPS_MIXIN_DECLS(faust_link);

      void update_link();
      void add_link();
    };

    OTTO_PROPS_MIXIN(with_cache)
    {
      OTTO_PROPS_MIXIN_DECLS(with_cache);

      void update_cache();
      value_type cached_value();
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
