#pragma once

#include "orb/print.hpp"
#include "orb/utility.hpp"
#include "orb/exception.hpp"

#include <cstdlib>

namespace orb
{
    template <typename... T>
    [[noreturn]] void panic(fmt::format_string<T...> fmt, T&&... args)
    {
        orb::println(std::move(fmt), std::forward<T>(args)...);
        exit(1);
    }

#ifdef ORB_ASSERT
    template <typename... T>
    void assertion(bool condition, fmt::format_string<T...> fmt, const char* f, int l, T&&... args)
    {
        if (!condition)
        {
            orb::println("");
            orb::println("orblib: Assertion failed at: {}:{}", f, l);
            orb::panic(std::move(fmt), std::forward<T>(args)...);
        }
    }

    // clang-format off
#define ORB_ASSERT_2ARGS(c, f) orb::assertion(c, f, __FILE__, __LINE__)                                 // NOLINT
#define ORB_ASSERT_3ARGS(c, f, a1) orb::assertion(c, f, __FILE__, __LINE__, a1)                         // NOLINT
#define ORB_ASSERT_4ARGS(c, f, a1, a2) orb::assertion(c, f, __FILE__, __LINE__, a1, a2)                 // NOLINT
#define ORB_ASSERT_5ARGS(c, f, a1, a2, a3) orb::assertion(c, f, __FILE__, __LINE__, a1, a2, a3)         // NOLINT
#define ORB_ASSERT_6ARGS(c, f, a1, a2, a3, a4) orb::assertion(c, f, __FILE__, __LINE__, a1, a2, a3, a6) // NOLINT
    // clang-format on

#else

    // clang-format off
#define ORB_ASSERT_2ARGS(c, f)                 // NOLINT
#define ORB_ASSERT_3ARGS(c, f, a1)             // NOLINT
#define ORB_ASSERT_4ARGS(c, f, a1, a2)         // NOLINT
#define ORB_ASSERT_5ARGS(c, f, a1, a2, a3)     // NOLINT
#define ORB_ASSERT_6ARGS(c, f, a1, a2, a3, a4) // NOLINT
    // clang-format on

#endif
    // clang-format off
#define GET_ORB_ASSERT_MACRO(_c, _f, _a1, _a2, _a3, _a4, NAME, ...) NAME // NOLINT
#define orbassert(...) GET_ORB_ASSERT_MACRO(__VA_ARGS__, ORB_ASSERT_6ARGS, ORB_ASSERT_5ARGS, ORB_ASSERT_4ARGS, ORB_ASSERT_3ARGS, ORB_ASSERT_2ARGS)(__VA_ARGS__) // NOLINT
    // clang-format on

} // namespace orb
