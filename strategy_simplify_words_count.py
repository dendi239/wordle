from dataclasses import dataclass
from collections import defaultdict
import typing as tp

import wordle


@dataclass
class State:
    guesses: tuple[tuple[str, tuple[wordle.Match]]]
    options: tuple[str]

    def record(self, word: str, matches: wordle.TMatches) -> None:
        self.guesses += ((word, matches),)
        self.options = tuple((
            option for option in self.options
            if wordle.get_matches(word, option) == matches
        ))

    def new_word(self, dictionary: tp.Iterable[str]) -> str:
        if len(self.options) == 1:
            return self.options[0]
        return min(dictionary, key=lambda w: score(w, self))
    
    @classmethod
    def default(cls) -> 'State':
        return State(
            guesses=tuple(),
            options=tuple(wordle.load_dictionary(wordle.DEFAULT_DATABASE)),
        )


def score(word: str, state: State) -> int:
    matches_to_secrets = defaultdict(int)

    for secret in state.options:
        matches_to_secrets[wordle.get_matches(word, secret)] += 1

    return max(matches_to_secrets.items(), key=lambda x: x[1])[1]
