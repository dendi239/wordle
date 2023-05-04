#pragma once

#include <string>
#include <vector>

namespace utility {

template <typename Hasher = ::std::hash<::std::string>>
class StringSet {
 public:
  StringSet(Hasher hasher = {}) : hasher_(hasher) {}

  template <typename Iterator>
  StringSet(Iterator begin, Iterator end, Hasher hasher = {});

  auto begin() const { return strings_.begin(); }  // NOLINT
  auto end() const { return strings_.end(); }      // NOLINT

  uint64_t GetHash() const noexcept { return hash_; }

  void Add(::std::string string) {
    hash_ ^= hasher_(string);
    strings_.push_back(::std::move(string));
  }

  const ::std::vector<::std::string> &Raw() const { return strings_; }

  size_t Size() const { return strings_.size(); }

  bool operator==(const StringSet &other) const {
    if (hash_ != other.hash_ || Size() != other.Size()) {
      return false;
    }

    if (strings_ == other.strings_) {
      return true;
    }

    auto my = strings_, their = other.strings_;
    ::std::sort(my.begin(), my.end());
    ::std::sort(their.begin(), their.end());

    return my == their;
  }

 private:
  uint64_t hash_;
  Hasher hasher_;
  ::std::vector<::std::string> strings_;
};

template <typename Hasher>
template <typename Iterator>
StringSet<Hasher>::StringSet(Iterator begin, Iterator end, Hasher hasher)
    : hash_{0}, hasher_{hasher} {
  strings_.reserve(::std::distance(begin, end));
  for (auto it = begin; it != end; ++it) {
    Add(*it);
  }
}

}  // namespace utility

namespace std {

template <typename Hasher>
struct hash<::utility::StringSet<Hasher>> {
  uint64_t operator()(
      const ::utility::StringSet<Hasher> &string_set) const noexcept {
    return string_set.GetHash();
  }
};

}  // namespace std
