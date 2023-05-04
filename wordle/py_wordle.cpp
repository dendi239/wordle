#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "wordle.hpp"

namespace py = pybind11;

PYBIND11_MODULE(py_wordle, m) {
  using namespace py::literals;

  m.def("get_matches", &::wordle::GetMatchesStr, "guess"_a, "word"_a,
        "Gets matches for given attempt with word");

  m.def("parse_matches", &::wordle::ParseMatches, "matches_str"_a,
        "Parses matches from given string");

  m.def("repr_matches", &::wordle::ReprMatches, "matches"_a,
        "Represents matches into string");

  pybind11::enum_<::wordle::Match>(m, "Match")
      .value("NOT_PRESENT", ::wordle::Match::NOT_PRESENT)
      .value("EXACT_PLACE", ::wordle::Match::EXACT_PLACE)
      .value("NOT_HERE", ::wordle::Match::NOT_HERE);
}
