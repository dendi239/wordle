#include <fstream>
#include <iostream>
#include <string>

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "simplify_words_count.hpp"

PYBIND11_MODULE(py_simplify_words_count, m) {
  pybind11::class_<::wordle::EliminateMostWordsStrategy>(
      m, "EliminateMostWordsStrategy")
      .def(pybind11::init<const std::string &>())
      .def("record", &::wordle::EliminateMostWordsStrategy::RecordMatches)
      .def("new_word", &::wordle::EliminateMostWordsStrategy::NewWord);
}
