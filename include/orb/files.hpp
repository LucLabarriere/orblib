#pragma once

#include "orb/platform.hpp"
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
        auto executable() -> bool;
        auto is_dir() -> bool;
        auto is_file() -> bool;
        auto ls() -> result<std::vector<orb::path>>;
        void remove();

        [[nodiscard]] static auto exists(const char* path) -> bool;
        [[nodiscard]] static auto readable(const char* path) -> bool;
        [[nodiscard]] static auto executable(const char* path) -> bool;
        [[nodiscard]] static auto is_dir(const char* path) -> bool;
        [[nodiscard]] static auto is_file(const char* path) -> bool;
        [[nodiscard]] static auto ls(const char* path) -> result<std::vector<orb::path>>;

        [[nodiscard]] auto data() const -> const char*
        {
            return m_path.data();
        }

        [[nodiscard]] auto view() const -> std::string_view
        {
            return m_path;
        }

        [[nodiscard]] auto c_str() const -> const char*
        {
            return m_path.c_str();
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

        auto operator+=(char rhs) -> path&
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

        friend auto operator+(path lhs, char rhs) -> path
        {
            lhs += rhs;
            return lhs;
        }

        [[nodiscard]] auto slash(std::string_view rhs) -> path
        {
            orb::path p = m_path;
            p += orb::path_separator;
            p += rhs;
            return p;
        }

        [[nodiscard]] auto read_file() const -> result<std::string>;

    private:
        std::string m_path;
    };
} // namespace orb
