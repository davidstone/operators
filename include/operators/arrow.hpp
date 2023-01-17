// Copyright David Stone 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef OPERATORS_ARROW_HPP
#define OPERATORS_ARROW_HPP

#include <operators/returns.hpp>

import operators.arrow_impl;

import std_module;

// Proposed for standardization as a language feature only

// We currently cannot have a free-function `operator->`, so the approaches used
// in the rest of this library cannot apply here.

#define OPERATORS_DETAIL_TEMPLATE_DECLTYPE_EXPRESSION(function, ...) \
	function<decltype(__VA_ARGS__)>(__VA_ARGS__)

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
	template<typename operators_indirect_identity = ::operators::detail::indirect> \
	constexpr auto operator->() const & OPERATORS_RETURNS( \
		OPERATORS_DETAIL_TEMPLATE_DECLTYPE_EXPRESSION( \
			function, \
			*self(operators_indirect_identity::identity(*this)) \
		) \
	) \
	template<typename operators_indirect_identity = ::operators::detail::indirect> \
	constexpr auto operator->() & OPERATORS_RETURNS( \
		OPERATORS_DETAIL_TEMPLATE_DECLTYPE_EXPRESSION( \
			function, \
			*self(operators_indirect_identity::identity(*this)) \
		) \
	) \
	template<typename operators_indirect_identity = ::operators::detail::indirect> \
	constexpr auto operator->() && OPERATORS_RETURNS( \
		OPERATORS_DETAIL_TEMPLATE_DECLTYPE_EXPRESSION( \
			function, \
			*self(operators_indirect_identity::identity(std::move(*this))) \
		) \
	) \
	auto operator->() const && = delete;

#define OPERATORS_DETAIL_ARROW_DEFINITIONS(self) \
	OPERATORS_DETAIL_ARROW_DEFINITIONS_IMPL(self, ::operators::detail::addressof_wrapper)

#define OPERATORS_DETAIL_ARROW_PROXY_DEFINITIONS(self) \
	OPERATORS_DETAIL_ARROW_DEFINITIONS_IMPL(self, ::operators::detail::arrow_proxy_value)

#define OPERATORS_ARROW_DEFINITIONS \
	OPERATORS_DETAIL_ARROW_DEFINITIONS(::operators::detail::indirect::identity)

#define OPERATORS_ARROW_PROXY_DEFINITIONS \
	OPERATORS_DETAIL_ARROW_PROXY_DEFINITIONS(::operators::detail::indirect::identity)

#endif // OPERATORS_ARROW_HPP