import string

import strategy.strategy as strategy
import wordle.wordle as wordle


PROMPT = "Type your word: "


class IOStrategy(strategy.Strategy):
    """Strategy that asks user to make each guess"""

    def __init__(self) -> None:
        self.alphabet = string.ascii_lowercase
        self.used, self.not_used = set(), set()

    def record(self, word: str, matches: wordle.TMatches) -> None:
        print(''.join(' ' for _ in PROMPT), wordle.repr_matches(matches), sep='')

        for symb, match in zip(word, matches):
            if match == wordle.Match.NOT_PRESENT:
                self.not_used.add(symb)
            else:
                self.used.add(symb)

        print("Used:", ''.join(c for c in self.alphabet if c in self.used))
        print("Not used:", ''.join(c for c in self.alphabet if c in self.not_used))
        print("Unknown:", ''.join(
            c for c in self.alphabet if c not in self.used and c not in self.not_used))
        print()


    def new_word(self) -> str:
        return input(PROMPT)
