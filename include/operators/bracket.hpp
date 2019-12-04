// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <operators/forward.hpp>
#include <operators/returns.hpp>

#include <type_traits>

// Not proposed for standardization
namespace operators {
namespace bracket {
namespace bracket_detail {

// We currently cannot have a free-function `operator[]`, so the approaches used
// in the rest of this library cannot apply here.

constexpr auto iterator_operator_bracket(auto && lhs, auto && rhs) OPERATORS_RETURNS(
	*(OPERATORS_FORWARD(lhs) + OPERATORS_FORWARD(rhs))
)

constexpr auto sequence_range_operator_bracket(auto && lhs, auto && rhs) OPERATORS_RETURNS(
	*(begin(OPERATORS_FORWARD(lhs)) + OPERATORS_FORWARD(rhs))
)

// This must use the full template syntax to avoid a clang crash
#define OPERATORS_DETAIL_BRACKET_DEFINITIONS(self, function) \
	template<typename Index> \
	constexpr auto operator[](Index && index) const & -> \
		decltype(function(self, index)) { \
		return function(self, OPERATORS_FORWARD(index)); \
	} \
	template<typename Index> \
	constexpr auto operator[](Index && index) & -> \
		decltype(function(self, index)) { \
		return function(self, OPERATORS_FORWARD(index)); \
	} \
	template<typename Index> \
	constexpr auto operator[](Index && index) && -> \
		decltype(function(std::move(self), index)) { \
		return function(std::move(self), OPERATORS_FORWARD(index)); \
	}

#define OPERATORS_DETAIL_BRACKET_ITERATOR_DEFINITIONS_IMPL(self) \
	OPERATORS_DETAIL_BRACKET_DEFINITIONS(self, ::operators::bracket::bracket_detail::iterator_operator_bracket)

#define OPERATORS_DETAIL_BRACKET_SEQUENCE_RANGE_DEFINITIONS_IMPL(self) \
	OPERATORS_DETAIL_BRACKET_DEFINITIONS(self, ::operators::bracket::bracket_detail::sequence_range_operator_bracket)


} // namespace bracket_detail


#define OPERATORS_BRACKET_ITERATOR_DEFINITIONS \
	OPERATORS_DETAIL_BRACKET_ITERATOR_DEFINITIONS_IMPL(*this)

#define OPERATORS_BRACKET_SEQUENCE_RANGE_DEFINITIONS \
	OPERATORS_DETAIL_BRACKET_SEQUENCE_RANGE_DEFINITIONS_IMPL(*this)


template<typename Derived>
struct iterator {
private:
	constexpr auto self() const & -> Derived const & {
		return static_cast<Derived const &>(*this);
	}
	constexpr auto self() & -> Derived & {
		return static_cast<Derived &>(*this);
	}
	constexpr auto self() && -> Derived && {
		return static_cast<Derived &&>(*this);
	}
public:
	OPERATORS_DETAIL_BRACKET_ITERATOR_DEFINITIONS_IMPL(self())
};


template<typename Derived>
struct sequence_range {
private:
	constexpr auto self() const & -> Derived const & {
		return static_cast<Derived const &>(*this);
	}
	constexpr auto self() & -> Derived & {
		return static_cast<Derived &>(*this);
	}
	constexpr auto self() && -> Derived && {
		return static_cast<Derived &&>(*this);
	}
public:
	OPERATORS_DETAIL_BRACKET_SEQUENCE_RANGE_DEFINITIONS_IMPL(self())
};

} // namespace bracket
} // namespace operators
