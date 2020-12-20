// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <operators/forward.hpp>
#include <operators/returns.hpp>

#include <compare>

// Not proposed for standardization
namespace operators::binary {
// cannot use inline namespace because that causes unintended ADL
namespace binary_minus {

constexpr auto operator-(auto && lhs, auto && rhs) OPERATORS_RETURNS(
	OPERATORS_FORWARD(lhs) + -OPERATORS_FORWARD(rhs)
)

struct minus {
	friend auto operator<=>(minus, minus) = default;
};

} // namespace binary_minus

using namespace binary_minus;

} // namespace operators::binary
