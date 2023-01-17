// Copyright David Stone 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

module;

#include <operators/forward.hpp>

export module operators.arrow_impl.arrow_proxy_value;

import std_module;

namespace operators::detail {

export template<typename T>
struct arrow_proxy_value {
	constexpr explicit arrow_proxy_value(T value_):
		value(OPERATORS_FORWARD(value_))
	{
	}
	constexpr auto operator->() && {
		return std::addressof(value);
	}

private:
	T value;
};

} // namespace operators::detail