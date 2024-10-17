#!/bin/bash

# Build library for all 4 architectures
REPO_PATH=$(git rev-parse --show-toplevel)
NDK=$REPO_PATH/Android/Sdk/ndk/21.4.7075529

## supported abis: arm64-v8a armeabi-v7a x86 x86_64


# arm64-v8a
mkdir build
cd build 

cmake .. -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-30
make
cp liblog.a ../lib/arm64-v8a/
cd ..
rm -rf build

# armeabi-v7a
mkdir build
cd build 

cmake .. -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake -DANDROID_ABI=armeabi-v7a -DANDROID_PLATFORM=android-30
make
cp liblog.a ../lib/armeabi-v7a/
cd ..
rm -rf build

# x86
mkdir build
cd build 

cmake .. -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake -DANDROID_ABI=x86 -DANDROID_PLATFORM=android-30
make
cp liblog.a ../lib/x86/
cd ..
rm -rf build

# x86
mkdir build
cd build 

# x86_64
cmake .. -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake -DANDROID_ABI=x86_64 -DANDROID_PLATFORM=android-30
make
cp liblog.a ../lib/x86_64/
cd ..
rm -rf build