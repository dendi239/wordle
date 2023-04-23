#pragma once

#include <fstream>
#include <string>
#include <string_view>

#include "wordle/wordle.hpp"

namespace wordle {

class EliminateMostWordsStrategy {
 public:
  EliminateMostWordsStrategy(const std::string &dict_path);

  ::std::string NewWord();
  void RecordMatches(const ::std::string &word,
                     const Matches &matches);

 private:
  struct Score {
    int score = 0;
    ::std::unordered_map<Matches, ::std::vector<::std::string>> options;
  };

  Score GetScore(::std::string_view word,
                 int limit = ::std::numeric_limits<int>::max()) const;

  ::std::string guess_;
  ::std::unordered_map<Matches, ::std::vector<::std::string>> options_;
  ::std::vector<::std::string> dictionary_, words_;
};

}  // namespace wordle
