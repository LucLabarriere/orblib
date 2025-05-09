#include "orb/dynlib.hpp"
#include "orb/platform.hpp"

#include <cstdlib>
#include <windows.h>

namespace orb
{
    dynlib::dynlib(dynlib&& other) noexcept : m_handle(other.m_handle)
    {
        other.m_handle = nullptr;
    }

    dynlib::~dynlib()
    {
        if (m_handle)
        {
            close();
        }
    }

    void dynlib::open(const orb::path& p)
    {
        if (p.extension() == "")
        {
            std::string path(p.data());
            path += "/";
            path += orb::dynlib_extension;

            m_handle = (lib_handle)LoadLibrary(path.c_str());
        }
        else
        {
            m_handle = (lib_handle)LoadLibrary(p.c_str());
        }
    }

    void dynlib::close()
    {
        FreeLibrary(static_cast<HMODULE>(m_handle));
        m_handle = nullptr;
    }

    auto dynlib::get_func(const char* fn_name) -> fn_void_handle
    {
        return (fn_void_handle)GetProcAddress(static_cast<HMODULE>(m_handle), fn_name);
    }

    auto dynlib::get_err() -> std::string
    {
        const auto err = GetLastError();

        switch (GetLastError())
        {
        case ERROR_MOD_NOT_FOUND:
        {
            return fmt::format("DLL error {}. Module not found", err);
        }

        case ERROR_BAD_EXE_FORMAT:
        {
            return fmt::format("DLL error {}. Bad executable format (32/64 bit mismatch)", err);
        }

        case ERROR_PROC_NOT_FOUND:
        {
            return fmt::format("DLL error {}. Function could not be found", err);
        }

        default:
        {
            return fmt::format("Unknown error {}", err);
        }
        }
    }

    auto dynlib::get_libfile_path(const orb::path& p) -> orb::path
    {
        if (p.extension() == "")
        {
            std::string path(p.view());
            path += ".";
            path += orb::dynlib_extension;
            return { std::move(path) };
        }

        return p;
    }
} // namespace orb
