#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "wordle.hpp"

PYBIND11_MODULE(pywordle, m) {
  m.def("get_matches", &::wordle::GetMatchesStr,
        "Gets matches for given attempt with word");

  m.def("parse_matches", &::wordle::ParseMatches,
        "Parses matches from given string");

  m.def("repr_matches", &::wordle::ReprMatches,
        "Represents matches into string");

  pybind11::enum_<::wordle::Match>(m, "Match")
      .value("NOT_PRESENT", ::wordle::Match::NOT_PRESENT)
      .value("EXACT_PLACE", ::wordle::Match::EXACT_PLACE)
      .value("NOT_HERE", ::wordle::Match::NOT_HERE);
}
