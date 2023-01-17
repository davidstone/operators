// Copyright David Stone 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef OPERATORS_BRACKET_HPP
#define OPERATORS_BRACKET_HPP

#include <operators/forward.hpp>
#include <operators/returns.hpp>

import operators.bracket_impl;

import std_module;

// Not proposed for standardization

// We currently cannot have a free-function `operator[]`, so the approaches used
// in the rest of this library cannot apply here.

// This must use the full template syntax to avoid a clang crash
#define OPERATORS_DETAIL_BRACKET_DEFINITIONS(self, function) \
	template<typename Index> \
	constexpr auto operator[](Index && index) const & OPERATORS_RETURNS( \
		function(self, OPERATORS_FORWARD(index)) \
	) \
	template<typename Index> \
	constexpr auto operator[](Index && index) & OPERATORS_RETURNS( \
		function(self, OPERATORS_FORWARD(index)) \
	) \
	template<typename Index> \
	constexpr auto operator[](Index && index) && OPERATORS_RETURNS( \
		function(std::move(self), OPERATORS_FORWARD(index)) \
	)

#define OPERATORS_DETAIL_BRACKET_ITERATOR_DEFINITIONS_IMPL(self) \
	OPERATORS_DETAIL_BRACKET_DEFINITIONS(self, ::operators::detail::iterator_operator_bracket)

#define OPERATORS_DETAIL_BRACKET_SEQUENCE_RANGE_DEFINITIONS_IMPL(self) \
	OPERATORS_DETAIL_BRACKET_DEFINITIONS(self, ::operators::detail::sequence_range_operator_bracket)


#define OPERATORS_BRACKET_ITERATOR_DEFINITIONS \
	OPERATORS_DETAIL_BRACKET_ITERATOR_DEFINITIONS_IMPL(*this)

#define OPERATORS_BRACKET_SEQUENCE_RANGE_DEFINITIONS \
	OPERATORS_DETAIL_BRACKET_SEQUENCE_RANGE_DEFINITIONS_IMPL(*this)

#endif // OPERATORS_BRACKET_HPP