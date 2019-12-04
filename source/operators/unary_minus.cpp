// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <operators/unary_minus.hpp>
#include <operators/unary_plus.hpp>

namespace {

template<typename T>
concept has_unary_plus = requires(T value) { +value; };

struct adl : operators::unary::minus {
	constexpr explicit adl(int value_):
		value(value_)
	{
	}
	friend constexpr auto operator-(int const lhs, adl const rhs) {
		return lhs - rhs.value;
	}

private:
	int value;
};

static_assert(0 - adl(3) == -3);
static_assert(-adl(3) == -3);

static_assert(!has_unary_plus<adl>);

namespace n {

using operators::unary::operator-;

struct implicit {
	friend constexpr auto operator-(int const lhs, implicit const rhs) {
		return lhs - rhs.value;
	}

	int value;
};

static_assert(0 - implicit{3} == -3);
static_assert(-implicit{3} == -3);

static_assert(!has_unary_plus<implicit>);

} // namespace n

static_assert(-n::implicit{3} == -3);

static_assert(!has_unary_plus<n::implicit>);

} // namespace
