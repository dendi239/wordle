#pragma once

#include <fstream>
#include <string>
#include <string_view>
#include <unordered_map>

#include "strategy/strategy.hpp"
#include "utility/string-set.hpp"
#include "wordle/wordle.hpp"

namespace wordle {

class EliminateMostWordsStrategy : public Strategy {
 private:
  struct Score {
    int score = 0;
    ::std::unordered_map<Matches, ::utility::StringSet<>> options;
  };

 public:
  class NewWordCache {
   public:
    bool Known(const ::utility::StringSet<> &strings) const;
    ::std::string &operator()(const ::utility::StringSet<> &strings);

   private:
    ::std::unordered_map<::utility::StringSet<>, ::std::string>
        strings_to_word_;
  };

  static NewWordCache shared_cache;

  explicit EliminateMostWordsStrategy(const ::std::string &dict_path);
  EliminateMostWordsStrategy(const ::std::string &dict_path,
                             NewWordCache *cache);

  ::std::string NewWord() override;
  void RecordMatches(const ::std::string &word, const Matches &matches) override;

  size_t PossibleWordsCount() const;
  const ::std::vector<::std::string> &PossibleWords() const;

 private:
  Score GetScore(::std::string_view word,
                 int limit = ::std::numeric_limits<int>::max()) const;

  NewWordCache *cache_;

  ::std::string guess_;
  ::std::unordered_map<Matches, ::utility::StringSet<>> options_;
  ::utility::StringSet<> dictionary_, words_;
};

}  // namespace wordle
