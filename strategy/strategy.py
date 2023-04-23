"""Base class for all wordle strategies"""

import abc
import typing as tp

import wordle.wordle as wordle


class Strategy(abc.ABC):
    """Base class for all wordle strategies"""

    @abc.abstractmethod
    def record(self, word: str, matches: wordle.TMatches) -> None:
        """Records information about the guess"""

    @abc.abstractmethod
    def new_word(self) -> str:
        """Picks new word to guess."""


class Scorer:
    """Scores particular *Strategy* on different words.
    
    Takes dictionary to work with and factory so each state is different.
    Stores all the stats in self.stats
    """
    def __init__(self, dictionary: tuple[str], strategy_factory: tp.Mapping[None, Strategy]):
        self.dictionary = dictionary
        self.factory = strategy_factory
        self.stats = [0] * 7

    def score(self, word: str) -> int:
        """Counts amount of tries for strategy to guess certain word"""
        strategy = self.factory()
        current = 0
        while True:
            guess = strategy.new_word()
            print(f"Guess: {guess}")
            current += 1

            if guess == word:
                while len(self.stats) <= current:
                    self.stats.append(0)
                self.stats[current] += 1
                return current

            matches = wordle.get_matches(guess, word)
            strategy.record(guess, matches)
