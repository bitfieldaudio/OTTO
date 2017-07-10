#include <plog/Log.h>

#include "module.h"

namespace module {

Opt<bool>::Opt(Data *data,
  std::string name,
  bool init,
  bool preserve)
  : TypedField<bool>(preserve, init) {
  data->addField(name, this);
  reset();
};

Opt<float>::Opt(Data *data,
  std::string name,
  float init,
  float min,
  float max,
  float step,
  bool preserve)
  : TypedField<float>(preserve, init),
  min(min),
  max(max),
  step(step) {
  data->addField(name, this);
  reset();
};

Opt<int>::Opt(Data *data,
  std::string name,
  int init,
  int min,
  int max,
  int step,
  bool preserve)
  : TypedField<int>(preserve, init),
  min(min),
  max(max),
  step(step) {
  data->addField(name, this);
  reset();
};

Opt<std::string>::Opt(Data *data,
 std::string name,
 std::string init,
 bool preserve)
  : TypedField<std::string>(preserve, init) {
  data->addField(name, this);
  reset();
};


top1::tree::Node Data::serialize() {
  top1::tree::Map node;
  for (auto field : fields) {
    if (field.second->preserve) {
      node[field.first] = field.second->serialize();
    }
  }
  return node;
}

void Data::deserialize(top1::tree::Node node) {
  node.match([&] (top1::tree::Map node) {
      for (auto &f : node) {
        if (fields.find(f.first) != fields.end()) {
          fields[f.first]->deserialize(f.second);
        } else {
          LOGE << "Unrecognized field: " << f.first;
        }
      }
    }, [] (auto) {});
}
}
