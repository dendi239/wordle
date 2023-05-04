load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")
load("@rules_python//python:defs.bzl", "py_library")

cc_library(
    name = "libwordle",
    srcs = ["wordle.cpp"],
    hdrs = ["wordle.hpp"],
    visibility = ["//visibility:public"],
    deps = ["//utility"],
)

pybind_extension(
    name = "py_wordle",
    srcs = ["py_wordle.cpp"],
    deps = [":libwordle"],
)

py_library(
    name = "wordle",
    srcs = ["wordle.py"],
    visibility = ["//visibility:public"],
    deps = [":py_wordle"],
)

py_library(
    name = "io_wordle",
    srcs = ["io_wordle.py"],
    deps = [":wordle"],
)

py_library(
    name = "local_wordle",
    srcs = [
        "local_wordle.py",
        "//data:database",
    ],
    visibility = [
        "//visibility:public",
    ],
    deps = [":wordle"],
)
