#!/bin/bash

# Set the workspace path
WORKSPACE=$(bazel info workspace)

# Function to display usage
usage() {
  echo "Usage: $0 [arm | arm64]"
  echo "  arm   : Build for armeabi-v7a"
  echo "  arm64 : Build for arm64-v8a"
  exit 1
}

# Check if a parameter is provided
if [ -z "$1" ]; then
  usage
fi

# Select configuration based on the parameter
case "$1" in
  arm)
    ARCH="armeabi-v7a"
    CONFIG="android_arm32"
    ;;
  arm64)
    ARCH="arm64-v8a"
    CONFIG="android_arm64"
    ;;
  *)
    usage
    ;;
esac

# remove libandroid_support
# https://github.com/bazelbuild/bazel/issues/12840
rm $WORKSPACE/Android/Sdk/ndk/21.4.7075529/sources/cxx-stl/llvm-libc++/libs/armeabi-v7a/libandroid_support.a

# Run Bazel build command with appropriate options
bazel build -c opt lyra:lyra_benchmark \
  --copt=-DBENCHMARK \
  --config="$CONFIG" \
  --linkopt="-L${WORKSPACE}/android_liblog_dummy/lib/${ARCH}" \

echo "Build completed for $ARCH"