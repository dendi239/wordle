"""Base class for all wordle strategies"""

import typing as tp

import wordle.wordle as wordle
from strategy.py_strategy import Strategy


TStrategyFactory = tp.Callable[[], Strategy]


def tries_to_guess(strategy: Strategy, word: str) -> tp.List[str]:
    tries = []
    
    while True:
        guess = strategy.new_word()
        matches = wordle.get_matches(guess, word)
        strategy.record(guess, matches)
        tries.append(guess)

        if guess == word:
            break
    
    return tries



def build_stats(words: tp.Iterable[str], strategy_factory: TStrategyFactory) -> tp.List[int]:
    stats = [0]

    for word in words:
        tries = tries_to_guess(strategy_factory(), word)
        while len(stats) <= len(tries):
            stats.append(0)
        
        stats[len(tries)] += 1
    
    return stats
