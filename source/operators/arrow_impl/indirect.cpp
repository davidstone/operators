// Copyright David Stone 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

module;

#include <operators/forward.hpp>

export module operators.arrow_impl.indirect;

import std_module;

namespace operators::detail {

// This delays the instantiation of the arrow operator until it is called. This
// allows you to use an `operator*` that is defined outside of the class or
// defined with a deduced return type.
export struct indirect {
	template<typename T>
	static constexpr auto identity(T && value) -> T && {
		return OPERATORS_FORWARD(value);
	}
};

} // namespace operators::detail