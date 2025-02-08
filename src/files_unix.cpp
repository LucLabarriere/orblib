#include "orb/files.hpp"

#include <array>
#include <dirent.h>
#include <fcntl.h>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

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
        return exists(m_path.c_str());
    }

    auto path::readable() -> bool
    {
        return readable(m_path.c_str());
    }

    auto path::executable() -> bool
    {
        return executable(m_path.c_str());
    }

    auto path::is_dir() -> bool
    {
        return is_dir(m_path.c_str());
    }

    auto path::is_file() -> bool
    {
        return is_file(m_path.c_str());
    }

    auto path::ls() -> result<std::vector<orb::path>>
    {
        return ls(m_path.c_str());
    }

    auto path::exists(const char* path) -> bool
    {
        return access(path, F_OK) == 0;
    }

    auto path::readable(const char* path) -> bool
    {
        return access(path, R_OK) == 0;
    }

    auto path::executable(const char* path) -> bool
    {
        return access(path, X_OK) == 0;
    }

    auto path::is_dir(const char* path) -> bool
    {
        return !is_file(path);
    }

    auto path::is_file(const char* path) -> bool
    {
        struct stat paths {};

        stat(path, &paths);
        return S_ISREG(paths.st_mode);
    }

    auto path::ls(const char* path) -> result<std::vector<orb::path>>
    {
        if (!is_dir(path))
        {
            return error_t { "{} is not a directory", path };
        }

        std::vector<orb::path> res;

        struct dirent* dir {};
        DIR*           d {};

        d = opendir(path);

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

    auto path::read_file() const -> result<std::string>
    {
        const int fd = open(m_path.c_str(), O_RDONLY);

        if (fd == -1)
        {
            return error_t { "{} does not exist", m_path };
        }

        std::array<char, 1024> buffer {};

        ssize_t total_read = -1;
        ssize_t read       = 0;

        std::string content;

        while (read != 0)
        {
            read = ::read(fd, buffer.data(), buffer.size());

            if (read < 0)
            {
                return error_t { "Could not read {}", m_path };
            }

            content += std::string_view { buffer.data(), (size_t)read };
        }

        return {};
    }

} // namespace orb
