// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <operators/binary_minus.hpp>

namespace {

struct adl : operators::binary::binary_minus::minus {
	constexpr explicit adl(int value_):
		value(value_)
	{
	}
	friend constexpr auto operator-(adl const x) {
		return adl(-x.value);
	}
	friend constexpr auto operator+(adl const lhs, adl const rhs) {
		return lhs.value + rhs.value;
	}

	int value;
};

static_assert(adl(4) - adl(1) == 3);

namespace n {

using operators::binary::operator-;

struct implicit {
	friend constexpr auto operator-(implicit const x) {
		return implicit{-x.value};
	}
	friend constexpr auto operator+(implicit const lhs, implicit const rhs) {
		return lhs.value + rhs.value;
	}

	int value;
};

static_assert(implicit{4} - implicit{1} == 3);

} // namespace n

static_assert(n::implicit{4} - n::implicit{1} == 3);

} // namespace
