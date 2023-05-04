"""Eliminate most words strategy.

Eliminates the most words in the worst case.
This is python wrapper, refer to .hpp/.cpp file for implementation.
"""

import data.database as data
import strategy.strategy as strategy
import wordle.wordle as wordle
import simplify_words_count.py_simplify_words_count


class EliminateMostWordsStrategy(simplify_words_count.py_simplify_words_count.EliminateMostWordsStrategy):
    """Strategy that eliminates most words in the worst case."""

    @classmethod
    def default(cls) -> "EliminateMostWordsStrategy":
        """Default implementation that using nytimes words list."""
        return EliminateMostWordsStrategy(data.DEFAULT_DATABASE)
