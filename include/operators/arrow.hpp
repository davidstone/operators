// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <operators/forward.hpp>
#include <operators/returns.hpp>

#include <memory>
#include <type_traits>

// Proposed for standardization as a language feature only
namespace operators {

// We currently cannot have a free-function `operator->`, so the approaches used
// in the rest of this library cannot apply here.

namespace detail {

template<typename T>
constexpr auto && cast_self(auto const & self) {
	return static_cast<T const &>(self);
}
template<typename T>
constexpr auto && cast_self(auto & self) {
	return static_cast<T &>(self);
}
template<typename T>
constexpr auto && cast_self(auto && self) {
	return static_cast<T &&>(self);
}

template<typename T>
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

// TODO: It might be ideal to store the exact type returned by `operator*`,
// meaning a value for values and an rvalue reference for rvalue references.
template<typename T>
arrow_proxy_value(T &&) -> arrow_proxy_value<T>;

// This delays the instantiation of the arrow operator until it is called. This
// allows you to use an `operator*` that is defined outside of the class or
// defined with a deduced return type.
struct indirect {
	static constexpr auto && identity(auto && value) {
		return OPERATORS_FORWARD(value);
	}
};

// It does not seem possible to make `operator->` SFINAE friendly, safe, and
// work with const return values. If we make it SFINAE friendly and we have a
// type that returns an rvalue from `operator*` when called on an rvalue, that
// will be removed from the overload set instead of causing an error and we will
// fall back on the `operator->() const &` overload, so we will still end up
// returning a reference to a temporary. To prevent this, we define an `auto
// operator->() const && = delete` overload to catch that case. This means that
// users will get an error if they return a const value from a function or if
// they move from a value declared const. Neither of those are the end of the
// world, but are still unfortunate.
#define OPERATORS_DETAIL_ARROW_DEFINITIONS_IMPL(self, function) \
	template<typename T = ::operators::detail::indirect> \
	constexpr auto operator->() const & OPERATORS_RETURNS( \
		function(*self(T::identity(*this))) \
	) \
	template<typename T = ::operators::detail::indirect> \
	constexpr auto operator->() & OPERATORS_RETURNS( \
		function(*self(T::identity(*this))) \
	) \
	template<typename T = ::operators::detail::indirect> \
	constexpr auto operator->() && OPERATORS_RETURNS( \
		function(*self(T::identity(std::move(*this)))) \
	) \
	auto operator->() const && = delete;

#define OPERATORS_DETAIL_ARROW_DEFINITIONS(self) \
	OPERATORS_DETAIL_ARROW_DEFINITIONS_IMPL(self, ::std::addressof)

#define OPERATORS_DETAIL_ARROW_PROXY_DEFINITIONS(self) \
	OPERATORS_DETAIL_ARROW_DEFINITIONS_IMPL(self, ::operators::detail::arrow_proxy_value)

} // namespace detail

#define OPERATORS_ARROW_DEFINITIONS \
	OPERATORS_DETAIL_ARROW_DEFINITIONS(::operators::detail::indirect::identity)

#define OPERATORS_ARROW_PROXY_DEFINITIONS \
	OPERATORS_DETAIL_ARROW_PROXY_DEFINITIONS(::operators::detail::indirect::identity)


template<typename Derived>
struct arrow {
	OPERATORS_DETAIL_ARROW_DEFINITIONS(::operators::detail::cast_self<Derived>)
};


template<typename Derived>
struct arrow_proxy {
	OPERATORS_DETAIL_ARROW_PROXY_DEFINITIONS(::operators::detail::cast_self<Derived>)
};

} // namespace operators
