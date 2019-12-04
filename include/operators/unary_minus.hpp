// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <operators/forward.hpp>
#include <operators/returns.hpp>

// Not proposed for standardization
namespace operators::unary {
// cannot use inline namespace because that causes unintended ADL
namespace unary_minus {

constexpr auto operator-(auto && value) OPERATORS_RETURNS(
	0 - OPERATORS_FORWARD(value)
)

struct minus {};

} // namespace unary_minus

using namespace unary_minus;

} // namespace operators::unary
