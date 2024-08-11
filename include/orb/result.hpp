#pragma once

#include "orb/fmt/format.h"
#include "orb/print.hpp"

#include <optional>
#include <variant>
#include <string>

namespace orb
{
    class error_t
    {
    public:
        constexpr error_t() noexcept = default;
        constexpr error_t(std::string message) noexcept : m_message(std::move(message))
        {
        }

        template <typename... Args>
        constexpr error_t(orb::format_string<Args...> fmt, Args&&... args) noexcept
            : m_message(orb::format(fmt, std::forward<Args>(args)...))
        {
        }
        constexpr error_t(const error_t&)         = delete;
        constexpr error_t(error_t&& err) noexcept = default;
        constexpr ~error_t() noexcept           = default;

        auto operator=(const error_t&) -> error_t& = delete;
        auto operator=(error_t&&) -> error_t&      = delete;

        [[nodiscard]] constexpr auto get_message() const -> const std::string&
        {
            return m_message;
        }

    private:
        std::string m_message { "Unknown error" };
    };

    template <typename T>
    class result
    {
    public:
        constexpr result(error_t&& err) noexcept
            : m_variant(std::forward<error_t>(std::move(err)))
        {
        }
        constexpr result(T&& v) noexcept : m_variant(std::forward<T>(std::move(v)))
        {
        }
        template <typename... Args>
        constexpr result(Args&&... args) noexcept : m_variant(T(std::forward<T>(args)...))
        {
        }
        constexpr result(const result&)     = delete;
        constexpr result(result&&) noexcept = default;
        constexpr ~result() noexcept        = default;

        auto operator=(const result&) -> result& = delete;
        auto operator=(result&&) -> result&      = delete;

        [[nodiscard]] constexpr auto value() noexcept -> T
        {
            return std::move(std::get<T>(m_variant));
        }

        [[nodiscard]] constexpr auto error() noexcept -> error_t
        {
            return std::move(std::get<error_t>(m_variant));
        }

        [[nodiscard]] constexpr auto is_error() const noexcept -> bool
        {
            return m_variant.index() == 0;
        }

        [[nodiscard]] constexpr auto is_value() const noexcept -> bool
        {
            return m_variant.index() == 1;
        }

        constexpr void throw_if_error() const
        {
            if (m_variant.index() == 0)
            {
                throw;
            }
        }

        operator bool() const
        {
            return is_value();
        }

    private:
        std::variant<error_t, T> m_variant;
    };

    template <>
    class result<void>
    {
    public:
        constexpr result() noexcept = default;
        constexpr result(error_t&& err) noexcept
            : m_error(std::forward<error_t>(std::move(err)))
        {
        }
        constexpr result(const result&)     = delete;
        constexpr result(result&&) noexcept = default;
        constexpr ~result() noexcept        = default;

        auto operator=(const result&) -> result& = delete;
        auto operator=(result&&) -> result&      = delete;

        [[nodiscard]] constexpr auto error() noexcept -> error_t
        {
            // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
            return std::move(m_error.value());
        }

        [[nodiscard]] constexpr auto is_error() const noexcept -> bool
        {
            return m_error.has_value();
        }

        operator bool() const
        {
            return !is_error();
        }

        constexpr void throw_if_error() const
        {
            if (m_error.has_value())
            {
                throw;
            }
        }

    private:
        std::optional<error_t> m_error;
    };
} // namespace orb
