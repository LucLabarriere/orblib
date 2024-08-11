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

        auto operator=(const path&) -> path&     = default;
        auto operator=(path&&) noexcept -> path& = default;

        auto                      exists() -> bool;
        [[nodiscard]] static auto exists(std::string_view path) -> bool;
        auto                      readable() -> bool;
        [[nodiscard]] static auto readable(std::string_view path) -> bool;
        auto                      writable() -> bool;
        [[nodiscard]] static auto writable(std::string_view path) -> bool;
        auto                      executable() -> bool;
        [[nodiscard]] static auto executable(std::string_view path) -> bool;
        auto                      is_dir() -> bool;
        [[nodiscard]] static auto is_dir(std::string_view path) -> bool;
        auto                      is_file() -> bool;
        [[nodiscard]] static auto is_file(std::string_view path) -> bool;
        auto                      ls() -> result<std::vector<orb::path>>;
        [[nodiscard]] static auto ls(std::string_view path) -> result<std::vector<orb::path>>;

        [[nodiscard]] auto data() const -> std::string_view
        {
            return m_path;
        }

    private:
        std::string m_path;
    };
} // namespace orb
