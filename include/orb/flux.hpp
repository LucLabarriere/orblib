#pragma once

#include "flux_raw.hpp"

namespace flux
{
    template <const_iterable_sequence Seq>
        requires(!flux::detail::is_ref_adaptor<Seq>)
    [[nodiscard]] constexpr inline auto enumerate(Seq&& seq)
    {
        return flux::zip(flux::ref(seq).cursors(), flux::ref(seq));
    }

} // namespace flux
