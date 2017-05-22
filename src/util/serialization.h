#pragma once

#include <vector>
#include <iterator>

namespace top1 {

typedef char byte;

template<class T>
std::vector<byte> serialize(T);

template<class T>
T deserialize(std::vector<byte>);
}
