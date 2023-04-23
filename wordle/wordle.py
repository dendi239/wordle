"""Base Wordle definitions."""

#! /usr/bin/env python3

import abc
import argparse
import string


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
    'Match',
    'TMatches',
    'Wordle',
    'UnknownWordException',
    'get_matches',
    'parse_matches',
    'repr_matches',
    'load_dictionary',
]


PROMPT = "Type your word: "
DEFAULT_DATABASE = "data/nytimes-words.txt"
MATCH_TO_SYMBOL = {
    Match.NOT_PRESENT: ' ',
    Match.EXACT_PLACE: '^',
    Match.NOT_HERE: '.',
}
SYMBOL_TO_MATCH = {s: m for m, s in MATCH_TO_SYMBOL.items()}


class IOWorlde(Wordle):
    def __init__(self, path_to_dict: str) -> None:
        self.words = load_dictionary(path_to_dict)

    def test(self, attempt: str) -> TMatches:
        print(f">>> {attempt}")
        mask = input(">>> ")
        return tuple([
            SYMBOL_TO_MATCH[s]
            for s in mask
        ])


class Guesser:
    def __init__(self, worlde: Wordle) -> None:
        self.alphabet = string.ascii_lowercase
        self.wordle = worlde
        self.used = set()
        self.not_used = set()

    def test(self, attempt: str) -> TMatches:
        matches = self.wordle.test(attempt)
        print(attempt)
        print(''.join(MATCH_TO_SYMBOL[c] for c in matches), sep='')

        for c, m in zip(attempt, matches):
            if m == Match.NOT_PRESENT:
                self.not_used.add(c)
            else:
                self.used.add(c)

        print("Used:", ''.join(c for c in self.alphabet if c in self.used))
        print("Not used:", ''.join(c for c in self.alphabet if c in self.not_used))
        print("Unknown:", ''.join(
            c for c in self.alphabet if c not in self.used and c not in self.not_used))

        return matches


def load_dictionary(dict_path: str) -> list[str]:
    with open(dict_path) as f:
        words = [line.strip() for line in f]
    return words


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('--seed', type=int, default=-1)
    parser.add_argument('--dict_path', default=DEFAULT_DATABASE)

    args = parser.parse_args()

    word = None
    if args.seed != -1:
        word = load_dictionary(DEFAULT_DATABASE)[args.seed]

    wordle = LocalWordle(args.dict_path, word)

    alphabet = string.ascii_lowercase
    used, not_used = set(), set()

    while True:
        attempt = input(PROMPT)
        try:
            matches = wordle.test(attempt)
            print(''.join(' ' for _ in PROMPT), ''.join(MATCH_TO_SYMBOL[c]
                                                        for c in matches), sep='')
        except UnknownWordException:
            print(f"Unknown word '{attempt}'")
            continue

        for c, m in zip(attempt, matches):
            if m == Match.NOT_PRESENT:
                not_used.add(c)
            else:
                used.add(c)

        print("Used:", ''.join(c for c in alphabet if c in used))
        print("Not used:", ''.join(c for c in alphabet if c in not_used))
        print("Unknown:", ''.join(
            c for c in alphabet if c not in used and c not in not_used))

        if all(m == Match.EXACT_PLACE for m in matches):
            print("Congrats!")
            break


if __name__ == '__main__':
    main()
