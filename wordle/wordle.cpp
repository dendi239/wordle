#include "wordle.hpp"

#include "utility/char-map.hpp"

namespace wordle {

Matches GetMatchesStr(::std::string guess, ::std::string word) {
  return GetMatches(guess, word);
}

::std::string ReprMatches(const Matches &matches) {
  ::std::string result;
  result.reserve(matches.size());
  const ::std::string_view options = " ^.";
  for (auto m : matches) {
    result.push_back(options[static_cast<int>(m)]);
  }
  return result;
}

Matches ParseMatches(const ::std::string &matches_str) {
  Matches matches;
  matches.reserve(matches_str.size());

  for (auto c : matches_str) {
    switch (c) {
      case ' ':
        matches.push_back(Match::NOT_PRESENT);
        break;
      case '.':
        matches.push_back(Match::NOT_HERE);
        break;
      case '^':
        matches.push_back(Match::EXACT_PLACE);
        break;
    }
  }
  return matches;
}

::std::vector<Match> GetMatches(::std::string_view guess,
                                ::std::string_view word) {
  std::vector<Match> result(guess.size(), Match::NOT_PRESENT);
  ::utility::LowercaseMap<int> cnts;

  for (auto c : word) {
    ++cnts[c];
  }

  for (size_t i = 0; i < word.size(); ++i) {
    if (word[i] == guess[i]) {
      --cnts[guess[i]];
      result[i] = Match::EXACT_PLACE;
    }
  }

  for (size_t i = 0; i < guess.size(); ++i) {
    if (result[i] == Match::NOT_PRESENT && cnts[guess[i]]) {
      --cnts[guess[i]];
      result[i] = Match::NOT_HERE;
    }
  }

  return result;
}

}  // namespace wordle