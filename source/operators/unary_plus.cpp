// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <operators/unary_plus.hpp>

namespace {

template<typename T>
concept has_unary_minus = requires(T value) { -value; };

struct adl : operators::unary::plus {
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
