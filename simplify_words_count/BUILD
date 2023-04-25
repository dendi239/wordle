load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")
load("@rules_python//python:defs.bzl", "py_library")

cc_library(
    name = "lib_simplify_words_count",
    srcs = ["simplify_words_count.cpp"],
    hdrs = ["simplify_words_count.hpp"],
    deps = ["//wordle:libwordle"],
)

pybind_extension(
    name = "py_simplify_words_count",
    srcs = ["py_simplify_words_count.cpp"],
    deps = [":lib_simplify_words_count"],
)

py_library(
    name = "simplify_words_count",
    srcs = ["simplify_words_count.py"],
    visibility = ["//:__pkg__"],
    deps = [
        ":py_simplify_words_count",
        "//data:database",
        "//strategy",
    ],
)
