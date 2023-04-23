#! /usr/bin/env python3

"""Updates current database with known nytimes words."""

import argparse
import asyncio
import csv
import dataclasses
import datetime
import typing as tp

import aiohttp

TStats = dict[str, tp.Any]


class NYSession:
    """Aiohttp based class for handling session of connection to nytimes.com"""

    def __init__(self):
        self.session = aiohttp.ClientSession()

    async def __aenter__(self) -> aiohttp.ClientSession:
        self.session = await self.session.__aenter__()
        return self

    async def __aexit__(
        self,
        exc_type: tp.Optional[tp.Type[BaseException]],
        exc_val: tp.Optional[BaseException],
        exc_tb: tp.Optional['TracebackType'],
    ) -> None:
        return await self.session.__aexit__(exc_type, exc_val, exc_tb)

    async def get_stats(self, date: datetime.date) -> TStats:
        """get stats of particular wordle by date."""
        url = f"https://www.nytimes.com/svc/wordle/v2/{date.strftime('%Y-%m-%d')}.json"
        return await (await self.session.get(url)).json()


@dataclasses.dataclass
class NYCSV:
    """Data stored within nytimes.csv"""
    launch_date: datetime.date
    fieldnames: tuple[str]
    rows: tuple[TStats]


def read_current_csv(csv_location: str) -> NYCSV:
    """Reads current csv file as it is."""
    with open(csv_location, 'r') as nytimescsv:
        reader = csv.DictReader(nytimescsv)
        fieldnames = reader.fieldnames
        rows = [row for row in reader]
        date = datetime.datetime.strptime(rows[0]['print_date'], '%Y-%m-%d')
        shift = datetime.timedelta(days=int(rows[0]['days_since_launch']))
        launch_date = date - shift

    return NYCSV(
        launch_date=launch_date,
        fieldnames=fieldnames,
        rows=tuple(rows),
    )


def sort_csv_data(csv_location: str) -> None:
    """Sorts data inside csv database."""
    csv_data = read_current_csv(csv_location)
    rows = sorted(list({row['id']: row for row in csv_data.rows}.values()),
                  key=lambda row: row['print_date'])

    with open(csv_location, 'w') as nytimescsv:
        writer = csv.DictWriter(nytimescsv, csv_data.fieldnames)
        writer.writeheader()
        writer.writerows(rows)


async def main() -> None:
    """Main function"""
    fieldnames = ["id", "solution", "print_date",
                  "days_since_launch", "editor"]

    parser = argparse.ArgumentParser()
    parser.add_argument('--csv', help='path to csv', default='nytimes/nytimes.csv')
    parser.add_argument('--shuffle', action='store_true',
                        help='removes duplicates from list and sorts by the date')
    args = parser.parse_args()

    csv_location = args.csv

    csv_data = read_current_csv(csv_location)
    known = {int(row['days_since_launch']) for row in csv_data.rows}

    async with NYSession() as session:
        with open(csv_location, 'a') as nytimescsv:
            for i in range((datetime.datetime.today() - csv_data.launch_date).days + 1):
                if i not in known:
                    writer = csv.DictWriter(nytimescsv, fieldnames)
                    writer.writerow(await session.get_stats(
                        csv_data.launch_date + datetime.timedelta(days=i)))

    if args.shuffle:
        sort_csv_data(csv_location)


if __name__ == '__main__':
    asyncio.run(main())
