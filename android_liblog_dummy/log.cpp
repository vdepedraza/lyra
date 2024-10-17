/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <cstdarg>  // For va_list
#include <cstdio>   // For vfprintf

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Writes the constant string `text` to the log, with priority `prio` and tag
 * `tag`.
 */
int __android_log_write(int prio, const char* tag, const char* text){
    std::cerr << "[Priority: " << prio << "] "
              << "[" << tag << "] "
              << text << std::endl;
              return 0;
}

int __android_log_print(int prio, const char* tag, const char* fmt, ...)
    {
    // Print priority and tag to stderr
    std::cerr << "[Priority: " << prio << "] [" << tag << "] ";

    // Handle variadic arguments for the formatted message
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);  // Print formatted message to stderr
    va_end(args);

    std::cerr << std::endl;  // Ensure the output ends with a newline
    return 0;
    }

/**
 * Equivalent to `__android_log_print`, but taking a `va_list`.
 * (If `__android_log_print` is like `printf`, this is like `vprintf`.)
 */
int __android_log_vprint(int prio, const char* tag, const char* fmt, va_list ap) {
        // Print priority and tag to stderr
    std::cerr << "[Priority: " << prio << "] [" << tag << "] ";

    // Print the formatted message using the va_list
    vfprintf(stderr, fmt, ap);

    // Add a newline to ensure output ends properly
    std::cerr << std::endl;
    return 0;
}


void __android_log_assert(const char* cond, const char* tag, const char* fmt,
                          ...){
    // Print priority and tag to stderr
    std::cerr << "ASSERT [" << tag << "] ";

    // Handle variadic arguments for the formatted message
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);  // Print formatted message to stderr
    va_end(args);

    std::cerr << std::endl;  // Ensure the output ends with a newline
                          }
}