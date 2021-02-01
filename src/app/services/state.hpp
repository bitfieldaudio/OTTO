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
      util::serialize_into(json_, *this);
      json::write_to_file(json_, file_path_);
    }

    void read_from_file()
    {
      if (!std::filesystem::exists(file_path_)) {
        LOGW("State file {} not found", file_path_);
        return;
      }
      json_ = json::parse_file(file_path_);
      util::deserialize_from(json_, *this);
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
    json::value json_;
    std::filesystem::path file_path_;
  };

} // namespace otto::services
