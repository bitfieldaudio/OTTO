#include "jsonfile.hpp"

#include <json.hpp>

namespace otto::util {

  using json = nlohmann::json;

  json treeToJson(const tree::Node &tree) {
    struct Visitor {
      json operator()(tree::Float n) {
        return json::number_float_t(n.value);
      }
      json operator()(tree::String n) {
        return json::string_t(n.value);
      }
      json operator()(tree::Int n) {
        return json::number_integer_t(n.value);
      }
      json operator()(tree::Bool n) {
        return json::boolean_t (n.value);
      }
      json operator()(tree::Null n) {
        return nullptr;
      }
      json operator()(tree::Array n) {
        json a = json::array();
        for (auto &el : n) {
          a.push_back(mapbox::util::apply_visitor(Visitor(), el));
        }
        return a;
      }
      json operator()(tree::Map n) {
        json m = json::object();
        for (auto &el : n) {
          m[el.first] = mapbox::util::apply_visitor(Visitor(), el.second);
        }
        return m;
      }
    };
    return mapbox::util::apply_visitor(Visitor(), tree);
  }

  tree::Node jsonToTree(const json &j) {
    if (j.is_null()) return tree::Null();
    if (j.is_boolean()) return tree::Bool { j.get<bool>() };
    if (j.is_number_integer()) return tree::Int { j.get<int>() };
    if (j.is_number()) return tree::Float { j.get<float>() };
    if (j.is_string()) return tree::String { j.get<std::string>() };
    if (j.is_array()) {
      tree::Array ar;
      for (auto &el : j) {
        ar.values.push_back(jsonToTree(el));
      }
      return ar;
    }
    if (j.is_object()) {
      tree::Map m;
      for (auto it = j.begin(); it != j.end(); ++it) {
        m[it.key()] = jsonToTree(it.value());
      }
      return m;
    }
    LOGE << "Unexpected json type";
    return tree::Null();
  }

  void JsonFile::read() {
    std::ifstream stream;
    stream.open(path);
    if (!stream) {
      LOGI << "Empty JsonFile, creating " << path;
      stream.close();
      write();
      stream.open(path);
    }
    json j;
    stream >> j;
    data = jsonToTree(j);
    stream.close();
  }

  void JsonFile::write() {
    std::ofstream stream(path, std::ios::trunc);
    stream << std::setw(2) << treeToJson(data) << std::endl;
    stream.close();
  }
}
