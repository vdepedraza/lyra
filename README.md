# Lyra: a generative low bitrate speech codec

## What is Lyra?

[Lyra](https://ai.googleblog.com/2021/08/soundstream-end-to-end-neural-audio.html)
is a high-quality, low-bitrate speech codec that makes voice communication
available even on the slowest networks. To do this it applies traditional codec
techniques while leveraging advances in machine learning (ML) with models
trained on thousands of hours of data to create a novel method for compressing
and transmitting voice signals.

### Overview

The basic architecture of the Lyra codec is quite simple. Features are extracted
from speech every 20ms and are then compressed for transmission at a desired
bitrate between 3.2kbps and 9.2kbps. On the other end, a generative model uses
those features to recreate the speech signal.

Lyra harnesses the power of new natural-sounding generative models to maintain
the low bitrate of parametric codecs while achieving high quality, on par with
state-of-the-art waveform codecs used in most streaming and communication
platforms today.

Computational complexity is reduced by using a cheaper convolutional generative
model called SoundStream, which enables Lyra to not only run on cloud servers,
but also on-device on low-end phones in real time (with a processing latency of
20ms). This whole system is then trained end-to-end on thousands of hours of
speech data with speakers in over 90 languages and optimized to accurately
recreate the input audio.

Lyra is supported on Android, Linux, Mac and Windows.

# Compiling

## Prerequisites

1. Ubuntu
2. Docker
3. Android ndk (only for building arm)

## Install android ndk

from repository root:
* sudo apt install google-android-cmdline-tools-5.0-installer
* mkdir Android
* mkdir Android/Sdk
* sdkmanager --sdk_root=$PWD/Android/Sdk --install  "platforms;android-30" "build-tools;30.0.3" "ndk;21.4.7075529"

## Compile benchmark
docker run -it -v path_to_repository:/home/user/lyra bazel:5.3.2

within docker: `./android_build_benchmark.sh arm | arm64 | x86`

output will be on: bazel-bin/lyra/lyra_benchmark

# Original README

The original readme has been moved to README.md.old