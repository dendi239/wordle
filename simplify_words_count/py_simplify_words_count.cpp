#include <fstream>
#include <iostream>
#include <string>

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "simplify_words_count.hpp"

namespace py = pybind11;

PYBIND11_MODULE(py_simplify_words_count, m) {
  using namespace py::literals;

  py::object strategy = static_cast<py::object>(
      py::module_::import("strategy.strategy").attr("Strategy"));

  py::class_<::wordle::EliminateMostWordsStrategy>(
      m, "EliminateMostWordsStrategy", strategy,
      "Strategy that eliminates most words in the worst case.")
      .def(pybind11::init<const std::string &>(), "dict_path"_a,
           "Initializes strategy with given dictionary file.")
      .def("possible_words_count",
           &::wordle::EliminateMostWordsStrategy::PossibleWordsCount,
           "Amount of words that can be hidden.")
      .def("possible_words",
           &::wordle::EliminateMostWordsStrategy::PossibleWords,
           "Words that can be hidden.");
}
