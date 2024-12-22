#pragma once

#include <concepts>

namespace orb
{

    class eval_t
    {
    public:
        constexpr auto operator|(std::invocable auto func) const
        {
            return std::invoke(func);
        }
    };

    constexpr eval_t eval;

} // namespace orb
