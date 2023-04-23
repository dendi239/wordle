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

py_binary(
    name = "wordle",
    srcs = ["wordle.py"],
    data = ["//data:nytimes-words.txt"],
    main = "wordle.py",
    visibility = ["//visibility:public"],
    deps = [":pywordle"],
)

py_library(
    name = "local_wordle",
    srcs = ["local_wordle.py"],
    visibility = ["//visibility:public"],
    deps = [":wordle"],
)
