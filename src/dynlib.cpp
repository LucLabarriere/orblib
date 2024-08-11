#include "orb/dynlib.hpp"

#include <cstdlib>
#include <dlfcn.h>

// TODO Implement for windows

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

    void dynlib::open(std::string_view path)
    {
        m_handle = dlopen(path.data(), RTLD_LAZY);
    }

    void dynlib::close()
    {
        dlclose(m_handle);
        m_handle = nullptr;
    }

    auto dynlib::get_func(std::string_view fn_name) -> fn_handle
    {
        return dlsym(m_handle, fn_name.data());
    }

    auto dynlib::get_err() -> std::string_view
    {
        return dlerror();
    }
} // namespace orb
