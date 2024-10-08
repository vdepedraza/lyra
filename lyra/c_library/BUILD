package(default_visibility = ["//visibility:public"])

exports_files(
    srcs = [
        "clib_dec.cc",
        "clib_enc.cc",
        "clib_enc.h",
        "clib_dec.h",
    ],
)

cc_library(
    name = "clib_dec",
    srcs = [
        "clib_dec.cc",
    ],
    hdrs = [
        "clib_dec.h",
    ],
    deps = [
        "//lyra:lyra_config",
        "//lyra:lyra_encoder",
        "//lyra:lyra_decoder",
        "//lyra:no_op_preprocessor",
        "//lyra:wav_utils",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/time",
        "@com_google_absl//absl/types:span",
        "@com_google_glog//:glog",
        "@gulrak_filesystem//:filesystem",
    ],
    linkstatic = 1,
    visibility = ["//visibility:public"], 

)

cc_library(
    name = "clib_enc",
    srcs = [
        "clib_enc.cc",
    ],
    hdrs = [
        "clib_enc.h",
    ],
    deps = [
        "//lyra:lyra_config",
        "//lyra:lyra_encoder",
        "//lyra:lyra_decoder",
        "//lyra:no_op_preprocessor",
        "//lyra:wav_utils",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/time",
        "@com_google_absl//absl/types:span",
        "@com_google_glog//:glog",
        "@gulrak_filesystem//:filesystem",
    ],
    linkstatic = 1,
    visibility = ["//visibility:public"],
)