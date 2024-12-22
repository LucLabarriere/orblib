#pragma once

#include "utility.hpp"

namespace orb
{
    template <typename T>
    class weak
    {
    public:
        weak(const weak&)                        = default;
        weak(weak&&) noexcept                    = default;
        auto operator=(const weak&) -> weak&     = default;
        auto operator=(weak&&) noexcept -> weak& = default;

        weak()  = default;
        ~weak() = default;

        constexpr weak(T* ptr) : m_ptr(ptr)
        {
        }

        auto raw() const -> T*
        {
            return m_ptr;
        }

        [[nodiscard]] auto is_valid() const -> bool
        {
            return (bool)m_ptr;
        }

        [[nodiscard]] auto operator*() -> T&
        {
            return *m_ptr;
        }

        [[nodiscard]] auto operator->() -> T*
        {
            return m_ptr;
        }

    private:
        T* m_ptr { nullptr };
    };

    template <typename T>
    class box
    {
    public:
        box()                              = default;
        box(const box&)                    = delete;
        auto operator=(const box&) -> box& = delete;

        box(T* ptr) : m_ptr(ptr)
        {
        }

        box(box&& other) noexcept : m_ptr(other.release())
        {
        }

        auto operator=(box&& other) noexcept -> box&
        {
            m_ptr = other.release();
            return *this;
        }

        ~box()
        {
            delete m_ptr;
            m_ptr = nullptr;
        }

        auto release() -> T*
        {
            T* ptr = m_ptr;
            m_ptr  = nullptr;
            return ptr;
        }

        void reset()
        {
            delete m_ptr;
            m_ptr = nullptr;
        }

        void reset(T* ptr)
        {
            delete m_ptr;
            m_ptr = ptr;
        }

        [[nodiscard]] auto getmut() -> weak<T>
        {
            return weak<T> { m_ptr };
        }

        [[nodiscard]] auto get() const -> weak<const T>
        {
            return weak<const T> { m_ptr };
        }

        [[nodiscard]] auto operator*() -> T&
        {
            return *m_ptr;
        }

        [[nodiscard]] auto operator*() const -> const T&
        {
            return *m_ptr;
        }

        [[nodiscard]] auto operator->() -> T*
        {
            return m_ptr;
        }

        [[nodiscard]] auto operator->() const -> const T*
        {
            return m_ptr;
        }

    private:
        T* m_ptr = nullptr;
    };

    template <typename T, typename... Args>
    [[nodiscard]] auto make_box(Args&&... args) -> box<T>
    {
        T* ptr = new T(orb::forward<Args>(args)...);
        return box(ptr);
    }

} // namespace orb
