#pragma once

#include <algorithm>
#include <array>

namespace utility {

template <class Key, class Value, Key low, Key high>
class RangedMap {
 public:
  RangedMap() { ::std::fill(data_.begin(), data_.end(), Value{}); }

  Value &operator[](Key key) { return data_[key - low]; }
  const Value &operator[](Key key) const { return data_[key - low]; }

 private:
  ::std::array<Value, high - low + 1> data_;
};

template <class Value>
using LowercaseMap = RangedMap<char, Value, 'a', 'z'>;

template <class Value, int low, int high>
using IntMap = RangedMap<int, Value, low, high>;

}  // namespace utility