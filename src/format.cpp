// Formatting library for C++
//
// Copyright (c) 2012 - 2016, Victor Zverovich
// All rights reserved.
//
// For the license information refer to format.h.
// version 11.0.2
// https://github.com/fmtlib/fmt/

#include "orb/fmt/format-inl.h"

ORBFMT_BEGIN_NAMESPACE
namespace detail {

template ORBFMT_API auto dragonbox::to_decimal(float x) noexcept
    -> dragonbox::decimal_fp<float>;
template ORBFMT_API auto dragonbox::to_decimal(double x) noexcept
    -> dragonbox::decimal_fp<double>;

#ifndef ORBFMT_STATIC_THOUSANDS_SEPARATOR
template ORBFMT_API locale_ref::locale_ref(const std::locale& loc);
template ORBFMT_API auto locale_ref::get<std::locale>() const -> std::locale;
#endif

// Explicit instantiations for char.

template ORBFMT_API auto thousands_sep_impl(locale_ref)
    -> thousands_sep_result<char>;
template ORBFMT_API auto decimal_point_impl(locale_ref) -> char;

template ORBFMT_API void buffer<char>::append(const char*, const char*);

template ORBFMT_API void vformat_to(buffer<char>&, string_view,
                                 typename vformat_args<>::type, locale_ref);

// Explicit instantiations for wchar_t.

template ORBFMT_API auto thousands_sep_impl(locale_ref)
    -> thousands_sep_result<wchar_t>;
template ORBFMT_API auto decimal_point_impl(locale_ref) -> wchar_t;

template ORBFMT_API void buffer<wchar_t>::append(const wchar_t*, const wchar_t*);

}  // namespace detail
ORBFMT_END_NAMESPACE
