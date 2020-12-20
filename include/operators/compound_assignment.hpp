// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <operators/forward.hpp>
#include <operators/returns.hpp>

#include <compare>
#include <utility>

namespace operators {
// cannot use inline namespace because that causes unintended ADL
namespace compound_assignment_impl {

// Note that this requires the implementation of your binary operator to allow
// an rvalue reference parameter on the left-hand side to potentially alias an
// lvalue reference parameter on the right-hand side.
#define OPERATORS_COMPOUND_ASSIGNMENT_OPERATORS(symbol) \
constexpr auto operator symbol##=(auto & lhs, auto && rhs) OPERATORS_RETURNS( \
	lhs = std::move(lhs) symbol OPERATORS_FORWARD(rhs) \
)

OPERATORS_COMPOUND_ASSIGNMENT_OPERATORS(+)
OPERATORS_COMPOUND_ASSIGNMENT_OPERATORS(-)
OPERATORS_COMPOUND_ASSIGNMENT_OPERATORS(*)
OPERATORS_COMPOUND_ASSIGNMENT_OPERATORS(/)
OPERATORS_COMPOUND_ASSIGNMENT_OPERATORS(%)
OPERATORS_COMPOUND_ASSIGNMENT_OPERATORS(<<)
OPERATORS_COMPOUND_ASSIGNMENT_OPERATORS(>>)
OPERATORS_COMPOUND_ASSIGNMENT_OPERATORS(&)
OPERATORS_COMPOUND_ASSIGNMENT_OPERATORS(|)
OPERATORS_COMPOUND_ASSIGNMENT_OPERATORS(^)

#undef OPERATORS_COMPOUND_ASSIGNMENT_OPERATORS

#define OPERATORS_IMPORT_COMPOUND_ASSIGNMENT \
	using ::operators::operator+=; \
	using ::operators::operator-=; \
	using ::operators::operator*=; \
	using ::operators::operator/=; \
	using ::operators::operator%=; \
	using ::operators::operator<<=; \
	using ::operators::operator>>=; \
	using ::operators::operator&=; \
	using ::operators::operator|=; \
	using ::operators::operator^=;

struct compound_assignment {
	friend auto operator<=>(compound_assignment, compound_assignment) = default;
};

} // namespace compound_assignment_impl

using namespace compound_assignment_impl;

namespace plus_equal_impl {
using ::operators::operator+=;
struct plus_equal {
	friend auto operator<=>(plus_equal, plus_equal) = default;
};
} // namespace plus_equal_impl
using namespace plus_equal_impl;

namespace minus_equal_impl {
using ::operators::operator-=;
struct minus_equal {
	friend auto operator<=>(minus_equal, minus_equal) = default;
};
} // namespace minus_equal_impl
using namespace minus_equal_impl;

namespace times_equal_impl {
using ::operators::operator*=;
struct times_equal {
	friend auto operator<=>(times_equal, times_equal) = default;
};
} // namespace times_equal_impl
using namespace times_equal_impl;

namespace divides_equal_impl {
using ::operators::operator/=;
struct divides_equal {
	friend auto operator<=>(divides_equal, divides_equal) = default;
};
} // namespace divides_equal_impl
using namespace divides_equal_impl;

namespace modulo_equal_impl {
using ::operators::operator%=;
struct modulo_equal {
	friend auto operator<=>(modulo_equal, modulo_equal) = default;
};
} // namespace modulo_equal_impl
using namespace modulo_equal_impl;

namespace left_shift_equal_impl {
using ::operators::operator<<=;
struct left_shift_equal {
	friend auto operator<=>(left_shift_equal, left_shift_equal) = default;
};
} // namespace left_shift_equal_impl
using namespace left_shift_equal_impl;

namespace right_shift_equal_impl {
using ::operators::operator>>=;
struct right_shift_equal {
	friend auto operator<=>(right_shift_equal, right_shift_equal) = default;
};
} // namespace right_shift_equal_impl
using namespace right_shift_equal_impl;

namespace and_equal_impl {
using ::operators::operator&=;
struct and_equal {
	friend auto operator<=>(and_equal, and_equal) = default;
};
} // namespace and_equal_impl
using namespace and_equal_impl;

namespace or_equal_impl {
using ::operators::operator|=;
struct or_equal {
	friend auto operator<=>(or_equal, or_equal) = default;
};
} // namespace or_equal_impl
using namespace or_equal_impl;

namespace xor_equal_impl {
using ::operators::operator^=;
struct xor_equal {
	friend auto operator<=>(xor_equal, xor_equal) = default;
};
} // namespace xor_equal_impl
using namespace xor_equal_impl;

} // namespace operators
