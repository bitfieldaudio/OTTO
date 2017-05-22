#include <plog/Log.h>

#include "module.h"
#include "util/serialization.h"

namespace module {

std::vector<char> Data::Field::serialize() {
  return top1::serialize<float>(*dataPtr);
}

void Data::Field::deserialize(std::vector<char>  data) {
  *dataPtr = top1::deserialize<float>(data);
}

std::vector<char> Data::serialize() {
  std::vector<char> xs;
  for (auto field : fields) {
    if (field.second->preserve) {
      std::vector<char> name = top1::serialize(field.first);
      std::vector<char> nameSize = top1::serialize<uint32_t>(name.size());
      std::vector<char> data = field.second->serialize();
      std::vector<char> dataSize = top1::serialize<uint32_t>(data.size());
      xs.insert(xs.end(), nameSize.begin(), nameSize.end());
      xs.insert(xs.end(), name.begin(), name.end());
      xs.insert(xs.end(), dataSize.begin(), dataSize.end());
      xs.insert(xs.end(), data.begin(), data.end());
    }
  }
  return xs;
}

void Data::deserialize(std::vector<char>  data) {
  for (uint i = 0; i < data.size(); i++) {
    uint nameSize = top1::deserialize<uint32_t>(
      std::vector<char>(data.begin() + i, data.begin() + i += 4));
    std::string name = top1::deserialize<std::string>(
      std::vector<char>(data.begin() + i, data.begin() + i += nameSize ));
    if (fields[name] != NULL) {
      uint dataSize = top1::deserialize<uint32_t>(
        std::vector<char>(data.begin() + i, data.begin() + i += 4 ));
      fields[name]->deserialize(
        std::vector<char>(data.begin() + i, data.begin() + i += dataSize));
    } else {
      LOGE << "Unrecognized field: " << name;
    }
  }
}
}
