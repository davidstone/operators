// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <operators/forward.hpp>
#include <operators/returns.hpp>

#include <compare>

namespace operators {
// cannot use inline namespace because that causes unintended ADL
namespace arrow_star_impl {

constexpr auto operator->*(auto && lhs, auto && rhs) OPERATORS_RETURNS(
	(*OPERATORS_FORWARD(lhs)).*OPERATORS_FORWARD(rhs)
)

struct arrow_star {
	friend auto operator<=>(arrow_star, arrow_star) = default;
};

} // namespace arrow_star_impl

using namespace arrow_star_impl;

} // namespace operators
