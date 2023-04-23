load("@rules_python//python:defs.bzl", "py_library")

py_library(
    name = "strategy",
    srcs = ["strategy.py"],
    visibility = ["//visibility:public"],
    deps = [
        "//wordle",
    ],
)

py_library(
    name = "io_strategy",
    srcs = ["io_strategy.py"],
    visibility = ["//:__pkg__"],
    deps = [
        "//strategy",
        "//wordle",
    ],
)
