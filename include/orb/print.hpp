#pragma once

#include "fmt/base.h"

namespace orb::colors
{
    inline constexpr string_view black   = "\u001b[30m";
    inline constexpr string_view red     = "\u001b[31m";
    inline constexpr string_view green   = "\u001b[32m";
    inline constexpr string_view yellow  = "\u001b[33m";
    inline constexpr string_view blue    = "\u001b[34m";
    inline constexpr string_view magenta = "\u001b[35m";
    inline constexpr string_view cyan    = "\u001b[36m";
    inline constexpr string_view white   = "\u001b[37m";
    inline constexpr string_view normal  = "\u001b[39m";
    inline constexpr string_view reset   = "\u001b[0m";

    namespace bg
    {
        inline constexpr string_view black   = "\u001b[40m";
        inline constexpr string_view red     = "\u001b[41m";
        inline constexpr string_view green   = "\u001b[42m";
        inline constexpr string_view yellow  = "\u001b[43m";
        inline constexpr string_view blue    = "\u001b[44m";
        inline constexpr string_view magenta = "\u001b[45m";
        inline constexpr string_view cyan    = "\u001b[46m";
        inline constexpr string_view white   = "\u001b[47m";
        inline constexpr string_view normal  = "\u001b[49m";
        inline constexpr string_view reset   = "\u001b[0m";
    } // namespace bg
} // namespace orb::colors
