load("@rules_python//python:defs.bzl", "py_library")

py_library(
    name = "database",
    srcs = ["database.py"],
    data = [":nytimes-words.txt"],
    visibility = ["//visibility:public"],
)
