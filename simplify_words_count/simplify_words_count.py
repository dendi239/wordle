"""Eliminate most words strategy.

Eliminates the most words in the worst case.
This is python wrapper, refer to .hpp/.cpp file for implementation.
"""

import strategy.strategy as strategy
import wordle.wordle as wordle
import simplify_words_count.py_simplify_words_count


class EliminateMostWordsStrategy(strategy.Strategy):
    """Strategy that eliminates most words in the worst case."""

    def __init__(self, dict_path: str) -> None:
        self.strategy = (
            simplify_words_count.py_simplify_words_count.EliminateMostWordsStrategy(
                dict_path
            )
        )

    def new_word(self) -> str:
        return self.strategy.new_word()

    def record(self, word: str, matches: wordle.TMatches) -> None:
        self.strategy.record(word, matches)

    @classmethod
    def default(cls) -> "EliminateMostWordsStrategy":
        """Default implementation that using nytimes words list."""
        return EliminateMostWordsStrategy("data/nytimes-words.txt")
