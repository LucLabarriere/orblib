#pragma once

#include "orb/files.hpp"
#include "orb/platform.hpp"

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

        void open(const orb::path& p);
        void close();
        auto get_err() -> std::string_view;

        [[nodiscard]] auto get_func(std::string_view fn_name) -> fn_handle;

        template <typename TFunc>
        [[nodiscard]] auto get_func(TFunc*, std::string_view fn_name) -> TFunc*
        {
            return reinterpret_cast<TFunc*>(get_func(fn_name)); // NOLINT
        }

        [[nodiscard]] auto is_valid() -> bool
        {
            return m_handle != nullptr;
        };

        static constexpr auto get_libfile_path(const orb::path& p) -> orb::path
        {
            if (p.extension() == "")
            {
                std::string path(p.data());
                path += ".";
                path += orb::dynlib_extension;
                return { std::move(path) };
            }

            return p;
        }

    private:
        lib_handle  m_handle { nullptr };
        std::string m_last_info = "";
    };
} // namespace orb
