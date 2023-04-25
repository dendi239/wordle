"""Local wordle"""

import random
import typing as tp

import data.database as data
import wordle.wordle as wordle


class LocalWordle(wordle.Wordle):
    """Local wordle represents wordle holding hidden word."""

    def __init__(self, path_to_dict: str, word: tp.Optional[str] = None) -> None:
        self.words = data.load_dictionary(path_to_dict)

        if word is not None:
            self.word = word
        else:
            self.word = random.choice(self.words)

    def test(self, attempt: str) -> wordle.TMatches:
        if attempt not in self.words:
            raise wordle.UnknownWordException(attempt)
        return wordle.get_matches(attempt, self.word)
