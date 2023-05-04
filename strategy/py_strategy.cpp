#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "strategy.hpp"

namespace py = pybind11;

class PyStrategy : public ::wordle::Strategy {
 public:
  PyStrategy() = default;

  ::std::string NewWord() override {
    PYBIND11_OVERRIDE_PURE(::std::string, ::wordle::Strategy, NewWord);
  }

  void RecordMatches(const ::std::string &word,
                     const ::wordle::Matches &matches) override {
    PYBIND11_OVERRIDE_PURE(void, ::wordle::Strategy, RecordMatches, word,
                           matches);
  }
};

PYBIND11_MODULE(py_strategy, m) {
  using namespace py::literals;

  py::class_<::wordle::Strategy, PyStrategy>(
      m, "Strategy", "Base class for all wordle strategies")
      .def(py::init<>())
      .def("record", &::wordle::Strategy::RecordMatches, "word"_a, "matches"_a,
           "Records information about the guess")
      .def("new_word", &::wordle::Strategy::NewWord,
           "Picks new word to guess.");

  m.def("tries_to_solve", &::wordle::TriesToSolve, "strategy"_a, "word"_a);
  m.def("build_stats", [](std::vector<std::string> words, py::object factory) {
    return ::wordle::BuildStats(words, [factory] {
      auto f = factory.cast<std::function<py::object()>>();
      auto strategy = f();
      return strategy.cast<::wordle::Strategy *>();
    });
  }, "words"_a, "factory"_a);
}
