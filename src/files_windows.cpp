#include "orb/files.hpp"
#include "orb/platform.hpp"

#include <filesystem>
#include <fstream>

namespace orb
{
    path::path(std::string path) : m_path(std::move(path))
    {
    }

    auto path::operator=(std::string_view str) -> path&
    {
        m_path = str;
        return *this;
    }

    auto path::exists() -> bool
    {
        return exists(m_path);
    }

    auto path::readable() -> bool
    {
        return readable(m_path);
    }

    auto path::executable() -> bool
    {
        return executable(m_path);
    }

    auto path::is_dir() -> bool
    {
        return is_dir(m_path);
    }

    auto path::is_file() -> bool
    {
        return is_file(m_path);
    }

    auto path::ls() -> result<std::vector<orb::path>>
    {
        return ls(m_path);
    }

    auto path::exists(std::string_view path) -> bool
    {
        return std::filesystem::exists(path);
    }

    auto path::readable(std::string_view path) -> bool
    {
        std::ifstream fs(path.data());
        return (bool)fs;
    }

    auto path::executable(std::string_view p) -> bool
    {
        const auto pos = p.find_last_of('/');
        const auto fname = pos == std::string::npos
            ? p
            : p.substr(pos + 1);

        const auto epos = fname.find_last_of('.');
        if (epos == std::string::npos)
        {
            return false;
        }

        return fname.substr(epos + 1) == "exe";
    }

    auto path::is_dir(std::string_view p) -> bool
    {
        return std::filesystem::is_directory(p);
    }

    auto path::is_file(std::string_view p) -> bool
    {
        return std::filesystem::is_regular_file(p);
    }

    auto path::ls(std::string_view p) -> result<std::vector<orb::path>>
    {
        if (!is_dir(p))
        {
            return error_t { "{} is not a directory", p };
        }

        std::vector<orb::path> res;
        for (const auto& entry : std::filesystem::directory_iterator(p))
        {
            res.emplace_back(entry.path().string());
        }

        return res;
    }

    void path::remove()
    {
        std::remove(m_path.data());
    }

    auto path::filename() const -> std::string_view
    {
        const auto pos = m_path.find_last_of(orb::path_separator);
        if (pos == std::string::npos)
        {
            return m_path;
        }

        return std::string_view { m_path }.substr(pos + 1);
    }

    auto path::basename() const -> std::string_view
    {
        const std::string_view fname = filename();

        const auto pos = fname.find_last_of('.');
        if (pos == std::string::npos)
        {
            return fname;
        }

        return fname.substr(0, pos);
    }

    auto path::extension() const -> std::string_view
    {
        const std::string_view fname = filename();

        const auto pos = fname.find_last_of('.');
        if (pos == std::string::npos)
        {
            return "";
        }

        return fname.substr(pos + 1);
    }

    auto path::parent() const -> std::string_view
    {
        const auto pos = m_path.find_last_of(orb::path_separator);
        if (pos == std::string::npos)
        {
            return m_path;
        }

        return std::string_view { m_path }.substr(0, pos);
    }

} // namespace orb
