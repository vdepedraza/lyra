package(default_visibility = ["//visibility:public"])

exports_files(
    srcs = [
        "c_dec.cc",
        "c_enc.cc",
        "c_enc.h",
        "c_dec.h",
    ],
)

cc_library(
    name = "c_dec",
    srcs = [
        "c_dec.cc",
    ],
    hdrs = [
        "c_dec.h",
    ],
    deps = [
        "//lyra:lyra_decoder",
    ]
)

cc_static_library(
    name = "c_dec_static",
    deps = [
        ":c_dec",
    ]
)

cc_library(
    name = "c_enc",
    srcs = [
        "c_enc.cc",
    ],
    hdrs = [
        "c_enc.h",
    ],
    deps = [
        "//lyra:lyra_encoder",
    ]
)

cc_static_library(
    name = "c_enc_static",
    deps = [
        ":c_enc",
    ]
)

load("@rules_pkg//pkg:tar.bzl", "pkg_tar")

pkg_tar(
    name = "lib_package",
    srcs = [":c_dec_static",
            ":c_enc_static"],
    deps = [
        # "//lyra:headers",
        # "//lyra:external_libs",
        ":lib_headers",
    ],
)

pkg_tar(
    name = "lib_headers",
    srcs = glob(["c_dec.h",
                 "c_enc.h"]),
    strip_prefix = "include",
    package_dir = "include",
)

pkg_tar(
    name = "external_libs",
    srcs = [
        "//lyra/c_library:c_dec",
        "//lyra:lyra_decoder",
        "//lyra:lyra_config",
        "//lyra:buffered_resampler",
        "//lyra:lyra_components",
        "//lyra:residual_vector_quantizer",
        "//lyra:comfort_noise_generator",
        "@com_google_glog//:glog",
        "//lyra:lyra_gan_model",
        "//lyra:log_mel_spectrogram_extractor_impl",
        "//lyra:tflite_model_wrapper",
        "@com_google_audio_dsp//audio/dsp:number_util",
        "@com_google_audio_dsp//audio/dsp/mfcc",
        "@com_google_audio_dsp//audio/dsp/spectrogram",
        "@com_google_audio_dsp//audio/dsp:signal_vector_util",
        "@com_google_audio_dsp//audio/dsp:resampler_q",
        "@com_google_absl//absl/flags:marshalling",
        "@com_google_absl//absl/random",
        "@com_google_absl//absl/random:bit_gen_ref",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/time",
        "@com_google_absl//absl/types:span",
        "//lyra:resampler",        



    ],
    package_dir = "ext",
)