load("@rules_python//python:defs.bzl", "py_binary")

py_binary(
    name = "python",
    srcs = ["python.py"],
    main = "python.py",
    deps = [
        "//nytimes:wordle",
        "//simplify_words_count",
        "//strategy",
        "//strategy:io_strategy",
        "//wordle",
        "//wordle:local_wordle",
    ],
)
