// Copyright David Stone 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

module;

#include <operators/forward.hpp>
#include <operators/returns.hpp>

export module operators.arrow_star;

import std_module;

#define OPERATORS_ARROW_STAR_DEFINITION \
	constexpr auto operator->*(auto && lhs, auto && rhs) OPERATORS_RETURNS( \
		(*OPERATORS_FORWARD(lhs)).*OPERATORS_FORWARD(rhs) \
	)

namespace operators_impl {

struct arrow_star {
	friend OPERATORS_ARROW_STAR_DEFINITION
	friend auto operator<=>(arrow_star, arrow_star) = default;
};

} // namespace operators_impl

namespace operators {

export OPERATORS_ARROW_STAR_DEFINITION
export using arrow_star = operators_impl::arrow_star;

} // namespace operators

namespace {

struct dot_star {
	constexpr explicit dot_star(int value_):
		value(value_)
	{
	}

	int value;
};

constexpr int dot_star::* member(&dot_star::value);

struct adl : private operators::arrow_star {
	constexpr explicit adl(int value_):
		value(value_)
	{
	}
	constexpr auto const & operator*() const {
		return value;
	}

private:
	dot_star value;
};

static_assert(adl(3)->*member == 3);

namespace n {

using operators::operator->*;

struct implicit {
	constexpr explicit implicit(int value_):
		value(value_)
	{
	}
	constexpr auto const & operator*() const {
		return value;
	}

private:
	dot_star value;
};

static_assert(implicit(3)->*member == 3);

} // namespace n

static_assert(n::implicit(3)->*member == 3);

} // namespace
