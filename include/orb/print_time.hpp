#pragma once

#include <orb/fmt/base.h>
#include <orb/fmt/format.h>
#include <orb/time.hpp>

namespace orb
{
    template <watch_type TWatch = stopwatch>
    static inline timepoint<TWatch> _global_timepoint {};

    template <watch_type TWatch = stopwatch>
    inline void begin_chrono()
    {
        _global_timepoint<TWatch> = TWatch::now();
    }

    template <watch_type TWatch = stopwatch, ratio_type TRatio = ms_t>
    inline void print_chrono(orb::format_string<duration<TRatio>> fmt)
    {
        orb::println(fmt, _global_timepoint<TWatch>.template elapsed_time<TRatio>());
    }
} // namespace orb
