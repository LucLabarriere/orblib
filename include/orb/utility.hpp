
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
} // namespace orb
