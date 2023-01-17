// Copyright David Stone 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

export module operators.arrow_impl.cast_self;

namespace operators::detail {

export template<typename T>
constexpr auto cast_self(auto const & self) -> T const & {
	return static_cast<T const &>(self);
}
export template<typename T>
constexpr auto cast_self(auto & self) -> T & {
	return static_cast<T &>(self);
}
export template<typename T>
constexpr auto cast_self(auto && self) -> T && {
	return static_cast<T &&>(self);
}

} // namespace operators::detail
