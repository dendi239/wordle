#include "simplify_words_count.hpp"

#include <algorithm>
#include <atomic>
#include <random>
#include <thread>

namespace wordle {

EliminateMostWordsStrategy::NewWordCache
    EliminateMostWordsStrategy::shared_cache;

EliminateMostWordsStrategy::EliminateMostWordsStrategy(
    const std::string &dict_path)
    : ::wordle::Strategy(), cache_(&shared_cache) {
  std::ifstream dictionary(dict_path);
  std::string word;

  while (dictionary >> word) {
    words_.Add(word);
  }

  dictionary_ = words_;
}

void EliminateMostWordsStrategy::RecordMatches(const ::std::string &word,
                                               const Matches &matches) {
  if (word == guess_) {
    words_ = options_[matches];
    options_ = {};
    guess_ = {};
    return;
  }

  words_ = GetScore(word).options[matches];
  options_ = {};
  guess_ = {};
}

::std::string EliminateMostWordsStrategy::NewWord() {
  if (words_.Size() == 1) {
    return *words_.begin();
  }

  if (cache_->Known(words_)) {
    return (*cache_)(words_);
  }
  auto &guess = (*cache_)(words_);

  ::std::atomic<int> best(words_.Size() + 10);
  ::std::mutex mu;

  const int threads_count = std::thread::hardware_concurrency();
  ::std::vector<::std::thread> workers;

  for (int ithread = 0; ithread < threads_count; ++ithread) {
    auto begin =
        dictionary_.begin() + ithread * dictionary_.Size() / threads_count;
    auto end = dictionary_.begin() +
               (ithread + 1) * dictionary_.Size() / threads_count;

    using Iter = decltype(begin);

    workers.emplace_back(
        [&](Iter begin, Iter end) {
          for (auto it = begin; it != end; ++it) {
            auto word = *it;
            auto possible = GetScore(word, best);
            if (possible.score < best) {
              ::std::lock_guard<::std::mutex> lock(mu);
              best = possible.score;
              guess_ = guess = word;
              options_ = ::std::move(possible.options);
            }
          }
        },
        begin, end);
  }

  for (auto &worker : workers) {
    worker.join();
  }

  return guess_;
}

auto EliminateMostWordsStrategy::GetScore(::std::string_view guess,
                                          int limit) const -> Score {
  Score score;

  for (auto word : words_) {
    auto matches = GetMatches(guess, word);
    auto &cluster = score.options[matches];
    cluster.Add(word);
    score.score = ::std::max<int>(score.score, cluster.Size());
    if (score.score >= limit) {
      break;
    }
  }

  return score;
}

size_t EliminateMostWordsStrategy::PossibleWordsCount() const {
  return words_.Size();
}

const ::std::vector<::std::string> &EliminateMostWordsStrategy::PossibleWords()
    const {
  return words_.Raw();
}

bool EliminateMostWordsStrategy::NewWordCache::Known(
    const ::utility::StringSet<> &strings) const {
  auto strings_it = strings_to_word_.find(strings);
  if (strings_it == strings_to_word_.end()) {
    return false;
  }

  return true;
}

::std::string &EliminateMostWordsStrategy::NewWordCache::operator()(
    const ::utility::StringSet<> &strings) {
  return strings_to_word_[strings];
}

}  // namespace wordle
