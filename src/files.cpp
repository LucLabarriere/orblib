#include "orb/files.hpp"

// TODO Test on windows

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#else
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

namespace orb
{
    path::path(std::string path) : m_path(std::move(path))
    {
    }

    auto path::exists() -> bool
    {
        return exists(m_path);
    }

    auto path::exists(std::string_view path) -> bool
    {
        return access(path.data(), F_OK) == 0;
    }

    auto path::readable() -> bool
    {
        return readable(m_path);
    }

    auto path::readable(std::string_view path) -> bool
    {
        return access(path.data(), R_OK) == 0;
    }

    auto path::writable() -> bool
    {
        return writable(m_path);
    }

    auto path::writable(std::string_view path) -> bool
    {
        return access(path.data(), W_OK) == 0;
    }

    auto path::executable() -> bool
    {
        return executable(m_path);
    }

    auto path::executable(std::string_view path) -> bool
    {
        return access(path.data(), X_OK) == 0;
    }

    auto path::is_dir() -> bool
    {
        return is_dir(m_path);
    }

    auto path::is_dir(std::string_view path) -> bool
    {
        return !is_file(path);
    }

    auto path::is_file() -> bool
    {
        return is_file(m_path);
    }

    auto path::is_file(std::string_view path) -> bool
    {
        struct stat paths
        { };

        stat(path.data(), &paths);
        return S_ISREG(paths.st_mode);
    }

    auto path::ls() -> result<std::vector<orb::path>>
    {
        return ls(m_path);
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
} // namespace orb
