#include <plog/Log.h>

#include "module.h"

namespace module {

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
