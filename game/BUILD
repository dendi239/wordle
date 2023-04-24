load("@rules_python//python:defs.bzl", "py_binary")

py_binary(
    name = "game",
    srcs = ["game.py"],
    data = ["//data:nytimes-words.txt"],
    main = "game.py",
    deps = [
        "//strategy:io_strategy",
        "//wordle:local_wordle",
    ],
)
