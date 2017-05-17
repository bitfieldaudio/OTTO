#pragma once

#include <vector>

template<class T>
std::vector<char> serialize(T);

template<class T>
T deserialize(std::vector<char>);
