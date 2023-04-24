"""Base Wordle definitions."""

#! /usr/bin/env python3

import abc

from wordle.pywordle import Match, get_matches, parse_matches, repr_matches


TMatches = tuple[Match]


class UnknownWordException(Exception):
    """Unknown word exception"""

    def __init__(self, word: str) -> None:
        self.word = word


class Wordle(abc.ABC):
    """Base class for wordle based game"""

    @abc.abstractmethod
    def test(self, attempt: str) -> TMatches:
        """Tests attept for matches"""


__all__ = [
    "Match",
    "TMatches",
    "Wordle",
    "UnknownWordException",
    "get_matches",
    "parse_matches",
    "repr_matches",
]
