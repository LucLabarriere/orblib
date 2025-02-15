#pragma once

#include "orb/files.hpp"
#include "orb/platform.hpp"

namespace orb
{
    class dynlib
    {
    public:
        using fn_void_handle = void*;
        using lib_handle     = void*;

        dynlib(const dynlib&)                    = delete;
        auto operator=(const dynlib&) -> dynlib& = delete;

        dynlib() = default;
        dynlib(dynlib&&) noexcept;
        ~dynlib();

        auto operator=(dynlib&&) noexcept -> dynlib&;

        void open(const orb::path& p);
        void close();
        auto get_err() -> std::string;

        [[nodiscard]] auto get_func(const char* fn_name) -> fn_void_handle;

        template <typename FuncPointer>
        [[nodiscard]] auto get_func(const char* fn_name) -> FuncPointer
        {
            return reinterpret_cast<FuncPointer>(get_func(fn_name)); // NOLINT
        }

        [[nodiscard]] auto is_valid() -> bool
        {
            return m_handle != nullptr;
        };

        static auto get_libfile_path(const orb::path& p) -> orb::path;

    private:
        lib_handle  m_handle { nullptr };
    };
} // namespace orb
