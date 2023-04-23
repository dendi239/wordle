#include "simplify_words_count.hpp"

#include <algorithm>
#include <atomic>
#include <random>
#include <thread>

namespace wordle {

EliminateMostWordsStrategy::EliminateMostWordsStrategy(
    const std::string &dict_path) {
  std::ifstream dictionary(dict_path);
  std::string word;

  while (dictionary >> word) {
    words_.push_back(word);
  }

  dictionary_ = words_;
  ::std::mt19937 rnd(239);
  ::std::shuffle(dictionary_.begin(), dictionary_.end(), rnd);
}

void EliminateMostWordsStrategy::RecordMatches(
    const ::std::string &word, const Matches &matches) {
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
  if (words_.size() == 1) {
    return words_[0];
  }

  ::std::atomic<int> best(words_.size());
  ::std::mutex mu;

  const int threads_count = std::thread::hardware_concurrency();
  ::std::vector<::std::thread> workers;

  for (int ithread = 0; ithread < threads_count; ++ithread) {
    auto begin =
        dictionary_.begin() + ithread * dictionary_.size() / threads_count;
    auto end = dictionary_.begin() +
               (ithread + 1) * dictionary_.size() / threads_count;

    using Iter = decltype(begin);

    workers.emplace_back(
        [&](Iter begin, Iter end) {
          for (auto it = begin; it != end; ++it) {
            auto word = *it;
            auto possible = GetScore(word, best);
            if (possible.score < best) {
              ::std::lock_guard<::std::mutex> lock(mu);
              best = possible.score;
              guess_ = word;
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
    cluster.push_back(word);
    score.score = ::std::max<int>(score.score, cluster.size());
    if (score.score >= limit) {
      break;
    }
  }

  return score;
}

}  // namespace wordle
