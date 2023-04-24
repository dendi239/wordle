"""Retains ownership of default database."""

DEFAULT_DATABASE = "data/nytimes-words.txt"


def load_dictionary(dict_path: str) -> list[str]:
    with open(dict_path) as f:
        words = [line.strip() for line in f]
    return words
