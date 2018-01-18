#pragma once

#include "base.hpp"
#include "macros.hpp"

#include <json.hpp>

namespace otto::core::props {

  namespace mixins {

    OTTO_PROPS_MIXIN(has_value)
    {
      OTTO_PROPS_MIXIN_DECLS(has_value);

      virtual value_type get() const
      {
        return value;
      }

      virtual void set(const value_type& v)
      {
        value = v;
      }

      self_type& operator=(const value_type& rhs)
      {
        value = rhs;
        return *this;
      }

      operator const value_type&() const
      {
        return value;
      }

      value_type value;
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

    OTTO_PROPS_MIXIN(serializable)
    {
      OTTO_PROPS_MIXIN_DECLS(serializable);

      virtual nlohmann::json to_json() const
      {
        
      }
    };

    OTTO_PROPS_MIXIN(faust_link)
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

    OTTO_PROPS_MIXIN(steppable, has_value)
    {
      OTTO_PROPS_MIXIN_DECLS(steppable);

      void init(value_type p_step_size = value_type{1})
      {
        step_size = p_step_size;
      }

      virtual void step(int n)
      {
        //base<has_value>::set(base<has_value>::get() + n * step_size);
      }

      value_type step_size;
    };

  } // namespace mixins

} // namespace otto::core::props
