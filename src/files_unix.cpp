#include "orb/files.hpp"

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
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
        return access(path.data(), F_OK) == 0;
    }

    auto path::readable(std::string_view path) -> bool
    {
        return access(path.data(), R_OK) == 0;
    }

    auto path::executable(std::string_view path) -> bool
    {
        return access(path.data(), X_OK) == 0;
    }

    auto path::is_dir(std::string_view path) -> bool
    {
        return !is_file(path);
    }

    auto path::is_file(std::string_view path) -> bool
    {
        struct stat paths
        { };

        stat(path.data(), &paths);
        return S_ISREG(paths.st_mode);
    }

    auto path::ls(std::string_view path) -> result<std::vector<orb::path>>
    {
        if (!is_dir(path))
        {
            return error_t { "{} is not a directory", path };
        }

        std::vector<orb::path> res;

        struct dirent* dir {};
        DIR*           d {};

        d = opendir(path.data());

        if (d)
        {
            while ((dir = readdir(d)) != nullptr)
            {
                res.emplace_back(dir->d_name);
            }
            closedir(d);
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

        return std::string_view { fname }.substr(0, pos);
    }

    auto path::extension() const -> std::string_view
    {
        const std::string_view fname = filename();

        const auto pos = fname.find_last_of('.');
        if (pos == std::string::npos)
        {
            return "";
        }

        return std::string_view { m_path }.substr(pos + 1);
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
