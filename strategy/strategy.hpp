#pragma once

#include "wordle/wordle.hpp"

namespace wordle {

// Base class for all strategies.
class Strategy {
 public:
  virtual ~Strategy() = default;

  // Gives new word to guess with.
  virtual ::std::string NewWord() = 0;

  // Records matches with given word, most likely to be returned by NewWord one.
  virtual void RecordMatches(const ::std::string &word,
                             const Matches &matches) = 0;
};

::std::vector<::std::string> TriesToSolve(Strategy *strategy,
                                          const ::std::string &word);

::std::vector<int> BuildStats(const ::std::vector<::std::string> &words,
                              ::std::function<Strategy *()> factory);

}  // namespace wordle
