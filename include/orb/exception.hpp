#pragma once

#include "orb/fmt/format.h"
#include <stdexcept>

namespace orb
{
    class exception : public std::runtime_error
    {
    public:
        exception() noexcept : std::runtime_error("Orbital excepton: Unknown orblib error")
        {
        }

        exception(std::string msg) noexcept : std::runtime_error(std::move(msg))
        {
        }

        template <typename... Args>
        exception(orb::format_string<Args...> fmt, Args&&... args) noexcept
            : std::runtime_error(orb::format(fmt, std::forward<Args>(args)...))
        {
        }
    };
} // namespace orb
