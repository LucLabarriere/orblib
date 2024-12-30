#pragma once

#include "flux_raw.hpp"

namespace flux
{
    template <const_iterable_sequence Seq>
        requires(!flux::detail::is_ref_adaptor<Seq>)
    [[nodiscard]] constexpr inline auto enumerate(Seq&& seq)
    {
        return flux::zip(flux::ref(std::forward<Seq>(seq)).cursors(), flux::ref(std::forward<Seq>(seq)));
    }

    template <sequence Seq>
        requires(!flux::detail::is_ref_adaptor<Seq>)
    [[nodiscard]] constexpr inline auto enumerate_mut(Seq&& seq)
    {
        return flux::zip(flux::mut_ref(std::forward<Seq>(seq)).cursors(),
                         flux::mut_ref(std::forward<Seq>(seq)));
    }

    template <sequence... Seq>
    [[nodiscard]] constexpr inline auto zip_all(Seq&&... seqs)
    {
        return flux::zip(flux::ref(std::forward<Seq>(seqs))...);
    }

    template <sequence... Seq>
    [[nodiscard]] constexpr inline auto zip_all_mut(Seq&&... seqs)
    {
        return flux::zip(flux::mut_ref(std::forward<Seq>(seqs))...);
    }

    [[nodiscard]] constexpr inline auto range(size_t count)
    {
        return flux::iota(0uz, count);
    }

    [[nodiscard]] constexpr inline auto range(size_t start, size_t count)
    {
        return flux::iota(start, count);
    }

} // namespace flux
