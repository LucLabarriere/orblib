#pragma once

#include <string_view>

namespace orb
{
#ifdef ORB_ASSERT
    static constexpr bool assert_mode = true;
#else
    static constexpr bool assert_mode = false;
#endif


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define ORB_WINDOWS
    static constexpr bool on_windows = true;
    static constexpr bool on_macos   = false;
    static constexpr bool on_linux   = false;
    static constexpr std::string_view dynlib_extension = "dll";
    static constexpr char path_separator = '\\';
#elif __APPLE__
#if TARGET_OS_MAC
#define ORB_MACOS
    static constexpr bool on_windows = false;
    static constexpr bool on_macos   = true;
    static constexpr bool on_linux   = false;
    static constexpr std::string_view dynlib_extension = "dylib";
    static constexpr char path_separator = '/';
#else
#error "Unknown Apple platform"
#endif
#elif __linux__
#define ORB_LINUX
    static constexpr bool on_windows = false;
    static constexpr bool on_macos   = false;
    static constexpr bool on_linux   = true;
    static constexpr std::string_view dynlib_extension = "so";
    static constexpr char path_separator = '/';
#else
#error "Unknown compiler"
#endif
} // namespace orb
