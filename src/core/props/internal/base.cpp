#include "base.hpp"

namespace otto::core::props {

  property_base::property_base(branch_base* parent, std::string const& name)
    : parent_(parent), name_(name)
  {
    if (parent_ != nullptr) {
      parent->push_back(this);
    }
  }
}
