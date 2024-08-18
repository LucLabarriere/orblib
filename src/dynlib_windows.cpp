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
            m_last_info = path.data();

            m_handle = (lib_handle)LoadLibrary(path.data());
        }
        else
        {
            m_last_info = p.data();
            m_handle    = (lib_handle)LoadLibrary(p.data().data());
        }
    }

    void dynlib::close()
    {
        FreeLibrary(static_cast<HMODULE>(m_handle));
        m_handle = nullptr;
    }

    auto dynlib::get_func(std::string_view fn_name) -> fn_void_handle
    {
        m_last_info = fn_name;
        return (fn_void_handle)GetProcAddress(static_cast<HMODULE>(m_handle), fn_name.data());
    }

    auto dynlib::get_err() -> std::string_view
    {
        const auto err = GetLastError();

        switch (GetLastError())
        {
        case ERROR_MOD_NOT_FOUND:
        {
            static std::string e =
                orb::format("DLL error {}. Module not found. Last param used: {}", err, m_last_info);
            return e;
        }

        case ERROR_BAD_EXE_FORMAT:
        {
            static std::string e =
                orb::format("DLL error {}. Bad executable format (32/64 bit mismatch). Last param used: {}",
                            err,
                            m_last_info);
            return e;
        }

        case ERROR_PROC_NOT_FOUND:
        {
            static std::string e =
                orb::format("DLL error {}. Function could not be found. Last param used: {}",
                            err,
                            m_last_info);
            return e;
        }

        default:
        {
            static std::string e = orb::format("Unknown error {}. Last param used: {}", err, m_last_info);
            return e;
        }
        }
    }
} // namespace orb
