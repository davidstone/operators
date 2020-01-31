// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <operators/returns.hpp>

#include <compare>

// Not proposed for standardization
namespace operators::unary {
// cannot use inline namespace because that causes unintended ADL
namespace unary_plus {

constexpr auto operator+(auto value) OPERATORS_RETURNS(
	value
)

struct plus {
	friend auto operator<=>(plus const &, plus const &) = default;
};

} // namespace unary_plus

using namespace unary_plus;

} // namespace operators::unary
