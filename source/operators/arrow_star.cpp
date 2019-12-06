// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <operators/arrow_star.hpp>

namespace {

struct dot_star {
	constexpr explicit dot_star(int value_):
		value(value_)
	{
	}

	int value;
};

constexpr int dot_star::* member(&dot_star::value);

struct adl : operators::arrow_star {
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
