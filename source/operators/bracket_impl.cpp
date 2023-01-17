// Copyright David Stone 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

module;

#include <operators/forward.hpp>
#include <operators/returns.hpp>

export module operators.bracket_impl;

// Not proposed for standardization
namespace operators::detail {

export constexpr auto iterator_operator_bracket(auto && lhs, auto && rhs) OPERATORS_RETURNS(
	*(OPERATORS_FORWARD(lhs) + OPERATORS_FORWARD(rhs))
)

export constexpr auto sequence_range_operator_bracket(auto && lhs, auto && rhs) OPERATORS_RETURNS(
	*(begin(OPERATORS_FORWARD(lhs)) + OPERATORS_FORWARD(rhs))
)

} // namespace operators::detail
