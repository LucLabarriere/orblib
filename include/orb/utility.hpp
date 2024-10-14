#pragma once

#include <cstdint>
#include <type_traits>

namespace orb
{
    template <class T>
    [[nodiscard]] inline constexpr auto forward(std::remove_reference_t<T>& t) noexcept -> T&&
    {
        return static_cast<T&&>(t);
    }

    template <class T>
    [[nodiscard]] inline constexpr auto forward(std::remove_reference_t<T>&& t) noexcept -> T&&
    {
        static_assert(!std::is_lvalue_reference<T>::value, "cannot forward an rvalue as an lvalue");
        return static_cast<T&&>(t);
    }

    template <class T>
    [[nodiscard]] inline constexpr auto move(T&& t) noexcept -> std::remove_reference_t<T>&&
    {
        using Up = std::remove_reference_t<T>;
        return static_cast<Up&&>(t);
    }

    template <class T>
    using move_if_noexcept_result_t = std::conditional_t<!std::is_nothrow_move_constructible<T>::value
                                                             && std::is_copy_constructible<T>::value,
                                                         const T&,
                                                         T&&>;

    template <class T>
    [[nodiscard]] inline constexpr auto move_if_noexcept(T& x) noexcept -> move_if_noexcept_result_t<T>
    {
        return move(x);
    }

    using i8   = int8_t;
    using i16  = int16_t;
    using i32  = int32_t;
    using i64  = int64_t;
    using ui8  = uint8_t;
    using ui16 = uint16_t;
    using ui32 = uint32_t;
    using ui64 = uint64_t;
    using f32  = float;
} // namespace orb
