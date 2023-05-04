"""Wordle with today's nytimes word."""

import asyncio
import argparse
import datetime
import typing as tp

import data.database as data
import nytimes.nytimes as nytimes
import strategy.io_strategy as io_strategy
import wordle.wordle as wordle
import wordle.local_wordle as local_wordle


PROMPT = "Type your word: "


async def get_wordle(
    date: tp.Optional[datetime.date] = None,
    dict_path: str = data.DEFAULT_DATABASE,
) -> wordle.Wordle:
    """Gets NYTimes wordle for specified date."""
    if date is None:
        date = datetime.date.today()

    await nytimes.amend_csv_to(date)
    for row in nytimes.read_current_csv(nytimes.DEFAULT_CSV_LOCATION).rows:
        if row["print_date"] == date.strftime("%Y-%m-%d"):
            return local_wordle.LocalWordle(dict_path, row["solution"])

    async with nytimes.NYSession() as session:
        return local_wordle.LocalWordle(
            dict_path, (await session.get_stats(date))["solution"]
        )


def main() -> None:
    """Main function."""
    parser = argparse.ArgumentParser()

    parser.add_argument("--dict_path", default=data.DEFAULT_DATABASE)
    parser.add_argument(
        "--date",
        type=lambda s: datetime.datetime.strptime(s, "%Y-%m-%d"),
        default=datetime.datetime.today(),
    )

    args = parser.parse_args()

    wrdle = asyncio.run(get_wordle(args.date.date(), args.dict_path))
    strat = io_strategy.IOStrategy()

    while True:
        try:
            attempt = strat.new_word()
            matches = wrdle.test(attempt)
            strat.record(attempt, matches)
        except wordle.UnknownWordException:
            print(f"Unknown word '{attempt}'")
            continue

        if all(m == wordle.Match.EXACT_PLACE for m in matches):
            print("Congrats!")
            break


if __name__ == "__main__":
    main()
