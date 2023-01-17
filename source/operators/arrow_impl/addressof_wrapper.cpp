// Copyright David Stone 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

export module operators.arrow_impl.addressof_wrapper;

import std_module;

namespace operators::detail {

// This works on rvalue references
export template<typename T> requires std::is_reference_v<T>
constexpr auto addressof_wrapper(auto && object) noexcept {
	return ::std::addressof(object);
}

} // namespace operators::detail
