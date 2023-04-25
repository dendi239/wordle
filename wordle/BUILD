load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")
load("@rules_python//python:defs.bzl", "py_binary")

cc_library(
    name = "libwordle",
    srcs = ["wordle.cpp"],
    hdrs = ["wordle.hpp"],
    visibility = ["//visibility:public"],
)

pybind_extension(
    name = "pywordle",
    srcs = ["pywordle.cpp"],
    deps = [":libwordle"],
)

py_library(
    name = "wordle",
    srcs = ["wordle.py"],
    visibility = ["//visibility:public"],
    deps = [":pywordle"],
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
