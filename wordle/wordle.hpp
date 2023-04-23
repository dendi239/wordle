#pragma once

#include <string>
#include <vector>

namespace wordle {

enum class Match : uint8_t {
  NOT_PRESENT = 0,
  EXACT_PLACE = 1,
  NOT_HERE = 2,
};

using Matches = ::std::vector<Match>;

Matches GetMatches(::std::string_view guess, ::std::string_view word);
Matches GetMatchesStr(::std::string guess, ::std::string word);

::std::string ReprMatches(const Matches &matches);
Matches ParseMatches(const ::std::string &matches_str);

} // namespace wordle

namespace std {

template <> struct hash<::wordle::Matches> {
  int operator()(const ::wordle::Matches &matches) const noexcept {
    int result = 0;
    for (auto m : matches) {
      result = result * 3 + static_cast<uint8_t>(m);
    }
    return result;
  }
};

} // namespace std
