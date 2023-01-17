// Copyright David Stone 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

module;

#include <operators/returns.hpp>

export module operators.unary_plus;

import std_module;

// Not proposed for standardization

#define OPERATORS_UNARY_PLUS_DEFINITION \
	constexpr auto operator+(auto value) OPERATORS_RETURNS( \
		value \
	)

namespace operators_impl {

struct plus {
	friend OPERATORS_UNARY_PLUS_DEFINITION
	friend auto operator<=>(plus, plus) = default;
};

} // namespace operators_impl

namespace operators::unary {

export OPERATORS_UNARY_PLUS_DEFINITION
export using plus = operators_impl::plus;

} // namespace operators::unary
namespace {

template<typename T>
concept has_unary_minus = requires(T value) { -value; };

struct adl : private operators::unary::plus {
	constexpr explicit adl(int value_):
		value(value_)
	{
	}
	int value;
};

static_assert((+adl{3}).value == 3);
static_assert(!has_unary_minus<adl>);

namespace n {

using operators::unary::operator+;

struct implicit {
	int value;
};

static_assert((+implicit{3}.value) == +3);
static_assert(!has_unary_minus<implicit>);

} // namespace n

static_assert((+n::implicit{3}.value) == +3);
static_assert(!has_unary_minus<n::implicit>);

} // namespace
