# Description: Deepspeech native client library.

load("//tensorflow:tensorflow.bzl",
     "if_x86")

cc_library(
    name = "deepspeech",
    srcs = ["deepspeech.cc"],
    hdrs = ["deepspeech.h"],
    deps = ["//tensorflow/core:core",
            ":deepspeech_utils"],
)

# We have a single rule including c_speech_features and kissfft here as Bazel
# doesn't support static linking in library targets.

cc_library(
    name = "deepspeech_utils",
    srcs = ["deepspeech_utils.cc",
            "beam_search.cc",
            "alphabet.h",
            "c_speech_features/c_speech_features.c",
            "kiss_fft130/kiss_fft.c",
            "kiss_fft130/tools/kiss_fftr.c"] +
           glob(["kenlm/lm/*.cc", "kenlm/util/*.cc", "kenlm/util/double-conversion/*.cc",
                 "kenlm/lm/*.hh", "kenlm/util/*.hh", "kenlm/util/double-conversion/*.h"],
                exclude = ["kenlm/*/*test.cc", "kenlm/*/*main.cc"]),
    hdrs = ["deepspeech_utils.h"],
    includes = ["c_speech_features",
                "kiss_fft130",
                "kenlm"],
    defines = ["KENLM_MAX_ORDER=6"],
    deps = ["//tensorflow/core:core",
            "//tensorflow/core/util/ctc",
            "//third_party/eigen3",
    ],

    # fma/avx/avx2 enabled in gcc cause significant performance decreases in
    # c_speech_features and so are force-disabled.
    copts = [] + if_x86(["-mno-fma", "-mno-avx", "-mno-avx2"]),
    nocopts = "(-fstack-protector|-fno-omit-frame-pointer)",
)
