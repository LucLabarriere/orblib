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

#ifdef ORB_WINDOWS
        using string_type_t = std::wstring;
        using string_view_type_t = std::wstring_view;
        using char_type_t = wchar_t;
#else
        using string_type_t = std::string;
        using string_view_type_t = std::string_view;
        using char_type_t = char;
#endif

        path()                = default;
        path(const path&)     = default;
        path(path&&) noexcept = default;
        ~path()               = default;

        path(string_type_t path);

        auto operator=(string_view_type_t str) -> path&;
        auto operator=(const path&) -> path&     = default;
        auto operator=(path&&) noexcept -> path& = default;

        auto exists() -> bool;
        auto readable() -> bool;
        auto executable() -> bool;
        auto is_dir() -> bool;
        auto is_file() -> bool;
        auto ls() -> result<std::vector<orb::path>>;
        void remove();

        [[nodiscard]] static auto exists(const char_type_t* path) -> bool;
        [[nodiscard]] static auto readable(const char_type_t* path) -> bool;
        [[nodiscard]] static auto executable(const char_type_t* path) -> bool;
        [[nodiscard]] static auto is_dir(const char_type_t* path) -> bool;
        [[nodiscard]] static auto is_file(const char_type_t* path) -> bool;
        [[nodiscard]] static auto ls(const char_type_t* path) -> result<std::vector<orb::path>>;

        [[nodiscard]] auto data() const -> const char_type_t*
        {
            return m_path.data();
        }

        [[nodiscard]] auto view() const -> string_view_type_t
        {
            return m_path;
        }

        [[nodiscard]] auto c_str() const -> const char_type_t*
        {
            return m_path.c_str();
        }

        [[nodiscard]] auto filename() const -> string_view_type_t;
        [[nodiscard]] auto basename() const -> string_view_type_t;
        [[nodiscard]] auto extension() const -> string_view_type_t;
        [[nodiscard]] auto parent() const -> string_view_type_t;

        auto operator+=(const path& rhs) -> path&
        {
            m_path += rhs.m_path;
            return *this;
        }

        auto operator+=(string_view_type_t rhs) -> path&
        {
            m_path += rhs;
            return *this;
        }

        auto operator+=(char_type_t rhs) -> path&
        {
            m_path += rhs;
            return *this;
        }

        friend auto operator+(path lhs, const path& rhs) -> path
        {
            lhs += rhs;
            return lhs;
        }

        friend auto operator+(path lhs, string_view_type_t rhs) -> path
        {
            lhs += rhs;
            return lhs;
        }

        friend auto operator+(path lhs, char_type_t rhs) -> path
        {
            lhs += rhs;
            return lhs;
        }

        [[nodiscard]] auto slash(string_view_type_t rhs) -> path
        {
            orb::path p = m_path;
            p += orb::path_separator;
            p += rhs;
            return p;
        }

        [[nodiscard]] auto read_file() const -> result<std::string>;

    private:
        string_type_t m_path;
    };
} // namespace orb
