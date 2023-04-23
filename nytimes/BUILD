load("@rules_python//python:defs.bzl", "py_binary")

py_binary(
    name = "wordle",
    srcs = ["wordle.py"],
    data = [
        "//data:nytimes-words.txt",
    ],
    main = "wordle.py",
    visibility = ["//:__pkg__"],
    deps = [
        ":nytimes",
        "//strategy:io_strategy",
        "//wordle",
        "//wordle:local_wordle",
    ],
)

py_binary(
    name = "nytimes",
    srcs = ["nytimes.py"],
    data = [":nytimes.csv"],
    main = "nytimes.py",
)
