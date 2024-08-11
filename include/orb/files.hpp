#pragma once

#include "orb/result.hpp"
#include <string>
#include <vector>

namespace orb
{
    class path
    {
    public:
        path()                = default;
        path(const path&)     = default;
        path(path&&) noexcept = default;
        ~path()               = default;

        path(std::string path);

        auto operator=(std::string_view str) -> path&;
        auto operator=(const path&) -> path&     = default;
        auto operator=(path&&) noexcept -> path& = default;

        auto exists() -> bool;
        auto readable() -> bool;
        auto writable() -> bool;
        auto executable() -> bool;
        auto is_dir() -> bool;
        auto is_file() -> bool;
        auto ls() -> result<std::vector<orb::path>>;
        void remove();

        [[nodiscard]] static auto exists(std::string_view path) -> bool;
        [[nodiscard]] static auto readable(std::string_view path) -> bool;
        [[nodiscard]] static auto writable(std::string_view path) -> bool;
        [[nodiscard]] static auto executable(std::string_view path) -> bool;
        [[nodiscard]] static auto is_dir(std::string_view path) -> bool;
        [[nodiscard]] static auto is_file(std::string_view path) -> bool;
        [[nodiscard]] static auto ls(std::string_view path) -> result<std::vector<orb::path>>;

        [[nodiscard]] auto data() const -> std::string_view
        {
            return m_path;
        }

        [[nodiscard]] auto filename() const -> std::string_view;
        [[nodiscard]] auto basename() const -> std::string_view;
        [[nodiscard]] auto extension() const -> std::string_view;
        [[nodiscard]] auto parent() const -> std::string_view;

        auto operator+=(const path& rhs) -> path&
        {
            m_path += rhs.m_path;
            return *this;
        }

        auto operator+=(std::string_view rhs) -> path&
        {
            m_path += rhs;
            return *this;
        }

        friend auto operator+(path lhs, const path& rhs) -> path
        {
            lhs += rhs;
            return lhs;
        }

        friend auto operator+(path lhs, std::string_view rhs) -> path
        {
            lhs += rhs;
            return lhs;
        }

    private:
        std::string m_path;
    };
} // namespace orb
