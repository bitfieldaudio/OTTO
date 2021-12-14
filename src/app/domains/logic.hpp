#pragma once

#include "lib/itc/domain.hpp"

namespace otto {
  struct LogicDomain : itc::StaticDomain<struct logic_domain_tag_t> {};
} // namespace otto
