#pragma once

#include <string_view>

namespace orb
{
    class dynlib
    {
    public:
        using fn_handle  = void*;
        using lib_handle = void*;

        dynlib(const dynlib&)                    = delete;
        auto operator=(const dynlib&) -> dynlib& = delete;

        dynlib() = default;
        dynlib(dynlib&&) noexcept;
        ~dynlib();

        auto operator=(dynlib&&) noexcept -> dynlib&;

        void open(std::string_view path);
        void close();
        auto get_func(std::string_view fn_name) -> fn_handle;
        auto get_err() -> std::string_view;

    private:
        lib_handle m_handle { nullptr };
    };
} // namespace orb
