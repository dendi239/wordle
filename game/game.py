#! /usr/bin/env python3

import argparse

from data.database import DEFAULT_DATABASE, load_dictionary
from strategy.io_strategy import IOStrategy
from wordle.wordle import Match, load_dictionary
from wordle.local_wordle import LocalWordle


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--seed", type=int, default=-1)
    parser.add_argument("--dict_path", default=DEFAULT_DATABASE)

    args = parser.parse_args()

    word = None
    if args.seed != -1:
        word = load_dictionary(args.dict_path)[args.seed]

    s = IOStrategy()
    w = LocalWordle(args.dict_path, word)

    try:
        while True:
            guess = s.new_word()
            matches = w.test(guess)
            s.record(guess, matches)

            if all(m == Match.EXACT_PLACE for m in matches):
                break
    except KeyboardInterrupt:
        pass
    except EOFError:
        pass


if __name__ == "__main__":
    main()
