load("@rules_python//python:defs.bzl", "py_library")
load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")

cc_library(
    name = "libstrategy",
    hdrs = ["strategy.hpp"],
    srcs = ["strategy.cpp"],
    visibility = ["//visibility:public"],
    deps = ["//wordle:libwordle"],
)

pybind_extension(
    name = "py_strategy",
    srcs = ["py_strategy.cpp"],
    deps = [":libstrategy"],
)

py_library(
    name = "strategy",
    srcs = ["strategy.py"],
    visibility = ["//visibility:public"],
    deps = [
        ":py_strategy",
        "//wordle",
    ],
)

py_library(
    name = "io_strategy",
    srcs = ["io_strategy.py"],
    visibility = ["//visibility:public"],
    deps = [
        "//strategy",
        "//wordle",
    ],
)
