#pragma once

#include <fmt/base.h>
#include <string_view>

namespace orb
{
    namespace colors
    {
        inline constexpr std::string_view black   = "\u001b[30m";
        inline constexpr std::string_view red     = "\u001b[31m";
        inline constexpr std::string_view green   = "\u001b[32m";
        inline constexpr std::string_view yellow  = "\u001b[33m";
        inline constexpr std::string_view blue    = "\u001b[34m";
        inline constexpr std::string_view magenta = "\u001b[35m";
        inline constexpr std::string_view cyan    = "\u001b[36m";
        inline constexpr std::string_view white   = "\u001b[37m";
        inline constexpr std::string_view normal  = "\u001b[39m";
        inline constexpr std::string_view reset   = "\u001b[0m";

        namespace bg
        {
            inline constexpr std::string_view black   = "\u001b[40m";
            inline constexpr std::string_view red     = "\u001b[41m";
            inline constexpr std::string_view green   = "\u001b[42m";
            inline constexpr std::string_view yellow  = "\u001b[43m";
            inline constexpr std::string_view blue    = "\u001b[44m";
            inline constexpr std::string_view magenta = "\u001b[45m";
            inline constexpr std::string_view cyan    = "\u001b[46m";
            inline constexpr std::string_view white   = "\u001b[47m";
            inline constexpr std::string_view normal  = "\u001b[49m";
            inline constexpr std::string_view reset   = "\u001b[0m";
        } // namespace bg
    } // namespace colors

    template <typename... T>
    constexpr void println(FILE* f, fmt::format_string<T...> fmt, T&&... args)
    {
        const auto& vargs = fmt::make_format_args(std::forward<T>(args)...);
        return fmt::detail::use_utf8 ? vprintln(f, fmt, vargs)
                                     : fmt::detail::vprint_mojibake(f, fmt, vargs, true);
    }

    template <typename... T>
    constexpr void println(fmt::format_string<T...> fmt, T&&... args)
    {
        return fmt::println(stdout, fmt, std::forward<T>(args)...);
    }

} // namespace orb
