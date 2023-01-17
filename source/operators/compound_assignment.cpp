// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

module;

#include <operators/forward.hpp>
#include <operators/returns.hpp>

export module operators.compound_assignment;

import std_module;

// Note that this requires the implementation of your binary operator to allow
// an rvalue reference parameter on the left-hand side to potentially alias an
// lvalue reference parameter on the right-hand side.
#define OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(symbol) \
constexpr auto operator symbol##=(auto & lhs, auto && rhs) OPERATORS_RETURNS( \
	lhs = std::move(lhs) symbol OPERATORS_FORWARD(rhs) \
)

#define OPERATORS_COMPOUND_ASSIGNMENT_ALL(...) \
	__VA_ARGS__ OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(+) \
	__VA_ARGS__ OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(-) \
	__VA_ARGS__ OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(*) \
	__VA_ARGS__ OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(/) \
	__VA_ARGS__ OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(%) \
	__VA_ARGS__ OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(<<) \
	__VA_ARGS__ OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(>>) \
	__VA_ARGS__ OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(&) \
	__VA_ARGS__ OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(|) \
	__VA_ARGS__ OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(^)

namespace operators_impl {

namespace plus_equal {
struct impl {
	friend OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(+)
	friend auto operator<=>(impl, impl) = default;
};
}
namespace minus_equal {
struct impl {
	friend OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(-)
	friend auto operator<=>(impl, impl) = default;
};
}
namespace times_equal {
struct impl {
	friend OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(*)
	friend auto operator<=>(impl, impl) = default;
};
}
namespace divides_equal {
struct impl {
	friend OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(/)
	friend auto operator<=>(impl, impl) = default;
};
}
namespace modulo_equal {
struct impl {
	friend OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(%)
	friend auto operator<=>(impl, impl) = default;
};
}
namespace left_shift_equal {
struct impl {
	friend OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(<<)
	friend auto operator<=>(impl, impl) = default;
};
}
namespace right_shift_equal {
struct impl {
	friend OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(>>)
	friend auto operator<=>(impl, impl) = default;
};
}
namespace and_equal {
struct impl {
	friend OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(&)
	friend auto operator<=>(impl, impl) = default;
};
}
namespace or_equal {
struct impl {
	friend OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(|)
	friend auto operator<=>(impl, impl) = default;
};
}
namespace xor_equal {
struct impl {
	friend OPERATORS_COMPOUND_ASSIGNMENT_DEFINITION(^)
	friend auto operator<=>(impl, impl) = default;
};
}
namespace compound_assignment {
struct impl {
	OPERATORS_COMPOUND_ASSIGNMENT_ALL(friend)
	friend auto operator<=>(impl, impl) = default;
};
}

} // namespace operators_impl

namespace operators {

OPERATORS_COMPOUND_ASSIGNMENT_ALL(export)

export using plus_equal = operators_impl::plus_equal::impl;
export using minus_equal = operators_impl::minus_equal::impl;
export using times_equal = operators_impl::times_equal::impl;
export using divides_equal = operators_impl::divides_equal::impl;
export using modulo_equal = operators_impl::modulo_equal::impl;
export using left_shift_equal = operators_impl::left_shift_equal::impl;
export using right_shift_equal = operators_impl::right_shift_equal::impl;
export using and_equal = operators_impl::and_equal::impl;
export using or_equal = operators_impl::or_equal::impl;
export using xor_equal = operators_impl::xor_equal::impl;
export using compound_assignment = operators_impl::compound_assignment::impl;

} // namespace operators
