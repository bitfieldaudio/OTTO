#pragma once

#include <string_view>
#include <utility>

#include <boost/container/flat_map.hpp>

#include "lib/util/dynamic.hpp"
#include "lib/util/serialization.hpp"
#include "lib/util/smart_ptr.hpp"

#include "lib/logging.hpp"

namespace otto::services {

  struct StateManager {
    StateManager(std::filesystem::path path) : file_path_(std::move(path)) {}

    void add(std::string key, util::DynSerializable ser)
    {
      serializers_.try_emplace(std::move(key), std::move(ser));
    }

    bool remove(const std::string& key)
    {
      auto found = serializers_.find(key);
      if (found == serializers_.end()) return false;
      serializers_.erase(found);
      return true;
    }

    void write_to_file()
    {
      json::write_to_file(util::serialize(*this), file_path_);
    }

    void read_from_file()
    {
      if (!std::filesystem::exists(file_path_)) {
        LOGW("State file {} not found", file_path_);
        return;
      }
      try {
        util::deserialize_from(json::parse_file(file_path_), *this);
      } catch (json::value::parse_error& e) {
        LOGW("State file parse error!");
        LOGW("{}", e.what());
        auto corrupt = file_path_;
        corrupt += ".corrupt";
        std::filesystem::rename(file_path_, corrupt);
        LOGW("State file has been backed up as {}", corrupt);
      }
    }

    void visit(util::AVisitorOf<util::DynSerializable> auto&& visitor)
    {
      for (auto& [k, v] : serializers_) visitor(k, v);
    }
    void visit(util::AVisitorOf<util::DynSerializable> auto&& visitor) const
    {
      for (const auto& [k, v] : serializers_) visitor(k, v);
    }

  private:
    boost::container::flat_map<std::string, util::DynSerializable> serializers_;
    std::filesystem::path file_path_;
  };

} // namespace otto::services
