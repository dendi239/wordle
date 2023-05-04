#include "strategy.hpp"

namespace wordle {

::std::vector<::std::string> TriesToSolve(Strategy *strategy,
                                          const ::std::string &word) {
  ::std::vector<::std::string> result;
  while (result.empty() || result.back() != word) {
    auto guess = strategy->NewWord();
    auto matches = GetMatches(guess, word);
    strategy->RecordMatches(guess, matches);
    result.push_back(guess);
  }
  return result;
}

::std::vector<int> BuildStats(const ::std::vector<::std::string> &words,
                              ::std::function<Strategy *()> factory) {
  std::vector<int> stats;

  for (auto word : words) {
    auto strategy = factory();
    auto tries = TriesToSolve(strategy, word);
    while (stats.size() <= tries.size()) stats.push_back(0);
    ++stats[tries.size()];
  }

  return stats;
}

}  // namespace wordle