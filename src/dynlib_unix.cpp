#include "orb/dynlib.hpp"

#include <cstdlib>
#include <dlfcn.h>

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
            m_handle = dlopen(path.c_str(), RTLD_LAZY);
        }
        else
        {
            m_handle = dlopen(p.c_str(), RTLD_LAZY);
        }
    }

    void dynlib::close()
    {
        dlclose(m_handle);
        m_handle = nullptr;
    }

    auto dynlib::get_func(const char* fn_name) -> fn_void_handle
    {
        return dlsym(m_handle, fn_name);
    }

    auto dynlib::get_err() -> std::string_view
    {
        static std::string e = orb::format("Dynlib error {}. Last param used: {}", dlerror(), m_last_info);
        return e;
    }

    auto dynlib::get_libfile_path(const orb::path& p) -> orb::path
    {
        if (p.extension() == "")
        {
            std::string path(p.view());
            path += ".";
            path += orb::dynlib_extension;
            return std::move(path);
        }

        return p;
    }
} // namespace orb
