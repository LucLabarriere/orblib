#pragma once

#include <chrono>

namespace orb
{
    template <typename T>
    concept clock_std_type = requires(T t) {
        { t.now() } -> std::same_as<std::chrono::time_point<T>>;
    };

    using s_t  = std::ratio<1, 1>;
    using ms_t = std::milli;
    using us_t = std::micro;
    using ns_t = std::nano;

    template <typename T>
    concept ratio_type = requires {
        std::same_as<T, s_t> || std::same_as<T, ms_t> || std::same_as<T, us_t> || std::same_as<T, ns_t>;
    };

    static_assert(ratio_type<s_t>);
    static_assert(ratio_type<ms_t>);
    static_assert(ratio_type<us_t>);
    static_assert(ratio_type<ns_t>);

    template <ratio_type TRatio>
    using duration_std_t = std::chrono::duration<float, TRatio>;

    template <clock_std_type TClock>
    class watch;

    using sys_watch     = watch<std::chrono::system_clock>;
    using precise_watch = watch<std::chrono::high_resolution_clock>;
    using stopwatch     = watch<std::chrono::steady_clock>;

    template <typename T>
    concept watch_type = requires {
        std::same_as<T, sys_watch> || std::same_as<T, precise_watch> || std::same_as<T, stopwatch>;
    };

    template <ratio_type TRatio>
    class duration : public std::chrono::duration<float, TRatio>
    {
    public:
        static consteval auto unit() -> std::string_view
        {
            if constexpr (std::same_as<TRatio, s_t>)
            {
                return "s";
            }
            else if constexpr (std::same_as<TRatio, ms_t>)
            {
                return "ms";
            }
            else if constexpr (std::same_as<TRatio, us_t>)
            {
                return "us";
            }
            else if constexpr (std::same_as<TRatio, ns_t>)
            {
                return "ns";
            }
            else
            {
                return "";
            }
        }
    };

    template <ratio_type TRatio>
    class orb::formatter<duration<TRatio>>
    {
    public:
        constexpr auto parse(format_parse_context& ctx)
        {
            return ctx.begin();
        }

        template <typename Context>
        constexpr auto format(const duration<TRatio>& dur, Context& ctx) const
        {
            return format_to(ctx.out(), "{} {}", dur.count(), dur.unit());
        }
    };

    template <watch_type TWatch>
    class timepoint : public std::chrono::time_point<typename TWatch::clock_t>
    {
    public:
        using std_type = std::chrono::time_point<typename TWatch::clock_t>;
        using watch_t  = TWatch;

        timepoint()                                    = default;
        timepoint(timepoint&&)                         = default;
        timepoint(const timepoint&)                    = default;
        auto operator=(const timepoint&) -> timepoint& = default;
        auto operator=(timepoint&&) -> timepoint&      = default;
        ~timepoint()                                   = default;

        timepoint(std_type&& other) : std_type(std::move(other))
        {
        }
        timepoint(const std_type& other) : std_type(other)
        {
        }
        auto operator=(const std_type& other) -> timepoint&
        {
            if (this == &other)
            {
                return *this;
            }
            std_type::operator=(other);
            return *this;
        }
        auto operator=(std_type&& other) -> timepoint&
        {
            if (this == &other)
            {
                return *this;
            }
            std_type::operator=(std::move(other));
            return *this;
        }

        template <ratio_type TRatio = ms_t>
        auto elapsed_time() -> duration<TRatio>
        {
            return watch_t::template dur<TRatio>(*this, watch_t::now());
        }
    };

    template <typename T>
    concept timepoint_type = requires {
        std::same_as<T, timepoint<sys_watch>> || std::same_as<T, timepoint<sys_watch>>
            || std::same_as<T, timepoint<stopwatch>>;
    };

    using seconds_t      = std::chrono::duration<float, std::ratio<1, 1>>;
    using milliseconds_t = std::chrono::duration<float, std::milli>;
    using microseconds_t = std::chrono::duration<float, std::micro>;
    using nanoseconds_t  = std::chrono::duration<float, std::nano>;

    template <clock_std_type TClock>
    class watch
    {
    public:
        using clock_t = TClock;

        template <ratio_type TRatio>
        static inline auto dur(timepoint<watch> t0, timepoint<watch> t1) -> duration<TRatio>
        {
            return duration<TRatio> { std::chrono::duration_cast<duration_std_t<TRatio>>(t1 - t0) };
        }

        template <ratio_type TRatio>
        static inline auto elapsed_time_since(timepoint<watch> t0) -> duration<TRatio>
        {
            return dur<TRatio>(t0, clock_t::now());
        }

        static inline auto now() -> timepoint<watch>
        {
            return timepoint<watch> { clock_t::now() };
        }

    private:
    };

    static_assert(watch_type<sys_watch>);
    static_assert(watch_type<precise_watch>);
    static_assert(watch_type<stopwatch>);
} // namespace orb
