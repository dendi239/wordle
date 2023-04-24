"""IO based Wordle implementation.

Uses the same notation as other places:
- ' ' for non-existing character;
- '.' for existing character with wrong position;
- '^' for character sitting inplace.
"""

import wordle.wordle as wordle


class IOWorlde(wordle.Wordle):
    """IO based wordle"""

    def __init__(self, path_to_dict: str) -> None:
        self.words = wordle.load_dictionary(path_to_dict)

    def test(self, attempt: str) -> wordle.TMatches:
        print(f">>> {attempt}")
        mask = input(">>> ")
        return wordle.parse_matches(mask)
